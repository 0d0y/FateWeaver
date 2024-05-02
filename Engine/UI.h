#pragma once
#include "EventHandler.h"
#include "GameObject.h"
#include "TextRenderer.h"
#include "Vector2.h"

namespace McCol
{
    class Transform;
    class OBB;
    class TextRenderer;
    class TextureRenderer;
    class PrimitiveRenderer;

    class UI : public GameObject, public EventHandler
    {
    public:
        UI(std::wstring_view name);
        ~UI() override;

    protected:
        D2D1_RECT_F m_UIAreaRect;

        Transform* m_UITransform;
        OBB* m_UICollider;
        TextRenderer* m_UIText;
        TextureRenderer* m_UITexture;
        PrimitiveRenderer* m_UIPrimitive;

        bool m_IsUIText;
        bool m_IsUITexture;
        bool m_IsUIPrimitive;

        bool m_IsActivate;     // 터치 불가가 될 UI인지 판정하는 bool 값 
        bool m_IsInteractable; // 실제로 UI의 터치 불가를 판정하는 bool값

    public:
        void Initialize() override;
        void Update(const float& deltaTime) override;
        void FixedUpdate(const float& deltaTime) override;
        void Render(McCol::D2DRender* renderer) override;

        void HandleCollisionEnter(McCol::Collider* otherCollider) override;
        void HandleCollisionStay(McCol::Collider* otherCollider) override;
        void HandleCollisionExit(McCol::Collider* otherCollider) override;

        Transform* GetUITransform();
        OBB* GetUICollider();
        TextRenderer* GetUIText();
        TextureRenderer* GetUITexture();
        PrimitiveRenderer* GetUIPrimitive();

        void AddUIText();
        void AddUITexture();
        void AddUIPrimitive();

        void SetUIAreaRect(const float& uiWidth, const float& uiHeight);
        void LoadUITexture(const std::wstring& strFilePath, std::wstring_view key);
        void SetUIText(const std::wstring_view srcText, const float& fontSize, FontWeight fontWeight, D2D1::ColorF::Enum brushColor);

        void SetUIActivate(bool uiActivate);
        void UIInteractiveOn(std::any any);
        void UIInteractiveOff(std::any any);

        void SubScribeOn(std::wstring_view evtID);
        void SubScribeOff(std::wstring_view evtID);

        void AbleOn(std::any any);
        void AbleOff(std::any any);
    };
}

