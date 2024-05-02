#pragma once

#include "Component.h"
#include "IUpdatable.h"

#include "Vector2.h"

namespace McCol
{
	class GameObject;

	class Transform : public Component, public IUpdatable
	{
	public:
		Transform(GameObject* owner);
		~Transform() override;

	private:
		Vector2 m_LocalPosition;	// Translation
		float m_LocalRotation;		// Rotation
		Vector2 m_LocalScale;		// Scale

		D2D1_MATRIX_3X2_F m_LocalMatrix;
		D2D1_MATRIX_3X2_F m_WorldMatrix;

		bool m_NeedsMatrixUpdate;	// UpdateMatrix 수행 필요성 검사

	public:
		// 상속 함수
		void Initialize() override;
		void Update(const float& deltaTime) override;

	private:
		void UpdateMatrix();

	public:
		// Transform 관련 함수
		void Translate(const Vector2& translation);
		void Rotate(const float& angle);

	public:
		// 로컬 좌표계 설정
		void SetPosition(const Vector2& position);
		void SetRotation(const float& rotation);
		void SetScale(const Vector2& scale);

		// 월드 좌표계 반환
		Vector2 GetPosition();
		Vector2 GetLocalPosition();
		float GetRotation();
		Vector2 GetScale();
		D2D1_MATRIX_3X2_F GetMatrix();
	};
}