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
		 *	@brief	�R�s�[�R���X�g���N�^
		 *	@param	matrix:�R�s�[���̃C���X�^���X
		 */
		Matrix::Matrix(const Matrix& matrix)
		{
			_11 = matrix._11; _21 = matrix._21; _31 = matrix._31; _41 = matrix._41;
			_12 = matrix._12; _22 = matrix._22; _32 = matrix._32; _42 = matrix._42;
			_13 = matrix._13; _23 = matrix._23; _33 = matrix._33; _43 = matrix._43;
			_14 = matrix._14; _24 = matrix._24; _34 = matrix._34; _44 = matrix._44;
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
			_11 = matrix._11; _21 = matrix._21; _31 = matrix._31; _41 = matrix._41;
			_12 = matrix._12; _22 = matrix._22; _32 = matrix._32; _42 = matrix._42;
			_13 = matrix._13; _23 = matrix._23; _33 = matrix._33; _43 = matrix._43;
			_14 = matrix._14; _24 = matrix._24; _34 = matrix._34; _44 = matrix._44;

			return *this;
		}
		
		/**
		 *	@brief	���Z������Z�q
		 *	@param	matrix:���Z����l
		 *	@return	���Z�������
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
		 *	@brief	���Z������Z�q
		 *	@param	matrix:���Z����l
		 *	@return	���Z�������
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
		 *	@brief	��Z������Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z�������
		 */
		Matrix& Matrix::operator *= (float multiplier)
		{
			x *= multiplier;
			y *= multiplier;
		
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
			x /= divisor;
			y /= divisor;

			return *this;
		}

		/**
		 *	@brief	���Z���Z�q
		 *	@param	matrix:���Z����l
		 *	@retun	���Z����
		 */
		Matrix Matrix::operator + (const Matrix& matrix) const
		{
			return Matrix(x + matrix.x, y + matrix.y);
		}

		/**
		 *	@brief	���Z���Z�q
		 *	@param	matrix:���Z����l
		 *	@return	���Z����
		 */
		Matrix Matrix::operator - (const Matrix& matrix) const
		{
			return Matrix(x - matrix.x, y - matrix.y);
		}

		/**
		 *	@brief	��Z���Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z����
		 */
		Matrix Matrix::operator * (float multiplier) const
		{
			return Matrix(x * multiplier, y * multiplier);
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
			return Matrix(x / divisor, y / divisor);
		}

		/**
		 *	@brief	������r���Z�q
		 *	@param	matrix:��r����l
		 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
		 */
		bool Matrix::operator == (const Matrix& matrix) const
		{
			// ������epsilon��菬����
			return fabsf(x - matrix.x) <= std::numeric_limits<float>::epsilon()
				&& fabsf(y - matrix.y) <= std::numeric_limits<float>::epsilon();
		}

		/**
		 *	@brief	�񓙉���r���Z�q
		 *	@param	matrix:��r����l
		 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
		 */
		bool Matrix::operator != (const Matrix& matrix) const
		{
			// ������epsilon���傫��
			return std::numeric_limits<float>::epsilon() < fabsf(x - matrix.x)
				|| std::numeric_limits<float>::epsilon() < fabsf(y - matrix.y);
		}

		/**
		 *	@brief	�������擾����
		 *	@return	����
		 */
		float Matrix::Length() const
		{
			return sqrtf(x * x + y * y);
		}

		/**
		 *	@brief	���K�����s��
		 *	@return	���K������
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
		 *	@brief	���ς��s��
		 *	@param	matrix1:���̓x�N�g��
		 *	@param	matrix2:���̓x�N�g��
		 *	@return	���ό���
		 */
		float Matrix::DotProduct(const Matrix& matrix1, const Matrix& matrix2)
		{
			// ���ς͊e�v�f�̊|���Z�̘a
			return matrix1.x * matrix2.x + matrix1.y * matrix2.y;
		}

		/**
		 *	@brief	�O�ς��s��
		 *	@param	matrix1:���̓x�N�g��
		 *	@param	matrix2:���̓x�N�g��
		 *	@return	�O�ό���
		 */
		float Matrix::CrossProduct(const Matrix& matrix1, const Matrix& matrix2)
		{
			return matrix1.x * matrix2.y - matrix1.y * matrix2.x;
		}
	}
}