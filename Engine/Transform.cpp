#include "pch.h"
#include "Transform.h"

McCol::Transform::Transform(GameObject* owner)
	: Component(owner)
	, m_LocalPosition(0.0f, 0.0f)
	, m_LocalRotation(0.0f)
	, m_LocalScale(1.0f, 1.0f)
	, m_LocalMatrix(D2D1::Matrix3x2F::Identity())
	, m_WorldMatrix(m_LocalMatrix)
	, m_NeedsMatrixUpdate(false)
{
	m_Name = stringToWstring(typeid(*this).name());
}

McCol::Transform::~Transform()
{
}

void McCol::Transform::Initialize()
{
}

void McCol::Transform::Update(const float& deltaTime)
{
	UpdateMatrix();
}

void McCol::Transform::Translate(const McCol::Vector2& translation)
{
	m_LocalPosition += translation;
	m_NeedsMatrixUpdate = true;
}

void McCol::Transform::Rotate(const float& angle)
{
	m_LocalRotation += angle;

	if (m_LocalRotation > 360.0f)
		m_LocalRotation -= 360.0f;

	m_NeedsMatrixUpdate = true;
}

void McCol::Transform::UpdateMatrix()
{
	if (!m_NeedsMatrixUpdate)
		return;

	// Assuming you have member variables for position, rotation, and scale
	const D2D1_MATRIX_3X2_F& scaleMatrix = D2D1::Matrix3x2F::Scale(m_LocalScale.x, m_LocalScale.y);
	const D2D1_MATRIX_3X2_F& rotationMatrix = D2D1::Matrix3x2F::Rotation(m_LocalRotation);
	const D2D1_MATRIX_3X2_F& translationMatrix = D2D1::Matrix3x2F::Translation(m_LocalPosition.x, m_LocalPosition.y);

	// Combine the transformation matrices in the SRT order (Scale-Rotate-Translate)
	m_LocalMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	m_WorldMatrix = m_LocalMatrix;

	Transform* parentTransform = GetComponentInParent<Transform>();
	while (parentTransform != nullptr)
	{
		m_WorldMatrix = m_WorldMatrix * parentTransform->m_LocalMatrix;
		parentTransform = parentTransform->GetComponentInParent<Transform>();
	}

	//m_NeedsMatrixUpdate = false;
}

void McCol::Transform::SetPosition(const McCol::Vector2& position)
{
	m_LocalPosition = position;
	m_NeedsMatrixUpdate = true;

	UpdateMatrix();
}

void McCol::Transform::SetRotation(const float& rotation)
{
	m_LocalRotation = rotation;
	m_NeedsMatrixUpdate = true;

	UpdateMatrix();
}

void McCol::Transform::SetScale(const McCol::Vector2& scale)
{
	m_LocalScale = scale;
	m_NeedsMatrixUpdate = true;

	UpdateMatrix();
}

McCol::Vector2 McCol::Transform::GetPosition()
{
	return Vector2{ m_WorldMatrix.dx, m_WorldMatrix.dy };
}

McCol::Vector2 McCol::Transform::GetLocalPosition()
{
	return m_LocalPosition;
}

float McCol::Transform::GetRotation()
{
	const float rotation = atanf(1.0f * (m_WorldMatrix.m12 / m_WorldMatrix.m11)) * (180.0f / 3.1415f);

	Vector2 _scale = GetScale();
	float _angle2 = acosf(m_WorldMatrix.m11 / _scale.x) * (180.0f / 3.1415f);
	float _angle3 = asinf(m_WorldMatrix.m12 / _scale.x) * (180.0f / 3.1415f);
	float _angle4 = asinf(-m_WorldMatrix.m21 / _scale.y) * (180.0f / 3.1415f);
	float _angle5 = acosf(m_WorldMatrix.m22 / _scale.y) * (180.0f / 3.1415f);

	return rotation;
}

McCol::Vector2 McCol::Transform::GetScale()
{
	const float scaleX = sqrtf(m_WorldMatrix._11 * m_WorldMatrix._11 + m_WorldMatrix._21 * m_WorldMatrix._21);
	const float scaleY = sqrtf(m_WorldMatrix._12 * m_WorldMatrix._12 + m_WorldMatrix._22 * m_WorldMatrix._22);

	return Vector2{ scaleX, scaleY };
}

D2D1_MATRIX_3X2_F McCol::Transform::GetMatrix()
{
	return D2D1::Matrix3x2F::Scale(1, -1) * m_WorldMatrix;
}

