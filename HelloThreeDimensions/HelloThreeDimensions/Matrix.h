/**
 *	@file		Matrix.h
 *	@brief		行列に関するヘッダファイル
 *	@author		kkllPreciel
 *	@date		2017/01/19
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
		struct Vector3D;

		/**
		 *	@brief	行列構造体
		 *
		 *	列優先行列です。
		 */
		struct Matrix
		{
			/**
			 *	@brief	コンストラクタ
			 */
			Matrix();

			/**
			 *	@brief	コピーコンストラクタ
			 *	@param	matrix:コピー元のインスタンス
			 */
			Matrix(const Matrix& matrix);

			/**
			 *	@brief	デストラクタ
			 */
			~Matrix();

			/**
			 *	@brief	代入演算子
			 *	@param	matrix:代入する値
			 *	@return	代入結果
			 */
			Matrix& operator = (const Matrix& matrix);

			/**
			 *	@brief	代入演算子
			 *	@param	matrix:代入する値
			 *	@return	代入結果
			 */
			Matrix& operator = (const Matrix& matrix);

			/**
			 *	@brief	加算代入演算子
			 *	@param	matrix:加算する値
			 *	@return	加算代入結果
			 */
			Matrix& operator += (const Matrix& matrix);

			/**
			 *	@brief	減算代入演算子
			 *	@param	matrix:減算する値
			 *	@return	減算代入結果
			 */
			Matrix& operator -= (const Matrix& matrix);

			/**
			 *	@brief	乗算代入演算子
			 *	@param	multiplier:乗算する値
			 *	@return	乗算代入結果
			 */
			Matrix& operator *= (float multiplier);

			/**
			 *	@brief	除算代入演算子
			 *	@param	divisor:除算する値
			 *	@return	除算代入結果
			 */
			Matrix& operator /= (float divisor);

			/**
			 *	@brief	加算演算子
			 *	@param	matrix:加算する値
			 *	@retun	加算結果
			 */
			Matrix operator + (const Matrix& matrix) const;

			/**
			 *	@brief	減算演算子
			 *	@param	matrix:減算する値
			 *	@return	減算結果
			 */
			Matrix operator - (const Matrix& matrix) const;

			/**
			 *	@brief	乗算演算子
			 *	@param	multiplier:乗算する値
			 *	@return	乗算結果
			 */
			Matrix operator * (float multiplier) const;

			/**
			 *	@brief	除算演算子
			 *	@param	divisor:除算する値
			 *	@return	除算結果
			 */
			Matrix operator / (float divisor) const;

			/**
			 *	@brief	等価比較演算子
			 *	@param	matrix:比較する値
			 *	@return	bool。等価ならtrue, 非等価ならfalse
			 */
			bool operator == (const Matrix& matrix) const;

			/**
			 *	@brief	非等価比較演算子
			 *	@param	matrix:比較する値
			 *	@return	bool。非等価ならtrue,等価ならfalse
			 */
			bool operator != (const Matrix& matrix) const;

			/**
			 *	@brief	左手系のビュー行列を作成する
			 *	@param	eye:カメラの座標
			 *	@param	lookat:カメラの注視点
			 *	@param	up:カメラの向き(上方向)
			 *	@return	ビュー行列
			 */
			Matrix CreateLookAtLeftHanded(const Vector3D& eye, const Vector3D& lookat, const Vector3D& up);
		
			/**
			 *	@brief	左手系の透視投影行列を作成する
			 *	@param	fovy:Y方向の視野角 (ラジアン単位)
			 *	@param	aspect:アスペクト比
			 *	@param	near:ニアクリップ
			 *	@param	far:ファークリップ
			 *	@return	透視投影行列
			 */
			Matrix CreatePerspectiveLeftHanded(float fovy, float aspect, float near, float far);
		
			/**
			 *	@brief	左手系の正射影(平行投影)行列を作成する
			 *	@param	width:ビューボリュームの幅
			 *	@param	height:ビューボリュームの高さ
			 *	@param	near:ニアクリップ
			 *	@param	far:ファークリップ
			 *	@return	正射影行列
			 */
			Matrix CreateOrthographicLeftHanded(float width, float height, float near, float far);
		
			/**
			 *	@brief	X軸の回転行列を作成する
			 *	@param	angle:回転角度(ラジアン)
			 *	@return	回転行列
			 */
			Matrix RotationX(float angle);
		
			/**
			 *	@brief	Y軸の回転行列を作成する
			 *	@param	angle:回転角度(ラジアン)
			 *	@return	回転行列
			 */
			Matrix RotationY(float angle);
		
			/**
			 *	@brief	Z軸の回転行列を作成する
			 *	@param	angle:回転角度(ラジアン)
			 *	@return	回転行列
			 */
			Matrix RotationZ(float angle);
		
			/**
			 *	@brief	平行移動行列を作成する
			 *	@param	x:X成分
			 *	@param	y:Y成分
			 *	@param	z:Z成分
			 *	@return	平行移動行列
			 */
			Matrix Translation(float x, float y, float z);
		
			/**
			 *	@brief	平行移動行列を作成する
			 *	@param	position:ベクトル
			 *	@return	平行移動行列
			 */
			Matrix Translation(const Vector3D& position);

			/**
			 *	@brief	単位行列化する
			 */
			Matrix& Identity();

			/**
			 *	@brief	単位行列を作成する
			 *	@return	単位行列
			 */
			Matrix CreateIdentity();

			/**
			 *	@brief	転置行列を作成する
			 *	@return	転置行列
			 */
			Matrix Transpose() const;

			/**
			 *	@brief 転置を行う
			 */
			void Transpose();

			union
			{
				struct
				{
					float _11, _21, _31, _41;
					float _12, _22, _32, _42;
					float _13, _23, _33, _43;
					float _14, _24, _34, _44;
				};
				float m[4][4];
			};

		};
	}
}