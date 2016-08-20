/**
 *	@file		Main.cpp
 *	@brief		アプリに関する処理を行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2016/08/17
 *	@version	1.0
 */

// include
#include <Windows.h>
#include "Win32Frame.h"
#include "HelloWindow.h"

// デバッグ用(メモリリーク)
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

// デバッグモード用include
#include <stdlib.h>
#include <crtdbg.h>

// 特定の警告の無視
#pragma warning ( disable : 4996 )
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// マクロ( M_PI使用の為 )
#define _USE_MATH_DEFINES

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
#ifdef _CRTDBG_MAP_ALLOC
	// メモリリークを検出させる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	HelloWindow sample(1280, 720, L"HelloWindow");
	return Win32Frame::Run(&sample, hInstance, nCmdShow);
}