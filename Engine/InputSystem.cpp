#include "pch.h"
#include "InputSystem.h"

McCol::InputSystem* McCol::InputSystem::m_Instance = nullptr;

McCol::InputSystem::InputSystem()
	: m_keyState{}
    , m_curMousePos{}
{
}

void McCol::InputSystem::Initialize()
{
	for (auto& key : m_keyState)
	{
		key.keyState = KeyState::NONE;
		key.prevPushed = false;
	}
}

void McCol::InputSystem::Update()
{
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < 256; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				if (m_keyState[i].prevPushed)
				{
					m_keyState[i].keyState = KeyState::HOLD;
				}
				else
				{
					m_keyState[i].keyState = KeyState::DOWN;
					m_keyState[i].prevPushed = true;
				}
			}
			else
			{
				if (m_keyState[i].prevPushed)
				{
					m_keyState[i].keyState = KeyState::UP;
					m_keyState[i].prevPushed = false;
				}
				else
				{
					m_keyState[i].keyState = KeyState::NONE;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 256; i++)
		{
			m_keyState[i].prevPushed = false;
			if (KeyState::DOWN == m_keyState[i].keyState || KeyState::HOLD == m_keyState[i].keyState)
			{
				m_keyState[i].keyState = KeyState::UP;
			}
			else if (KeyState::UP == m_keyState[i].keyState)
			{
				m_keyState[i].keyState = KeyState::NONE;
			}
		}
	}

	// Mouse 위치 계산
	POINT ptPos = {};
	// 현재 마우스 위치
	GetCursorPos(&ptPos);
	// 스크린좌표계로 마우스 위치 반환
	ScreenToClient(hWnd, &ptPos);
	m_curMousePos = Vector2((float)ptPos.x, (float)ptPos.y);
}

void McCol::InputSystem::Finalize()
{
	SAFE_DELETE(m_Instance)
}


