/**
 *	@file		Application.cpp
 *	@brief		�A�v���P�[�V�����x�[�X�Ɋւ��鏈�����s���v���O�����\�[�X
 *	@author		kkllPreciel
 *	@date		2016/10/10
 *	@version	1.0
 */

// include
#include "Application.h"
#include "Helper.h"

/**
 *	@brief	�����t���R���X�g���N�^
 *	@param	width:����
 *	@param	height:�c��
 *	@param	name:�A�v����
 */
Application::Application(unsigned int width, unsigned int height, std::wstring name) : width(width), height(height), title(name), aspect(static_cast<float>(width) / static_cast<float>(height))
{
	WCHAR assetsPath[512];
	helper::GetAssetsPath(assetsPath, _countof(assetsPath));
	assets_path = assetsPath;
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
 *	@brief	�A�X�y�N�g����擾����
 */
float Application::GetAspect() const
{
	return aspect;
}

/**
 *	@brief	�^�C�g�����擾����
 */
const WCHAR* Application::GetTitle() const
{
	return title.c_str();
}

/**
 *	@brief	�A�Z�b�g�̃t���p�X���擾����
 *	@param	asset_name:�t���p�X���擾����A�Z�b�g��
 *	@return	�A�Z�b�g�̃t���p�X
 */
std::wstring Application::GetAssetFullPath(LPCWSTR asset_name)
{
	return assets_path + asset_name;
}