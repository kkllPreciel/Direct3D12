/**
 *	@file		Application.cpp
 *	@brief		アプリケーションベースに関する処理を行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2016/10/10
 *	@version	1.0
 */

// include
#include "Application.h"
#include "Helper.h"

/**
 *	@brief	引数付きコンストラクタ
 *	@param	width:横幅
 *	@param	height:縦幅
 *	@param	name:アプリ名
 */
Application::Application(unsigned int width, unsigned int height, std::wstring name) : width(width), height(height), title(name), aspect(static_cast<float>(width) / static_cast<float>(height))
{
	WCHAR assetsPath[512];
	helper::GetAssetsPath(assetsPath, _countof(assetsPath));
	assets_path = assetsPath;
}

/**
 *	@brief	デストラクタ
 */
Application::~Application()
{

}

/**
 *	@brief	横幅を取得する
 */
unsigned int Application::GetWidth() const
{
	return width;
}

/**
 *	@brief	縦幅を取得する
 */
unsigned int Application::GetHeight() const
{
	return height;
}

/**
 *	@brief	アスペクト比を取得する
 */
float Application::GetAspect() const
{
	return aspect;
}

/**
 *	@brief	タイトルを取得する
 */
const WCHAR* Application::GetTitle() const
{
	return title.c_str();
}

/**
 *	@brief	アセットのフルパスを取得する
 *	@param	asset_name:フルパスを取得するアセット名
 *	@return	アセットのフルパス
 */
std::wstring Application::GetAssetFullPath(LPCWSTR asset_name)
{
	return assets_path + asset_name;
}