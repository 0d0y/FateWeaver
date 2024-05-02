#pragma once
#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"

#include "Vector2.h"
/*----------------------------------------------------------------------------------------------------------------------------------
Collider
AABB, OBB 각 이름 클래스를 게임오브젝트에 컴포넌트로 추가시키면 됨.
기본적으로 콜라이더 사이즈와 위치는 컴포넌트를 상속하고 있는 소유자 오브젝트의 값을 그대로 가져옴.
void SetColliPosOffset(const Vector2& ColliOffset);
void SetColliScaleOffset(const Vector2& ColliScale);
함수로 offset을 조정할 수 있다.
(지금은 소유자 오브젝트가 회전할때 posoffset 적용한 그 위치에서 콜라이더가 회전하는데
오브젝트 회전된 위치 따라서 콜라이더가 따라 돌게하려면 수정 해야됨.)
그리고 void AddCollider(Collider* collider)로
CollisionSystem 벡터 안에 콜라이더 넣어주고
(이 부분 일단 이렇게 명시적으로 해놨는데 추후 콜라이더 생성 시 자동으로 삽입되게 수정할수도? )
업데이트에서 CollisionSystem 업데이트 호출하면 돌아가면서
충돌 시 ICollidable를 상속받은 게임 오브젝트 파생클래스에 구현해둔 순수 가상함수
virtual void HandleCollision(Collider* mine, Collider* other); 이 호출 됨.
각 기능에 맞춰 각 게임오브젝트 파생클래스에 HandleCollision() 구현 해주면 됨.
현재 AABB, OBB 같은 콜라이더끼리만 충돌 체크 가능.

TODO : 이전 프레임에 충돌 됐는지 체크하는 멤버 변수하나 만들어서 Enter(), Exit(), OnCollision() 충돌 조건 세분화 하기
----------------------------------------------------------------------------------------------------------------------------------*/
namespace McCol
{
	class Transform;
	class BaseRenderer;

	class Collider : public Component, public IFixedUpdatable, public IRenderable
	{
	public:
		enum class CollisionState
		{
			None,
			Enter,
			Stay,
			Exit
		};
	public:
		/*temp*/
		//임시 충돌 확인용 색
		//D2D1_COLOR_F m_color;

	protected:
		bool m_IsColliding;
		CollisionState m_CollisionState;

		Transform* m_OwnerTransform;
		BaseRenderer* m_OwnerRenderer;

		Vector2 m_ColliPosOffset;
		Vector2 m_ColliScaleOffset;
		Vector2 m_Size;

		D2D1_MATRIX_3X2_F m_LocalMatrix;
		D2D1_MATRIX_3X2_F m_WorldMatrix;

	public:
		Collider(GameObject* owner);
		~Collider() override;

	public:
		void Initialize() override;
		void Render(D2DRender* renderer) override;

	public:
		virtual bool CheckCollision(Collider* other) abstract;

	public:
		void SetColliPosOffset(const Vector2& ColliOffset);
		void SetColliScaleOffset(const Vector2& ColliScale);

		Vector2 GetColliPosOffset() const { return m_ColliPosOffset; }
		Vector2 GetColliScaleOffset() const { return m_ColliScaleOffset; }

		Transform* GetOwnerTransform() const { return m_OwnerTransform; }
		D2D1_MATRIX_3X2_F GetMatrix() const { return m_WorldMatrix; }
		Vector2 GetSize() const { return m_Size; }
		void SetSize(Vector2 size) { m_Size = size; }

		void SetColliding(bool iscolliding);
		void SetCollisionState(CollisionState state);
		bool IsColliding() const;
		void ResetCollisionState();
	};
}
