#pragma once
#include "IUpdatable.h"
#include "Vector2.h"

namespace McCol
{
    class InputSystem
    {
    private:
        enum class KeyState
        {
            NONE,	  // 현재 및 이전	프레임에 입력 없음
            DOWN,	  // 현재			프레임에 입력 됨
            HOLD,	  // 현재 및 이전	프레임에 입력 됨
            UP,		  // 현재			프레임에 입력 종료함
        };

        struct KeyInfo
        {
            bool prevPushed;
            KeyState keyState;
        };

    private:
        InputSystem();
        ~InputSystem() = default;

    private:
        static InputSystem* m_Instance;
        KeyInfo m_keyState[256];	// Windows 키 코드는 0 ~ 255
        Vector2 m_curMousePos;

    public:
        static InputSystem* GetInstance()
        {
            if (m_Instance == nullptr)
                m_Instance = new InputSystem;

            return m_Instance;
        }
        void Initialize();
        void Update();
        void Finalize();

    public: // 키 입력 진행 순서는 아래 함수를 따름
        inline bool IsKeyNone(int keyCode) const;
        inline bool IsKeyDown(int keyCode) const;
        inline bool IsKeyHold(int keyCode) const;
        inline bool IsKeyUp(int keyCode) const;
        inline Vector2 GetMousePos() const;
    };

    inline bool InputSystem::IsKeyNone(int keyCode) const
    {
        return m_keyState[keyCode].keyState == KeyState::NONE;
    }

    inline bool InputSystem::IsKeyDown(int keyCode) const
    {
        return m_keyState[keyCode].keyState == KeyState::DOWN;
    }

    inline bool InputSystem::IsKeyHold(int keyCode) const
    {
        return m_keyState[keyCode].keyState == KeyState::HOLD;
    }

    inline bool InputSystem::IsKeyUp(int keyCode) const
    {
        return m_keyState[keyCode].keyState == KeyState::UP;
    }

    inline Vector2 McCol::InputSystem::GetMousePos() const
    {
        return {m_curMousePos.x - 960.f, -(m_curMousePos.y - 540.f)};
    }
}

