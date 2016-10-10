/**
 *	@file		Win32Frame.cpp
 *	@brief		Win32フレームに関する処理を行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2016/08/17
 *	@version	1.0
 */

// include
#include "Win32Frame.h"

HWND Win32Frame::m_hwnd = nullptr;

int Win32Frame::Run(Application* pApplication, HINSTANCE hInstance, int nCmdShow)
{
	// Initialize the window class.
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"DXSampleClass";
	RegisterClassEx(&windowClass);

	RECT windowRect = { 0, 0, static_cast<LONG>(pApplication->GetWidth()), static_cast<LONG>(pApplication->GetHeight()) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the window and store a handle to it.
	m_hwnd = CreateWindow(
		windowClass.lpszClassName,
		pApplication->GetTitle(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,		// We have no parent window.
		nullptr,		// We aren't using menus.
		hInstance,
		pApplication);

	// Initialize the sample. OnInit is defined in each child-implementation of DXSample.
	pApplication->OnInit();

	ShowWindow(m_hwnd, nCmdShow);

	// WM_PAINTが呼ばれないようにする
	ValidateRect(m_hwnd, 0);

	// Main sample loop.
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		// Process any messages in the queue.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			pApplication->OnUpdate();
			pApplication->OnRender();
		}
	}

	pApplication->OnDestroy();

	// Return this part of the WM_QUIT message to Windows.
	return static_cast<char>(msg.wParam);
}

// Main message handler for the sample.
LRESULT CALLBACK Win32Frame::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Application* pApplication = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_CREATE:
	{
		// Save the DXSample* passed in to CreateWindow.
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
	}
	return 0;
	case WM_PAINT:
		break;
	case WM_KEYDOWN:
		switch (static_cast<char>(wParam))
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	//case WM_SETCURSOR:
	//	// マウスを消す
	//	ShowCursor(false);
	//	break;
	}

	// Handle any messages the switch statement didn't.
	return DefWindowProc(hWnd, message, wParam, lParam);
}