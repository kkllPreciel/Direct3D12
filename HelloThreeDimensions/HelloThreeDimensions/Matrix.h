/**
 *	@file		Matrix.h
 *	@brief		�s��Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2017/01/19
 *	@version	1.0
 *  @copyright	(c) 2017, kkllPreciel
 */

// 2�dinclude�̖h�~
#pragma once

namespace Sein
{
	namespace Math
	{
		// �\���̂̐錾
		struct Vector3D;

		/**
		 *	@brief	�s��\����
		 *
		 *	�s�D��s��ł��B
		 */
		struct Matrix
		{
			/**
			 *	@brief	�R���X�g���N�^
			 */
			Matrix();

			/**
			 *	@brief	�����t���R���X�g���N�^
			 *	@param	m11:1�s1��̒l
			 *	@param	m12:1�s2��̒l
			 *	@param	m13:1�s3��̒l
			 *	@param	m14:1�s4��̒l
			 *	@param	m21:2�s1��̒l
			 *	@param	m22:2�s2��̒l
			 *	@param	m23:2�s3��̒l
			 *	@param	m24:2�s4��̒l
			 *	@param	m31:3�s1��̒l
			 *	@param	m32:3�s2��̒l
			 *	@param	m33:3�s3��̒l
			 *	@param	m34:3�s4��̒l
			 *	@param	m41:4�s1��̒l
			 *	@param	m42:4�s2��̒l
			 *	@param	m43:4�s3��̒l
			 *	@param	m44:4�s4��̒l
			 */
			explicit Matrix(
				float m11, float m12, float m13, float m14,
				float m21, float m22, float m23, float m24,
				float m31, float m32, float m33, float m34,
				float m41, float m42, float m43, float m44 );

			/**
			 *	@brief	�R�s�[�R���X�g���N�^
			 *	@param	matrix:�R�s�[���̃C���X�^���X
			 */
			Matrix(const Matrix& matrix);

			/**
			 *	@brief	�f�X�g���N�^
			 */
			~Matrix();

			/**
			 *	@brief	������Z�q
			 *	@param	matrix:�������l
			 *	@return	�������
			 */
			Matrix& operator = (const Matrix& matrix);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	matrix:���Z����l
			 *	@return	���Z�������
			 */
			Matrix& operator += (const Matrix& matrix);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	matrix:���Z����l
			 *	@return	���Z�������
			 */
			Matrix& operator -= (const Matrix& matrix);

			/**
			 *	@brief	��Z������Z�q
			 *	@param	multiplier:��Z����l
			 *	@return	��Z�������
			 */
			Matrix& operator *= (float multiplier);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	divisor:���Z����l
			 *	@return	���Z�������
			 */
			Matrix& operator /= (float divisor);

			/**
			 *	@brief	���Z���Z�q
			 *	@param	matrix:���Z����l
			 *	@retun	���Z����
			 */
			Matrix operator + (const Matrix& matrix) const;

			/**
			 *	@brief	���Z���Z�q
			 *	@param	matrix:���Z����l
			 *	@return	���Z����
			 */
			Matrix operator - (const Matrix& matrix) const;

			/**
			 *	@brief	��Z���Z�q
			 *	@param	multiplier:��Z����l
			 *	@return	��Z����
			 */
			Matrix operator * (float multiplier) const;

			/**
			 *	@brief	���Z���Z�q
			 *	@param	divisor:���Z����l
			 *	@return	���Z����
			 */
			Matrix operator / (float divisor) const;

			/**
			 *	@brief	������r���Z�q
			 *	@param	matrix:��r����l
			 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
			 */
			bool operator == (const Matrix& matrix) const;

			/**
			 *	@brief	�񓙉���r���Z�q
			 *	@param	matrix:��r����l
			 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
			 */
			bool operator != (const Matrix& matrix) const;

			/**
			 *	@brief	����n�̃r���[�s����쐬����
			 *	@param	eye:�J�����̍��W
			 *	@param	lookat:�J�����̒����_
			 *	@param	up:�J�����̌���(�����)
			 *	@return	�r���[�s��
			 */
			static Matrix CreateLookAtLeftHanded(const Vector3D& eye, const Vector3D& lookat, const Vector3D& up);
		
			/**
			 *	@brief	����n�̓������e�s����쐬����
			 *	@param	fovy:Y�����̎���p (���W�A���P��)
			 *	@param	aspect:�A�X�y�N�g��
			 *	@param	near:�j�A�N���b�v
			 *	@param	far:�t�@�[�N���b�v
			 *	@return	�������e�s��
			 */
			static Matrix CreatePerspectiveLeftHanded(float fovy, float aspect, float near, float far);
		
			/**
			 *	@brief	����n�̐��ˉe(���s���e)�s����쐬����
			 *	@param	width:�r���[�{�����[���̕�
			 *	@param	height:�r���[�{�����[���̍���
			 *	@param	near:�j�A�N���b�v
			 *	@param	far:�t�@�[�N���b�v
			 *	@return	���ˉe�s��
			 */
			static Matrix CreateOrthographicLeftHanded(float width, float height, float near, float far);
		
			/**
			 *	@brief	X���̉�]�s����쐬����
			 *	@param	angle:��]�p�x(���W�A��)
			 *	@return	��]�s��
			 */
			static Matrix RotationX(float angle);
		
			/**
			 *	@brief	Y���̉�]�s����쐬����
			 *	@param	angle:��]�p�x(���W�A��)
			 *	@return	��]�s��
			 */
			static Matrix RotationY(float angle);
		
			/**
			 *	@brief	Z���̉�]�s����쐬����
			 *	@param	angle:��]�p�x(���W�A��)
			 *	@return	��]�s��
			 */
			static Matrix RotationZ(float angle);
		
			/**
			 *	@brief	���s�ړ��s����쐬����
			 *	@param	x:X����
			 *	@param	y:Y����
			 *	@param	z:Z����
			 *	@return	���s�ړ��s��
			 */
			static Matrix Translation(float x, float y, float z);
		
			/**
			 *	@brief	���s�ړ��s����쐬����
			 *	@param	position:�x�N�g��
			 *	@return	���s�ړ��s��
			 */
			static Matrix Translation(const Vector3D& position);

			/**
			 *	@brief	�P�ʍs�񉻂���
			 */
			Matrix& Identity();

			/**
			 *	@brief	�P�ʍs����쐬����
			 *	@return	�P�ʍs��
			 */
			static Matrix CreateIdentity();

			/**
			 *	@brief �]�u���s��
			 */
			void Transpose();

			/**
			 *	@brief	�]�u�s����쐬����
			 *	@return	�]�u�s��
			 */
			Matrix Transpose() const;

			union
			{
				struct
				{
					float _11, _12, _13, _14;
					float _21, _22, _23, _24;
					float _31, _32, _33, _34;
					float _41, _42, _43, _44;
				};
				float m[4][4];
			};

		};
	}
}