/**
 *	@file		Matrix.cpp
 *	@brief		行列に関する処理行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2017/01/19
 *	@version	1.0
 *  @copyright	(c) 2017, kkllPreciel
 */

// include
#include <math.h>
#include <limits>
#include <crtdbg.h>
#include "Vector3D.h"
#include "Matrix.h"

namespace Sein
{
	namespace Math
	{
		/**
		 *	@brief	コンストラクタ
		 */
		Matrix::Matrix()
		{
		
		}
		
		/**
		 *	@brief	コピーコンストラクタ
		 *	@param	matrix:コピー元のインスタンス
		 */
		Matrix::Matrix(const Matrix& matrix)
		{
			_11 = matrix._11; _21 = matrix._21; _31 = matrix._31; _41 = matrix._41;
			_12 = matrix._12; _22 = matrix._22; _32 = matrix._32; _42 = matrix._42;
			_13 = matrix._13; _23 = matrix._23; _33 = matrix._33; _43 = matrix._43;
			_14 = matrix._14; _24 = matrix._24; _34 = matrix._34; _44 = matrix._44;
		}
		
		/**
		 *	@brief	デストラクタ
		 */
		Matrix::~Matrix()
		{
		
		}
		
		/**
		 *	@brief	代入演算子
		 *	@param	matrix:代入する値
		 *	@return	代入結果
		 */
		Matrix& Matrix::operator = (const Matrix& matrix)
		{
			_11 = matrix._11; _21 = matrix._21; _31 = matrix._31; _41 = matrix._41;
			_12 = matrix._12; _22 = matrix._22; _32 = matrix._32; _42 = matrix._42;
			_13 = matrix._13; _23 = matrix._23; _33 = matrix._33; _43 = matrix._43;
			_14 = matrix._14; _24 = matrix._24; _34 = matrix._34; _44 = matrix._44;

			return *this;
		}
		
		/**
		 *	@brief	加算代入演算子
		 *	@param	matrix:加算する値
		 *	@return	加算代入結果
		 */
		Matrix& Matrix::operator += (const Matrix& matrix)
		{
			_11 += matrix._11; _21 += matrix._21; _31 += matrix._31; _41 += matrix._41;
			_12 += matrix._12; _22 += matrix._22; _32 += matrix._32; _42 += matrix._42;
			_13 += matrix._13; _23 += matrix._23; _33 += matrix._33; _43 += matrix._43;
			_14 += matrix._14; _24 += matrix._24; _34 += matrix._34; _44 += matrix._44;
		
			return *this;
		}
		
		/**
		 *	@brief	減算代入演算子
		 *	@param	matrix:減算する値
		 *	@return	減算代入結果
		 */
		Matrix& Matrix::operator -= (const Matrix& matrix)
		{
			_11 -= matrix._11; _21 -= matrix._21; _31 -= matrix._31; _41 -= matrix._41;
			_12 -= matrix._12; _22 -= matrix._22; _32 -= matrix._32; _42 -= matrix._42;
			_13 -= matrix._13; _23 -= matrix._23; _33 -= matrix._33; _43 -= matrix._43;
			_14 -= matrix._14; _24 -= matrix._24; _34 -= matrix._34; _44 -= matrix._44;
		
			return *this;
		}
		
		/**
		 *	@brief	乗算代入演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算代入結果
		 */
		Matrix& Matrix::operator *= (float multiplier)
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
		Matrix& Matrix::operator /= (float divisor)
		{
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor && "division by zero.(Matrix::operator/=)");
#endif;
			x /= divisor;
			y /= divisor;

			return *this;
		}

		/**
		 *	@brief	加算演算子
		 *	@param	matrix:加算する値
		 *	@retun	加算結果
		 */
		Matrix Matrix::operator + (const Matrix& matrix) const
		{
			return Matrix(x + matrix.x, y + matrix.y);
		}

		/**
		 *	@brief	減算演算子
		 *	@param	matrix:減算する値
		 *	@return	減算結果
		 */
		Matrix Matrix::operator - (const Matrix& matrix) const
		{
			return Matrix(x - matrix.x, y - matrix.y);
		}

		/**
		 *	@brief	乗算演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算結果
		 */
		Matrix Matrix::operator * (float multiplier) const
		{
			return Matrix(x * multiplier, y * multiplier);
		}

		/**
		 *	@brief	除算演算子
		 *	@param	divisor:除算する値
		 *	@return	除算結果
		 */
		Matrix Matrix::operator / (float divisor) const
		{
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor && "division by zero.(Matrix::operator/)");
#endif;
			return Matrix(x / divisor, y / divisor);
		}

		/**
		 *	@brief	等価比較演算子
		 *	@param	matrix:比較する値
		 *	@return	bool。等価ならtrue, 非等価ならfalse
		 */
		bool Matrix::operator == (const Matrix& matrix) const
		{
			// 差分がepsilonより小さい
			return fabsf(x - matrix.x) <= std::numeric_limits<float>::epsilon()
				&& fabsf(y - matrix.y) <= std::numeric_limits<float>::epsilon();
		}

		/**
		 *	@brief	非等価比較演算子
		 *	@param	matrix:比較する値
		 *	@return	bool。非等価ならtrue,等価ならfalse
		 */
		bool Matrix::operator != (const Matrix& matrix) const
		{
			// 差分がepsilonより大きい
			return std::numeric_limits<float>::epsilon() < fabsf(x - matrix.x)
				|| std::numeric_limits<float>::epsilon() < fabsf(y - matrix.y);
		}

		/**
		 *	@brief	長さを取得する
		 *	@return	長さ
		 */
		float Matrix::Length() const
		{
			return sqrtf(x * x + y * y);
		}

		/**
		 *	@brief	正規化を行う
		 *	@return	正規化結果
		 */
		Matrix& Matrix::Normalize()
		{
			float fLength = Length();
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= fLength && "division by zero.(Matrix::Normalize)");				
#endif;
			x /= fLength;
			y /= fLength;

			return *this;
		}

		/**
		 *	@brief	内積を行う
		 *	@param	matrix1:入力ベクトル
		 *	@param	matrix2:入力ベクトル
		 *	@return	内積結果
		 */
		float Matrix::DotProduct(const Matrix& matrix1, const Matrix& matrix2)
		{
			// 内積は各要素の掛け算の和
			return matrix1.x * matrix2.x + matrix1.y * matrix2.y;
		}

		/**
		 *	@brief	外積を行う
		 *	@param	matrix1:入力ベクトル
		 *	@param	matrix2:入力ベクトル
		 *	@return	外積結果
		 */
		float Matrix::CrossProduct(const Matrix& matrix1, const Matrix& matrix2)
		{
			return matrix1.x * matrix2.y - matrix1.y * matrix2.x;
		}
	}
}