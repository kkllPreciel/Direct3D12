/**
 *	@file		Vector3D.h
 *	@brief		3次元ベクトルに関するヘッダファイル
 *	@author		kkllPreciel
 *	@date		2017/01/17
 *	@version	1.0
 *  @copyright	(c) 2017, kkllPreciel
 */

// 2重includeの防止
#pragma once

namespace Sein
{
	namespace Math
	{
		// 構造体の宣言
		struct Vector2D;

		/**
		 *	@brief	3次元ベクトル構造体
		 */
		struct Vector3D
		{
			/**
			 *	@brief	コンストラクタ
			 */
			Vector3D();

			/**
			 *	@brief	引数付きコンストラクタ
			 *	@param	x:x成分
			 *	@param	y:y成分
			 *	@param	z:z成分
			 */
			Vector3D(float x, float y, float z);

			/**
			 *	@brief	引数付きコンストラクタ
			 *	@param	vector:2次元ベクトル
			 *	@param	z:z成分
			 */
			Vector3D(const Vector2D& vector, float z);

			/**
			 *	@brief	コピーコンストラクタ
			 *	@param	vector:コピー元のインスタンス
			 */
			Vector3D(const Vector3D& vector);

			/**
			 *	@brief	デストラクタ
			 */
			~Vector3D();

			/**
			 *	@brief	代入演算子
			 *	@param	vector:代入する値
			 *	@return	代入結果
			 */
			Vector3D& operator = (const Vector3D& vector);

			/**
			 *	@brief	加算代入演算子
			 *	@param	vector:加算する値
			 *	@return	加算代入結果
			 */
			Vector3D& operator += (const Vector3D& vector);

			/**
			 *	@brief	減算代入演算子
			 *	@param	vector:減算する値
			 *	@return	減算代入結果
			 */
			Vector3D& operator -= (const Vector3D& vector);

			/**
			 *	@brief	乗算代入演算子
			 *	@param	multiplier:乗算する値
			 *	@return	乗算代入結果
			 */
			Vector3D& operator *= (float multiplier);

			/**
			 *	@brief	除算代入演算子
			 *	@param	divisor:除算する値
			 *	@return	除算代入結果
			 */
			Vector3D& operator /= (float divisor);

			/**
			 *	@brief	加算演算子
			 *	@param	vector:加算する値
			 *	@retun	加算結果
			 */
			Vector3D operator + (const Vector3D& vector) const;

			/**
			 *	@brief	減算演算子
			 *	@param	vector:減算する値
			 *	@return	減算結果
			 */
			Vector3D operator - (const Vector3D& vector) const;

			/**
			 *	@brief	乗算演算子
			 *	@param	multiplier:乗算する値
			 *	@return	乗算結果
			 */
			Vector3D operator * (float multiplier) const;

			/**
			 *	@brief	除算演算子
			 *	@param	divisor:除算する値
			 *	@return	除算結果
			 */
			Vector3D operator / (float divisor) const;

			/**
			 *	@brief	等価比較演算子
			 *	@param	vector:比較する値
			 *	@return	bool。等価ならtrue, 非等価ならfalse
			 */
			bool operator == (const Vector3D& vector) const;

			/**
			 *	@brief	非等価比較演算子
			 *	@param	vector:比較する値
			 *	@return	bool。非等価ならtrue,等価ならfalse
			 */
			bool operator != (const Vector3D& vector) const;

			/**
			 *	@brief	長さを取得する
			 *	@return	長さ
			 */
			float Length() const;

			/**
			 *	@brief	正規化を行う
			 *	@return	正規化結果
			 */
			Vector3D& Normalize();

			/**
			 *	@brief	内積を行う
			 *	@param	vector1:入力ベクトル
			 *	@param	vector2:入力ベクトル
			 *	@return	内積結果
			 */
			static float DotProduct(const Vector3D& vector1, const Vector3D& vector2);

			/**
			 *	@brief	外積を行う
			 *	@param	vector1:入力ベクトル
			 *	@param	vector2:入力ベクトル
			 *	@return	外積結果
			 */
			static Vector3D CrossProduct(const Vector3D& vector1, const Vector3D& vector2);

			// メソッド
			// 零ベクトル
			// 線形補間
			// 各方向(↑↓→←)

			float x; ///< x成分
			float y; ///< y成分
			float z; ///< z成分
		};
	}
}