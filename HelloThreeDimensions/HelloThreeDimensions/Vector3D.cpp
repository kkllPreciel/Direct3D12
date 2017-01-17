/**
 *	@file		Vector3D.cpp
 *	@brief		3次元ベクトルに関する処理行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2017/01/17
 *	@version	1.0
 *  @copyright	(c) 2017, kkllPreciel
 */

// include
#include <math.h>
#include <limits>
#include <crtdbg.h>
#include "Vector2D.h"
#include "Vector3D.h"

namespace Sein
{
	namespace Math
	{
		/**
		 *	@brief	コンストラクタ
		 */
		Vector3D::Vector3D()
		{

		}
		
		/**
		 *	@brief	引数付きコンストラクタ
		 *	@param	x:x成分
		 *	@param	y:y成分
		 *	@param	z:z成分
		 */
		Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
		{

		}
		
		/**
		 *	@brief	引数付きコンストラクタ
		 *	@param	vector:2次元ベクトル
		 *	@param	z:z成分
		 */
		Vector3D::Vector3D(const Vector2D& vector, float z) : x(vector.x), y(vector.y), z(z)
		{

		}
		
		/**
		 *	@brief	コピーコンストラクタ
		 *	@param	vector:コピー元のインスタンス
		 */
		Vector3D::Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z)
		{

		}
		
		/**
		 *	@brief	デストラクタ
		 */
		Vector3D::~Vector3D()
		{

		}
		
		/**
		 *	@brief	代入演算子
		 *	@param	vector:代入する値
		 *	@return	代入結果
		 */
		Vector3D& Vector3D::operator = (const Vector3D& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;

			return *this;
		}

		/**
		 *	@brief	加算代入演算子
		 *	@param	vector:加算する値
		 *	@return	加算代入結果
		 */
		Vector3D& Vector3D::operator += (const Vector3D& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;

			return *this;
		}

		/**
		 *	@brief	減算代入演算子
		 *	@param	vector:減算する値
		 *	@return	減算代入結果
		 */
		Vector3D& Vector3D::operator -= (const Vector3D& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;

			return *this;
		}

		/**
		 *	@brief	乗算代入演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算代入結果
		 */
		Vector3D& Vector3D::operator *= (float multiplier)
		{
			x *= multiplier;
			y *= multiplier;
			z *= multiplier;

			return *this;
		}

		/**
		 *	@brief	除算代入演算子
		 *	@param	divisor:除算する値
		 *	@return	除算代入結果
		 */
		Vector3D& Vector3D::operator /= (float divisor)
		{
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor && "division by zero.(Vector3D::operator/=)");
#endif;
			x /= divisor;
			y /= divisor;
			z /= divisor;

			return *this;
		}

		/**
		 *	@brief	加算演算子
		 *	@param	vector:加算する値
		 *	@retun	加算結果
		 */
		Vector3D Vector3D::operator + (const Vector3D& vector) const
		{
			return Vector3D(x + vector.x, y + vector.y, z + vector.z);
		}

		/**
		 *	@brief	減算演算子
		 *	@param	vector:減算する値
		 *	@return	減算結果
		 */
		Vector3D Vector3D::operator - (const Vector3D& vector) const
		{
			return Vector3D(x - vector.x, y - vector.y, z - vector.z);
		}

		/**
		 *	@brief	乗算演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算結果
		 */
		Vector3D Vector3D::operator * (float multiplier) const
		{
			return Vector3D(x * multiplier, y * multiplier, z * multiplier);
		}

		/**
		 *	@brief	除算演算子
		 *	@param	divisor:除算する値
		 *	@return	除算結果
		 */
		Vector3D Vector3D::operator / (float divisor) const
		{
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor && "division by zero.(Vector3D::operator/)");
#endif;
			return Vector3D(x / divisor, y / divisor, z / divisor);
		}

		/**
		 *	@brief	等価比較演算子
		 *	@param	vector:比較する値
		 *	@return	bool。等価ならtrue, 非等価ならfalse
		 */
		bool Vector3D::operator == (const Vector3D& vector) const
		{
			// 差分がepsilonより小さい
			return fabsf(x - vector.x) <= std::numeric_limits<float>::epsilon()
				&& fabsf(y - vector.y) <= std::numeric_limits<float>::epsilon()
				&& fabsf(z - vector.z) <= std::numeric_limits<float>::epsilon();
		}

		/**
		 *	@brief	非等価比較演算子
		 *	@param	vector:比較する値
		 *	@return	bool。非等価ならtrue,等価ならfalse
		 */
		bool Vector3D::operator != (const Vector3D& vector) const
		{
			// 差分がepsilonより大きい
			return std::numeric_limits<float>::epsilon() < fabsf(x - vector.x)
				|| std::numeric_limits<float>::epsilon() < fabsf(y - vector.y)
				|| std::numeric_limits<float>::epsilon() < fabsf(z - vector.z);
		}

		/**
		 *	@brief	長さを取得する
		 *	@return	長さ
		 */
		float Vector3D::Length() const
		{
			return sqrtf(x * x + y * y + z * z);
		}
		
		/**
		 *	@brief	正規化を行う
		 *	@return	正規化結果
		 */
		Vector3D& Vector3D::Normalize()
		{
			float fLength = Length();
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= fLength && "division by zero.(Vector3D::Normalize)");
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
		float Vector3D::DotProduct(const Vector3D& vector1, const Vector3D& vector2)
		{
			// 内積は各要素の掛け算の和
			return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
		}
		
		/**
		 *	@brief	外積を行う
		 *	@param	vector1:入力ベクトル
		 *	@param	vector2:入力ベクトル
		 *	@return	外積結果
		 */
		Vector3D Vector3D::CrossProduct(const Vector3D& vector1, const Vector3D& vector2)
		{
			return Vector3D(
				vector1.y * vector2.z - vector1.z * vector2.y,
				vector1.z * vector2.x - vector1.x * vector2.z,
				vector1.x * vector2.y - vector1.y * vector2.x
			);
		}
	}
}