/**
 *	@file		Win32Frame.h
 *	@brief		Win32フレームに関するヘッダファイル
 *	@author		kkllPreciel
 *	@date		2016/08/17
 *	@version	1.0
 */

#pragma once

// include
#include <Windows.h>
#include "Application.h"

class Win32Frame
{
public:
	static int Run(Application* pApplication, HINSTANCE hInstance, int nCmdShow);
	static HWND GetHwnd() { return m_hwnd; }

protected:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static HWND m_hwnd;
};