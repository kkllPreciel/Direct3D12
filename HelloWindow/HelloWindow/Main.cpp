/**
 *	@file		Main.cpp
 *	@brief		�A�v���Ɋւ��鏈�����s���v���O�����\�[�X
 *	@author		kkllPreciel
 *	@date		2016/08/17
 *	@version	1.0
 */

// include
#include <Windows.h>
#include "Win32Frame.h"
#include "HelloWindow.h"

// �f�o�b�O�p(���������[�N)
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

// �f�o�b�O���[�h�pinclude
#include <stdlib.h>
#include <crtdbg.h>

// ����̌x���̖���
#pragma warning ( disable : 4996 )
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// �}�N��( M_PI�g�p�̈� )
#define _USE_MATH_DEFINES

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
#ifdef _CRTDBG_MAP_ALLOC
	// ���������[�N�����o������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	HelloWindow sample(1280, 720, L"HelloWindow");
	return Win32Frame::Run(&sample, hInstance, nCmdShow);
}