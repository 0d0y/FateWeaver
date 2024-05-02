#pragma once
#include "EventHandler.h"
#include "../RenderEngine/D2DRender.h"

namespace McCol
{
	class TimeSystem;
	class InputSystem;
	class SceneSystem;

	class Mengine : public EventHandler
	{
	public:
		Mengine();
		virtual ~Mengine();

	public:
		/*Window Resolution*/
		static constexpr int ResolutionWidth = 1920;
		static constexpr int ResolutionHeight = 1080;

		/*Windows*/
	protected:
		HWND m_hWnd;
		MSG m_Msg;

		/*Delta Time*/
		float m_deltaTime = 0.016f;

	protected:
		/*System*/
		D2DRender* m_Renderer;
		TimeSystem* m_TimeSystem;
		SceneSystem* m_SceneSystem;

	public:
		/*Init*/
		virtual HRESULT Initialize(HINSTANCE hInst, const char* appName);

		/*Render*/
		virtual void BeginRender();
		virtual void EndRender();

		/*Loop*/
		void Loop();

		/*unInit*/
		virtual void Finalize();

		// TODO : D2DTexture로 분리하기
		D2DRender* GetEngine() { return m_Renderer; }

	protected:
		virtual void UpdateAll(const float& deltaTime);
		virtual void RenderAll();

	public:
		HCURSOR m_CustomCursor;

	private:
		bool m_IsLoop;
		void EndLoop(std::any any);
	};
}