/**
 *	@file		Application.h
 *	@brief		アプリケーションに関するヘッダファイル
 *	@author		kkllPreciel
 *	@date		2016/10/10
 *	@version	1.0
 */

#pragma once

// include
#include <Windows.h>
#include <string>

/**
 *	@brief	アプリケーションベースクラス
 */
class Application
{
public:
	/**
	 *	@brief	引数付きコンストラクタ
	 *	@param	width:横幅
	 *	@param	height:縦幅
	 *	@param	name:アプリ名
	 */
	Application(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	デストラクタ
	 */
	virtual ~Application();

	/**
	 *	@brief	初期化処理を行う
	 */
	virtual void OnInit() = 0;

	/**
	 *	@brief	更新処理を行う
	 */
	virtual void OnUpdate() = 0;

	/**
	 *	@brief	描画処理を行う
	 */
	virtual void OnRender() = 0;

	/**
	 *	@brief	終了処理を行う
	 */
	virtual void OnDestroy() = 0;

	/**
	 *	@brief	横幅を取得する
	 */
	unsigned int GetWidth() const;

	/**
	 *	@brief	縦幅を取得する
	 */
	unsigned int GetHeight() const;

	/**
	 *	@brief	アスペクト比を取得する
	 */
	float GetAspect() const;

	/**
	 *	@brief	タイトルを取得する
	 */
	const WCHAR* GetTitle() const;

protected:
	/**
	 *	@brief	アセットのフルパスを取得する
	 *	@param	asset_name:フルパスを取得するアセット名
	 *	@return	アセットのフルパス
	 */
	std::wstring GetAssetFullPath(LPCWSTR asset_name);

private:
	/**
	 *	@brief	コンストラクタ
	 */
	Application() = delete;

	/**
	 *	@brief	コピーコンストラクタ
	 *	@param	other:コピー元
	 */
	Application(const Application& other) = delete;

	/**
	 *	@brief	代入演算子オペレータ
	 *	@param	other:代入元
	 */
	Application& operator = (const Application& other) = delete;

	unsigned int	width;			///< 横幅
	unsigned int	height;			///< 縦幅
	float			aspect;			///< アスペクト比
	std::wstring	title;			///< タイトル
	std::wstring	assets_path;	///< アセットパス
};