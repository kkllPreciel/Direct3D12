/**
 *	@file		Application.cpp
 *	@brief		�A�v���P�[�V�����x�[�X�Ɋւ��鏈�����s���v���O�����\�[�X
 *	@author		kkllPreciel
 *	@date		2016/08/17
 *	@version	1.0
 */

// include
#include "Application.h"

/**
 *	@brief	�����t���R���X�g���N�^
 *	@param	width:����
 *	@param	height:�c��
 *	@param	name:�A�v����
 */
Application::Application(unsigned int width, unsigned int height, std::wstring name) : width(width), height(height), title(name)
{

}

/**
 *	@brief	�f�X�g���N�^
 */
Application::~Application()
{

}

/**
 *	@brief	�������擾����
 */
unsigned int Application::GetWidth() const
{
	return width;
}

/**
 *	@brief	�c�����擾����
 */
unsigned int Application::GetHeight() const
{
	return height;
}

/**
 *	@brief	�^�C�g�����擾����
 */
const WCHAR* Application::GetTitle() const
{
	return title.c_str();
}