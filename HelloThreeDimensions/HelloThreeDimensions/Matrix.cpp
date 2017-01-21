/**
 *	@file		Matrix.cpp
 *	@brief		�s��Ɋւ��鏈���s���v���O�����\�[�X
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
		 *	@brief	�R���X�g���N�^
		 */
		Matrix::Matrix()
		{
		
		}

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
		 *	@brief	�R�s�[�R���X�g���N�^
		 *	@param	matrix:�R�s�[���̃C���X�^���X
		 */
		Matrix::Matrix(const Matrix& matrix)
		{
			_11 = matrix._11; _12 = matrix._12; _13 = matrix._13; _14 = matrix._14;
			_21 = matrix._21; _22 = matrix._22; _23 = matrix._23; _24 = matrix._24;
			_31 = matrix._31; _32 = matrix._32; _33 = matrix._33; _34 = matrix._34;
			_41 = matrix._41; _42 = matrix._42; _43 = matrix._43; _44 = matrix._44;
		}
		
		/**
		 *	@brief	�f�X�g���N�^
		 */
		Matrix::~Matrix()
		{
		
		}
		
		/**
		 *	@brief	������Z�q
		 *	@param	matrix:�������l
		 *	@return	�������
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
		 *	@brief	���Z������Z�q
		 *	@param	matrix:���Z����l
		 *	@return	���Z�������
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
		 *	@brief	���Z������Z�q
		 *	@param	matrix:���Z����l
		 *	@return	���Z�������
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
		 *	@brief	��Z������Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z�������
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
		 *	@brief	���Z������Z�q
		 *	@param	divisor:���Z����l
		 *	@return	���Z�������
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
		 *	@brief	���Z���Z�q
		 *	@param	matrix:���Z����l
		 *	@retun	���Z����
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
		 *	@brief	���Z���Z�q
		 *	@param	matrix:���Z����l
		 *	@return	���Z����
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
		 *	@brief	��Z���Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z����
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
		 *	@brief	���Z���Z�q
		 *	@param	divisor:���Z����l
		 *	@return	���Z����
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
		 *	@brief	������r���Z�q
		 *	@param	matrix:��r����l
		 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
		 */
		bool Matrix::operator == (const Matrix& matrix) const
		{
			// �������P�ʂŔ�r
			return (0 == memcmp(this, &matrix, sizeof(Matrix)));
		}

		/**
		 *	@brief	�񓙉���r���Z�q
		 *	@param	matrix:��r����l
		 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
		 */
		bool Matrix::operator != (const Matrix& matrix) const
		{
			// �������P�ʂŔ�r
			return (0 != memcmp(this, &matrix, sizeof(Matrix)));
		}

		/**
		 *	@brief	����n�̃r���[�s����쐬����
		 *	@param	eye:�J�����̍��W
		 *	@param	lookat:�J�����̒����_
		 *	@param	up:�J�����̌���(�����)
		 *	@return	�r���[�s��
		 */
		Matrix Matrix::CreateLookAtLeftHanded(const Vector3D& eye, const Vector3D& lookat, const Vector3D& up);
		
		/**
		 *	@brief	����n�̓������e�s����쐬����
		 *	@param	fovy:Y�����̎���p (���W�A���P��)
		 *	@param	aspect:�A�X�y�N�g��
		 *	@param	near:�j�A�N���b�v
		 *	@param	far:�t�@�[�N���b�v
		 *	@return	�������e�s��
		 */
		Matrix Matrix::CreatePerspectiveLeftHanded(float fovy, float aspect, float near, float far);
		
		/**
		 *	@brief	����n�̐��ˉe(���s���e)�s����쐬����
		 *	@param	width:�r���[�{�����[���̕�
		 *	@param	height:�r���[�{�����[���̍���
		 *	@param	near:�j�A�N���b�v
		 *	@param	far:�t�@�[�N���b�v
		 *	@return	���ˉe�s��
		 */
		Matrix Matrix::CreateOrthographicLeftHanded(float width, float height, float near, float far);
		
		/**
		 *	@brief	X���̉�]�s����쐬����
		 *	@param	angle:��]�p�x(���W�A��)
		 *	@return	��]�s��
		 */
		Matrix Matrix::RotationX(float angle);
		
		/**
		 *	@brief	Y���̉�]�s����쐬����
		 *	@param	angle:��]�p�x(���W�A��)
		 *	@return	��]�s��
		 */
		Matrix Matrix::RotationY(float angle);
		
		/**
		 *	@brief	Z���̉�]�s����쐬����
		 *	@param	angle:��]�p�x(���W�A��)
		 *	@return	��]�s��
		 */
		Matrix Matrix::RotationZ(float angle);
		
		/**
		 *	@brief	���s�ړ��s����쐬����
		 *	@param	x:X����
		 *	@param	y:Y����
		 *	@param	z:Z����
		 *	@return	���s�ړ��s��
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
		 *	@brief	���s�ړ��s����쐬����
		 *	@param	position:�x�N�g��
		 *	@return	���s�ړ��s��
		 */
		Matrix Matrix::Translation(const Vector3D& position)
		{
			return Translation(position.x, position.y, position.z);
		}
		
		/**
		 *	@brief	�P�ʍs�񉻂���
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
		 *	@brief	�P�ʍs����쐬����
		 *	@return	�P�ʍs��
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
		 *	@brief �]�u���s��
		 */
		void Matrix::Transpose()
		{
			// *this = Matrix::Transpose();
		}
		
		/**
		 *	@brief	�]�u�s����쐬����
		 *	@return	�]�u�s��
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