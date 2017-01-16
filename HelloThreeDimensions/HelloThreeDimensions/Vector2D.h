/**
 *	@file		Vector2D.h
 *	@brief		2次元ベクトルに関するヘッダファイル
 *	@author		kkllPreciel
 *	@date		2017/01/16
 *	@version	1.0
 *  @copyright	(c) 2017, kkllPreciel
 */

// 2重includeの防止
#pragma once

namespace Sein
{
	namespace Math
	{
		/**
		 *	@brief	2次元ベクトル構造体
		 */
		struct Vector2D
		{
		public:
			/**
			 *	@brief	コンストラクタ
			 */
			Vector2D();

			/**
			 *	@brief	引数付きコンストラクタ
			 *	@param	x:x成分
			 *	@param	y:y成分
			 */
			Vector2D(float x, float y);

			/**
			 *	@brief	コピーコンストラクタ
			 *	@param	vector:コピー元のインスタンス
			 */
			explicit Vector2D(const Vector2D& vector);

			/**
			 *	@brief	デストラクタ
			 */
			~Vector2D();

			/**
			 *	@brief	代入演算子
			 *	@param	vector:代入する値
			 *	@return	代入結果
			 */
			Vector2D operator = (const Vector2D& vector);

			/**
			 *	@brief	加算代入演算子
			 *	@param	vector:加算する値
			 *	@return	加算代入結果
			 */
			Vector2D operator += (const Vector2D& vector);

			/**
			 *	@brief	減算代入演算子
			 *	@param	vector:減算する値
			 *	@return	減算代入結果
			 */
			Vector2D operator -= (const Vector2D& vector);

			/**
			 *	@brief	乗算代入演算子
			 *	@param	multiplier:乗数
			 *	@return	乗算代入結果
			 */
			Vector2D operator *= (float multiplier);

			/**
			 *	@brief	除算代入演算子
			 *	@param	divisor:除数
			 *	@return	除算代入結果
			 */
			Vector2D operator /= (float divisor);

			// オペレータ
			// 加算
			// 減算
			// 乗算
			// 除算
			// 比較

			// メソッド
			// 長さ
			// 零ベクトル
			// 正規化
			// 内積
			// 外積
			// 線形補間
			// 比較
			// 各方向(↑↓→←)

			// 
			float x; ///< x成分
			float y; ///< y成分
		};
	}
}