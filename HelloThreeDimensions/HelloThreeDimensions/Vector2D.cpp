/**
 *	@file		Vector2D.cpp
 *	@brief		2次元ベクトルに関する処理行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2017/01/17
 *	@version	1.0
 *  @copyright	(c) 2015, kkllPreciel
 */

// include
#include <math.h>
#include <limits>
#include <crtdbg.h>
#include "Vector2D.h"

namespace Sein
{
	namespace Math
	{
		/**
		 *	@brief	コンストラクタ
		 */
		Vector2D::Vector2D()
		{
		
		}
		
		/**
		 *	@brief	引数付きコンストラクタ
		 *	@param	x:x成分
		 *	@param	y:y成分
		 */
		Vector2D::Vector2D(float x, float y) : x(x), y(y)
		{
		
		}
		
		/**
		 *	@brief	コピーコンストラクタ
		 *	@param	vector:コピー元のインスタンス
		 */
		Vector2D::Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y)
		{
		
		}
		
		/**
		 *	@brief	デストラクタ
		 */
		Vector2D::~Vector2D()
		{
		
		}
		
		/**
		 *	@brief	代入演算子
		 *	@param	vector:代入する値
		 *	@return	代入結果
		 */
		Vector2D& Vector2D::operator = (const Vector2D& vector)
		{
			x = vector.x;
			y = vector.y;
		
			return *this;
		}
		
		/**
		 *	@brief	加算代入演算子
		 *	@param	vector:加算する値
		 *	@return	加算代入結果
		 */
		Vector2D& Vector2D::operator += (const Vector2D& vector)
		{
			x += vector.x;
			y += vector.y;
		
			return *this;
		}
		
		/**
		 *	@brief	減算代入演算子
		 *	@param	vector:減算する値
		 *	@return	減算代入結果
		 */
		Vector2D& Vector2D::operator -= (const Vector2D& vector)
		{
			x -= vector.x;
			y -= vector.y;
		
			return *this;
		}
		
		/**
		 *	@brief	乗算代入演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算代入結果
		 */
		Vector2D& Vector2D::operator *= (float multiplier)
		{
			x *= multiplier;
			y *= multiplier;
		
			return *this;
		}
		
		/**
		 *	@brief	除算代入演算子
		 *	@param	divisor:除算する値
		 *	@return	除算代入結果
		 */
		Vector2D& Vector2D::operator /= (float divisor)
		{
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor);
#endif;
			x /= divisor;
			y /= divisor;

			return *this;
		}

		/**
		 *	@brief	加算演算子
		 *	@param	vector:加算する値
		 *	@retun	加算結果
		 */
		Vector2D Vector2D::operator + (const Vector2D& vector) const
		{
			return Vector2D(x + vector.x, y + vector.y);
		}

		/**
		 *	@brief	減算演算子
		 *	@param	vector:減算する値
		 *	@return	減算結果
		 */
		Vector2D Vector2D::operator - (const Vector2D& vector) const
		{
			return Vector2D(x - vector.x, y - vector.y);
		}

		/**
		 *	@brief	乗算演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算結果
		 */
		Vector2D Vector2D::operator * (float multiplier) const
		{
			return Vector2D(x * multiplier, y * multiplier);
		}

		/**
		 *	@brief	除算演算子
		 *	@param	divisor:除算する値
		 *	@return	除算結果
		 */
		Vector2D Vector2D::operator / (float divisor) const
		{
#ifdef _DEBUG
				_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor);
#endif;
			return Vector2D(x / divisor, y / divisor);
		}

		/**
		 *	@brief	等価比較演算子
		 *	@param	vector:比較する値
		 *	@return	bool。等価ならtrue, 非等価ならfalse
		 */
		bool Vector2D::operator == (const Vector2D& vector) const
		{
			// 差分がepsilonより小さい
			return fabsf(x - vector.x) <= std::numeric_limits<float>::epsilon()
				&& fabsf(y - vector.y) <= std::numeric_limits<float>::epsilon();
		}

		/**
		 *	@brief	非等価比較演算子
		 *	@param	vector:比較する値
		 *	@return	bool。非等価ならtrue,等価ならfalse
		 */
		bool Vector2D::operator != (const Vector2D& vector) const
		{
			// 差分がepsilonより大きい
			return std::numeric_limits<float>::epsilon() < fabsf(x - vector.x)
				|| std::numeric_limits<float>::epsilon() < fabsf(y - vector.y);
		}

		/**
		 *	@brief	長さを取得する
		 *	@return	長さ
		 */
		float Vector2D::Length() const
		{
			return sqrtf(x * x + y * y);
		}

		/**
		 *	@brief	正規化を行う
		 *	@return	正規化結果
		 */
		Vector2D& Vector2D::Normalize()
		{
			float fLength = Length();
#ifdef _DEBUG
				_ASSERTE(std::numeric_limits<float>::epsilon() <= fLength && "正規化に失敗しました。(CVector2D::Normalize)");
#endif;
			x /= fLength;
			y /= fLength;

			return *this;
		}

		/**
		 *	@brief	内積を行う
		 *	@param	vector1:入力ベクトル
		 *	@param	vector2:入力ベクトル
		 *	@return	内積結果
		 */
		float Vector2D::DotProduct(const Vector2D& vector1, const Vector2D& vector2)
		{
			// 内積は各要素の掛け算の和
			return vector1.x * vector2.x + vector1.y * vector2.y;
		}

		/**
		 *	@brief	外積を行う
		 *	@param	vector1:入力ベクトル
		 *	@param	vector2:入力ベクトル
		 *	@return	外積結果
		 */
		float Vector2D::CrossProduct(const Vector2D& vector1, const Vector2D& vector2)
		{
			return vector1.x * vector2.y - vector1.y * vector2.x;
		}
	}
}