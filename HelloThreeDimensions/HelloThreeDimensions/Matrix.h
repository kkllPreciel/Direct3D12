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
		 *	��D��s��ł��B
		 */
		struct Matrix
		{
			/**
			 *	@brief	�R���X�g���N�^
			 */
			Matrix();

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
			Matrix CreateLookAtLeftHanded(const Vector3D& eye, const Vector3D& lookat, const Vector3D& up);
		
			/**
			 *	@brief	����n�̓������e�s����쐬����
			 *	@param	fovy:Y�����̎���p (���W�A���P��)
			 *	@param	aspect:�A�X�y�N�g��
			 *	@param	near:�j�A�N���b�v
			 *	@param	far:�t�@�[�N���b�v
			 *	@return	�������e�s��
			 */
			Matrix CreatePerspectiveLeftHanded(float fovy, float aspect, float near, float far);
		
			/**
			 *	@brief	����n�̐��ˉe(���s���e)�s����쐬����
			 *	@param	width:�r���[�{�����[���̕�
			 *	@param	height:�r���[�{�����[���̍���
			 *	@param	near:�j�A�N���b�v
			 *	@param	far:�t�@�[�N���b�v
			 *	@return	���ˉe�s��
			 */
			Matrix CreateOrthographicLeftHanded(float width, float height, float near, float far);
		
			/**
			 *	@brief	X���̉�]�s����쐬����
			 *	@param	angle:��]�p�x(���W�A��)
			 *	@return	��]�s��
			 */
			Matrix RotationX(float angle);
		
			/**
			 *	@brief	Y���̉�]�s����쐬����
			 *	@param	angle:��]�p�x(���W�A��)
			 *	@return	��]�s��
			 */
			Matrix RotationY(float angle);
		
			/**
			 *	@brief	Z���̉�]�s����쐬����
			 *	@param	angle:��]�p�x(���W�A��)
			 *	@return	��]�s��
			 */
			Matrix RotationZ(float angle);
		
			/**
			 *	@brief	���s�ړ��s����쐬����
			 *	@param	x:X����
			 *	@param	y:Y����
			 *	@param	z:Z����
			 *	@return	���s�ړ��s��
			 */
			Matrix Translation(float x, float y, float z);
		
			/**
			 *	@brief	���s�ړ��s����쐬����
			 *	@param	position:�x�N�g��
			 *	@return	���s�ړ��s��
			 */
			Matrix Translation(const Vector3D& position);

			/**
			 *	@brief	�P�ʍs�񉻂���
			 */
			Matrix& Identity();

			/**
			 *	@brief	�P�ʍs����쐬����
			 *	@return	�P�ʍs��
			 */
			Matrix CreateIdentity();

			/**
			 *	@brief	�]�u�s����쐬����
			 *	@return	�]�u�s��
			 */
			Matrix Transpose() const;

			/**
			 *	@brief �]�u���s��
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