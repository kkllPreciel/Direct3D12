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
		 *	@brief	引数付きコンストラクタ
		 *	@param	m11:1行1列の値
		 *	@param	m12:1行2列の値
		 *	@param	m13:1行3列の値
		 *	@param	m14:1行4列の値
		 *	@param	m21:2行1列の値
		 *	@param	m22:2行2列の値
		 *	@param	m23:2行3列の値
		 *	@param	m24:2行4列の値
		 *	@param	m31:3行1列の値
		 *	@param	m32:3行2列の値
		 *	@param	m33:3行3列の値
		 *	@param	m34:3行4列の値
		 *	@param	m41:4行1列の値
		 *	@param	m42:4行2列の値
		 *	@param	m43:4行3列の値
		 *	@param	m44:4行4列の値
		 */
		Matrix::Matrix(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			_11 = m11; _12 = m12; _13 = m13; _14 = m14;
			_21 = m21; _22 = m22; _23 = m23; _24 = m24;
			_31 = m31; _32 = m32; _33 = m33; _34 = m34;
			_41 = m41; _42 = m42; _43 = m43; _44 = m44;
		}
		
		/**
		 *	@brief	コピーコンストラクタ
		 *	@param	matrix:コピー元のインスタンス
		 */
		Matrix::Matrix(const Matrix& matrix)
		{
			_11 = matrix._11; _12 = matrix._12; _13 = matrix._13; _14 = matrix._14;
			_21 = matrix._21; _22 = matrix._22; _23 = matrix._23; _24 = matrix._24;
			_31 = matrix._31; _32 = matrix._32; _33 = matrix._33; _34 = matrix._34;
			_41 = matrix._41; _42 = matrix._42; _43 = matrix._43; _44 = matrix._44;
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
			// TODO:memcpy
			_11 = matrix._11; _12 = matrix._12; _13 = matrix._13; _14 = matrix._14;
			_21 = matrix._21; _22 = matrix._22; _23 = matrix._23; _24 = matrix._24;
			_31 = matrix._31; _32 = matrix._32; _33 = matrix._33; _34 = matrix._34;
			_41 = matrix._41; _42 = matrix._42; _43 = matrix._43; _44 = matrix._44;

			return *this;
		}
		
		/**
		 *	@brief	加算代入演算子
		 *	@param	matrix:加算する値
		 *	@return	加算代入結果
		 */
		Matrix& Matrix::operator += (const Matrix& matrix)
		{
			_11 += matrix._11; _12 += matrix._12; _13 += matrix._13; _14 += matrix._14;
			_21 += matrix._21; _22 += matrix._22; _23 += matrix._23; _24 += matrix._24;
			_31 += matrix._31; _32 += matrix._32; _33 += matrix._33; _34 += matrix._34;
			_41 += matrix._41; _42 += matrix._42; _43 += matrix._43; _44 += matrix._44;
		
			return *this;
		}
		
		/**
		 *	@brief	減算代入演算子
		 *	@param	matrix:減算する値
		 *	@return	減算代入結果
		 */
		Matrix& Matrix::operator -= (const Matrix& matrix)
		{
			_11 -= matrix._11; _12 -= matrix._12; _13 -= matrix._13; _14 -= matrix._14;
			_21 -= matrix._21; _22 -= matrix._22; _23 -= matrix._23; _24 -= matrix._24;
			_31 -= matrix._31; _32 -= matrix._32; _33 -= matrix._33; _34 -= matrix._34;
			_41 -= matrix._41; _42 -= matrix._42; _43 -= matrix._43; _44 -= matrix._44;
		
			return *this;
		}
		
		/**
		 *	@brief	乗算代入演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算代入結果
		 */
		Matrix& Matrix::operator *= (float multiplier)
		{
			_11 *= multiplier; _12 *= multiplier; _13 *= multiplier; _14 *= multiplier;
			_21 *= multiplier; _22 *= multiplier; _23 *= multiplier; _24 *= multiplier;
			_31 *= multiplier; _32 *= multiplier; _33 *= multiplier; _34 *= multiplier;
			_41 *= multiplier; _42 *= multiplier; _43 *= multiplier; _44 *= multiplier;
		
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

			_11 /= divisor; _12 /= divisor; _13 /= divisor; _14 /= divisor;
			_21 /= divisor; _22 /= divisor; _23 /= divisor; _24 /= divisor;
			_31 /= divisor; _32 /= divisor; _33 /= divisor; _34 /= divisor;
			_41 /= divisor; _42 /= divisor; _43 /= divisor; _44 /= divisor;

			return *this;
		}

		/**
		 *	@brief	加算演算子
		 *	@param	matrix:加算する値
		 *	@retun	加算結果
		 */
		Matrix Matrix::operator + (const Matrix& matrix) const
		{
			return Matrix(
				_11 + matrix._11, _12 + matrix._12, _13 + matrix._13, _14 + matrix._14,
				_21 + matrix._21, _22 + matrix._22, _23 + matrix._23, _24 + matrix._24,
				_31 + matrix._31, _32 + matrix._32, _33 + matrix._33, _34 + matrix._34,
				_41 + matrix._41, _42 + matrix._42, _43 + matrix._43, _44 + matrix._44 );
		}

		/**
		 *	@brief	減算演算子
		 *	@param	matrix:減算する値
		 *	@return	減算結果
		 */
		Matrix Matrix::operator - (const Matrix& matrix) const
		{
			return Matrix(
				_11 - matrix._11, _12 - matrix._12, _13 - matrix._13, _14 - matrix._14,
				_21 - matrix._21, _22 - matrix._22, _23 - matrix._23, _24 - matrix._24,
				_31 - matrix._31, _32 - matrix._32, _33 - matrix._33, _34 - matrix._34,
				_41 - matrix._41, _42 - matrix._42, _43 - matrix._43, _44 - matrix._44);
		}

		/**
		 *	@brief	乗算演算子
		 *	@param	multiplier:乗算する値
		 *	@return	乗算結果
		 */
		Matrix Matrix::operator * (float multiplier) const
		{
			return Matrix(
				_11 * multiplier, _12 * multiplier, _13 * multiplier, _14 * multiplier,
				_21 * multiplier, _22 * multiplier, _23 * multiplier, _24 * multiplier,
				_31 * multiplier, _32 * multiplier, _33 * multiplier, _34 * multiplier,
				_41 * multiplier, _42 * multiplier, _43 * multiplier, _44 * multiplier);
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
			return Matrix(
				_11 * divisor, _12 * divisor, _13 * divisor, _14 * divisor,
				_21 * divisor, _22 * divisor, _23 * divisor, _24 * divisor,
				_31 * divisor, _32 * divisor, _33 * divisor, _34 * divisor,
				_41 * divisor, _42 * divisor, _43 * divisor, _44 * divisor);
		}

		/**
		 *	@brief	等価比較演算子
		 *	@param	matrix:比較する値
		 *	@return	bool。等価ならtrue, 非等価ならfalse
		 */
		bool Matrix::operator == (const Matrix& matrix) const
		{
			// メモリ単位で比較
			return (0 == memcmp(this, &matrix, sizeof(Matrix)));
		}

		/**
		 *	@brief	非等価比較演算子
		 *	@param	matrix:比較する値
		 *	@return	bool。非等価ならtrue,等価ならfalse
		 */
		bool Matrix::operator != (const Matrix& matrix) const
		{
			// メモリ単位で比較
			return (0 != memcmp(this, &matrix, sizeof(Matrix)));
		}

		/**
		 *	@brief	左手系のビュー行列を作成する
		 *	@param	eye:カメラの座標
		 *	@param	lookat:カメラの注視点
		 *	@param	up:カメラの向き(上方向)
		 *	@return	ビュー行列
		 */
		Matrix Matrix::CreateLookAtLeftHanded(const Vector3D& eye, const Vector3D& lookat, const Vector3D& up);
		
		/**
		 *	@brief	左手系の透視投影行列を作成する
		 *	@param	fovy:Y方向の視野角 (ラジアン単位)
		 *	@param	aspect:アスペクト比
		 *	@param	near:ニアクリップ
		 *	@param	far:ファークリップ
		 *	@return	透視投影行列
		 */
		Matrix Matrix::CreatePerspectiveLeftHanded(float fovy, float aspect, float near, float far);
		
		/**
		 *	@brief	左手系の正射影(平行投影)行列を作成する
		 *	@param	width:ビューボリュームの幅
		 *	@param	height:ビューボリュームの高さ
		 *	@param	near:ニアクリップ
		 *	@param	far:ファークリップ
		 *	@return	正射影行列
		 */
		Matrix Matrix::CreateOrthographicLeftHanded(float width, float height, float near, float far);
		
		/**
		 *	@brief	X軸の回転行列を作成する
		 *	@param	angle:回転角度(ラジアン)
		 *	@return	回転行列
		 */
		Matrix Matrix::RotationX(float angle);
		
		/**
		 *	@brief	Y軸の回転行列を作成する
		 *	@param	angle:回転角度(ラジアン)
		 *	@return	回転行列
		 */
		Matrix Matrix::RotationY(float angle);
		
		/**
		 *	@brief	Z軸の回転行列を作成する
		 *	@param	angle:回転角度(ラジアン)
		 *	@return	回転行列
		 */
		Matrix Matrix::RotationZ(float angle);
		
		/**
		 *	@brief	平行移動行列を作成する
		 *	@param	x:X成分
		 *	@param	y:Y成分
		 *	@param	z:Z成分
		 *	@return	平行移動行列
		 */
		Matrix Matrix::Translation(float x, float y, float z)
		{
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				   x,    y,    z, 1.0f);
		}
		
		/**
		 *	@brief	平行移動行列を作成する
		 *	@param	position:ベクトル
		 *	@return	平行移動行列
		 */
		Matrix Matrix::Translation(const Vector3D& position)
		{
			return Translation(position.x, position.y, position.z);
		}
		
		/**
		 *	@brief	単位行列化する
		 */
		Matrix& Matrix::Identity()
		{
			_11 = _22 = _33 = _44 = 1.0f;

			_12 = _13 = _14 =
			_21 = _23 = _24 =
			_31 = _32 = _34 =
			_41 = _42 = _43 = 0.0f;

			return *this;
		}
		
		/**
		 *	@brief	単位行列を作成する
		 *	@return	単位行列
		 */
		Matrix Matrix::CreateIdentity()
		{
			return Matrix(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 *	@brief 転置を行う
		 */
		void Matrix::Transpose()
		{
			// *this = Matrix::Transpose();
		}
		
		/**
		 *	@brief	転置行列を作成する
		 *	@return	転置行列
		 */
		Matrix Matrix::Transpose() const
		{
			return Matrix(
				_11, _21, _31, _41,
				_12, _22, _32, _42,
				_13, _23, _33, _43,
				_14, _24, _34, _44 );
		}
	}
}