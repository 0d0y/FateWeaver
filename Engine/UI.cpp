#include "pch.h"
#include "UI.h"

#include "CameraSystem.h"
#include "InputSystem.h"

#include "Transform.h"
#include "OBB.h"
#include "TextRenderer.h"
#include "TextureRenderer.h"
#include "PrimitiveRenderer.h"

#include "../RenderEngine/D2DRender.h"
#include "../RenderEngine/D2DTextureSystem.h"

#define TEXT_LENGTH(T) static_cast<UINT32>((T).length())

McCol::UI::UI(std::wstring_view name)
    : GameObject(name, Layer::UI)
    , m_UIAreaRect{}
    , m_UITransform(nullptr)
    , m_UICollider(nullptr)
    , m_UIText(nullptr)
    , m_UITexture(nullptr)
    , m_UIPrimitive(nullptr)
    , m_IsUIText(false)
    , m_IsUITexture(false)
    , m_IsUIPrimitive(false)
    , m_IsInteractable(true)
    , m_IsActivate(true)
{
    m_UITransform = AddComponent<Transform>();
    m_UICollider = AddComponent<OBB>();

    McCol::EventSystem::GetInstance()->Subscribe(L"UI_INTERACTIVE_TRUE", MakeListenerInfo(&UI::UIInteractiveOn));
    McCol::EventSystem::GetInstance()->Subscribe(L"UI_INTERACTIVE_FALSE", MakeListenerInfo(&UI::UIInteractiveOff));
}

McCol::UI::~UI()
{
}

// 민정) DebugPrint용 Time 설정할때 필요한 코드
float ProgressTime = 0.f;

void McCol::UI::Initialize()
{
    GameObject::Initialize();
}

void McCol::UI::Update(const float& deltaTime)
{
    /*const float debugTime = 1.0f;

    if (ProgressTime > debugTime)
    {
        ProgressTime -= debugTime;
        DEBUGPRINT("Mouse Pos X : %f / Mouse Pos Y : %f \n", InputSystem::GetInstance()->GetMousePos().x, InputSystem::GetInstance()->GetMousePos().y);
    }

    ProgressTime += deltaTime;*/
}

void McCol::UI::FixedUpdate(const float& deltaTime)
{
    GameObject::FixedUpdate(deltaTime);
}

void McCol::UI::Render(McCol::D2DRender* renderer)
{
    GameObject::Render(renderer);
}

void McCol::UI::HandleCollisionEnter(McCol::Collider* otherCollider)
{

}

void McCol::UI::HandleCollisionStay(McCol::Collider* otherCollider)
{
}

void McCol::UI::HandleCollisionExit(McCol::Collider* otherCollider)
{
}

McCol::Transform* McCol::UI::GetUITransform()
{
    return m_UITransform;
}

McCol::OBB* McCol::UI::GetUICollider()
{
    return m_UICollider;
}

McCol::TextRenderer* McCol::UI::GetUIText()
{
    return m_UIText;
}

McCol::TextureRenderer* McCol::UI::GetUITexture()
{
    return m_UITexture;
}

McCol::PrimitiveRenderer* McCol::UI::GetUIPrimitive()
{
    return m_UIPrimitive;
}

void McCol::UI::AddUIText()
{
    m_UIText = AddComponent<TextRenderer>();
    m_IsUIText = true;
}

void McCol::UI::AddUITexture()
{
    m_UITexture = AddComponent<TextureRenderer>();
    m_IsUITexture = true;
}

void McCol::UI::AddUIPrimitive()
{
    m_UIPrimitive = AddComponent<PrimitiveRenderer>();
    m_IsUIPrimitive = true;
}

void McCol::UI::SetUIAreaRect(const float& uiWidth, const float& uiHeight)
{
    // Collider, Text, Texture, Prmitive에서 UI가 그려질 영역 Set
    m_UICollider->SetSize({ uiWidth, uiHeight });

    if(m_IsUIText)
    {
        m_UIText->SetLayoutRect(uiWidth, uiHeight);
    }

    if(m_IsUIPrimitive)
        m_UIPrimitive->SetPmRectangle(uiWidth, uiHeight);
}

void McCol::UI::LoadUITexture(const std::wstring& strFilePath, std::wstring_view key)
{
    if(m_IsUITexture)
    {
        m_UITexture->SetBitmap(D2DTextureSystem::GetInstance()->LoadTexture(strFilePath, key));
        m_UITexture->SetTextureScale(1.0f);
    }
}

void McCol::UI::SetUIText(const std::wstring_view srcText, const float& fontSize, FontWeight fontWeight, D2D1::ColorF::Enum brushColor)
{
    if (m_IsUIText)
    {
        m_UIText->SetTextAttribute(srcText, fontSize, fontWeight);
        m_UIText->SetBrushColor(brushColor);
    }
}

void McCol::UI::SetUIActivate(bool uiActivate)
{
    m_IsActivate = uiActivate;
}

void McCol::UI::UIInteractiveOn(std::any any)
{
    if (m_IsActivate)
        m_IsInteractable = true;
}

void McCol::UI::UIInteractiveOff(std::any any)
{
    if (m_IsActivate)
        m_IsInteractable = false;
}

void McCol::UI::SubScribeOn(std::wstring_view evtID)
{
    EventSystem::GetInstance()->Subscribe(evtID, MakeListenerInfo(&UI::AbleOn));
}

void McCol::UI::SubScribeOff(std::wstring_view evtID)
{
    EventSystem::GetInstance()->Subscribe(evtID, MakeListenerInfo(&UI::AbleOff));
}

void McCol::UI::AbleOn(std::any any)
{
    SetAble(true);
}

void McCol::UI::AbleOff(std::any any)
{
    SetAble(false);
}



