#pragma once
#include "IUpdatable.h"

namespace McCol
{
    class UI;
    class UISystem : public IUpdatable
    {
    public:
        UISystem();
        ~UISystem() = default;

    private:
        static UISystem* m_Instance;
        std::vector<UI*> m_UIs;
        UI* m_FocusedUI;

    public:
        static UISystem* GetInstance()
        {
            if (m_Instance == nullptr)
                m_Instance = new UISystem;

            return m_Instance;
        }

        void Initialize();
        void Update(const float& deltaTime);

        void SetFocusedUI(UI* ui);
        void GetFocusedUI();

        void RegisterUI(const std::wstring_view& uiName, UI* ui);
    };
}
