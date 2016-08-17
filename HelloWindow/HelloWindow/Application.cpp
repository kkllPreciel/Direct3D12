/**
 *	@file		Application.cpp
 *	@brief		アプリケーションベースに関する処理を行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2016/08/17
 *	@version	1.0
 */

// include
#include "Application.h"

/**
 *	@brief	引数付きコンストラクタ
 *	@param	width:横幅
 *	@param	height:縦幅
 *	@param	name:アプリ名
 */
Application::Application(unsigned int width, unsigned int height, std::wstring name) : width(width), height(height), title(name)
{

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
 *	@brief	タイトルを取得する
 */
const WCHAR* Application::GetTitle() const
{
	return title.c_str();
}