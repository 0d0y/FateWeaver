#pragma once
#include <windows.h>
#include <d2d1.h>


namespace McCol
{
	class IRenderEngine abstract
	{
	protected:
		static IRenderEngine* m_Instance;

	public:
		static IRenderEngine* GetInstance() { return m_Instance; }

	public:
		/*Init*/
		virtual void Initialize(HINSTANCE hinst, HWND hWnd, int ResolutionWidth, int ResolutionHeight) abstract;

		/*unInit*/
		virtual void Finalize() abstract;

		/*Render*/
		virtual void BeginRender() abstract;
		virtual void EndRender() abstract;

		/*Draw*/
		virtual void SetBrushColor(float r, float g, float b, float a) abstract;
		virtual void SetBrushColor(unsigned long RGBColor) abstract;

		virtual void DrawLine(int x1, int y1, int x2, int y2) abstract;

		virtual void DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F color) abstract;
		virtual void DrawRectangle(int x, int y, int x1, int y1, COLORREF Brush) abstract;
		virtual void DrawRectangle(int x, int y, int x1, int y1) abstract;

		virtual void DrawEllipse(int x, int y, int size) abstract;
		virtual void DrawEllipse(int left, int top, int right, int bottom) abstract;

		virtual bool DrawText(int x, int y, const wchar_t* pch, ...) abstract;

		virtual ID2D1HwndRenderTarget* GetRenderTarget() abstract;
	};
}