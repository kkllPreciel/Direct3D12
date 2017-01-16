/**
 *	@file		Vector2D.cpp
 *	@brief		2�����x�N�g���Ɋւ��鏈���s���v���O�����\�[�X
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
		 *	@brief	�R���X�g���N�^
		 */
		Vector2D::Vector2D()
		{
		
		}
		
		/**
		 *	@brief	�����t���R���X�g���N�^
		 *	@param	x:x����
		 *	@param	y:y����
		 */
		Vector2D::Vector2D(float x, float y) : x(x), y(y)
		{
		
		}
		
		/**
		 *	@brief	�R�s�[�R���X�g���N�^
		 *	@param	vector:�R�s�[���̃C���X�^���X
		 */
		Vector2D::Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y)
		{
		
		}
		
		/**
		 *	@brief	�f�X�g���N�^
		 */
		Vector2D::~Vector2D()
		{
		
		}
		
		/**
		 *	@brief	������Z�q
		 *	@param	vector:�������l
		 *	@return	�������
		 */
		Vector2D& Vector2D::operator = (const Vector2D& vector)
		{
			x = vector.x;
			y = vector.y;
		
			return *this;
		}
		
		/**
		 *	@brief	���Z������Z�q
		 *	@param	vector:���Z����l
		 *	@return	���Z�������
		 */
		Vector2D& Vector2D::operator += (const Vector2D& vector)
		{
			x += vector.x;
			y += vector.y;
		
			return *this;
		}
		
		/**
		 *	@brief	���Z������Z�q
		 *	@param	vector:���Z����l
		 *	@return	���Z�������
		 */
		Vector2D& Vector2D::operator -= (const Vector2D& vector)
		{
			x -= vector.x;
			y -= vector.y;
		
			return *this;
		}
		
		/**
		 *	@brief	��Z������Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z�������
		 */
		Vector2D& Vector2D::operator *= (float multiplier)
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
		 *	@brief	���Z���Z�q
		 *	@param	vector:���Z����l
		 *	@retun	���Z����
		 */
		Vector2D Vector2D::operator + (const Vector2D& vector) const
		{
			return Vector2D(x + vector.x, y + vector.y);
		}

		/**
		 *	@brief	���Z���Z�q
		 *	@param	vector:���Z����l
		 *	@return	���Z����
		 */
		Vector2D Vector2D::operator - (const Vector2D& vector) const
		{
			return Vector2D(x - vector.x, y - vector.y);
		}

		/**
		 *	@brief	��Z���Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z����
		 */
		Vector2D Vector2D::operator * (float multiplier) const
		{
			return Vector2D(x * multiplier, y * multiplier);
		}

		/**
		 *	@brief	���Z���Z�q
		 *	@param	divisor:���Z����l
		 *	@return	���Z����
		 */
		Vector2D Vector2D::operator / (float divisor) const
		{
#ifdef _DEBUG
				_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor);
#endif;
			return Vector2D(x / divisor, y / divisor);
		}

		/**
		 *	@brief	������r���Z�q
		 *	@param	vector:��r����l
		 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
		 */
		bool Vector2D::operator == (const Vector2D& vector) const
		{
			// ������epsilon��菬����
			return fabsf(x - vector.x) <= std::numeric_limits<float>::epsilon()
				&& fabsf(y - vector.y) <= std::numeric_limits<float>::epsilon();
		}

		/**
		 *	@brief	�񓙉���r���Z�q
		 *	@param	vector:��r����l
		 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
		 */
		bool Vector2D::operator != (const Vector2D& vector) const
		{
			// ������epsilon���傫��
			return std::numeric_limits<float>::epsilon() < fabsf(x - vector.x)
				|| std::numeric_limits<float>::epsilon() < fabsf(y - vector.y);
		}

		/**
		 *	@brief	�������擾����
		 *	@return	����
		 */
		float Vector2D::Length() const
		{
			return sqrtf(x * x + y * y);
		}

		/**
		 *	@brief	���K�����s��
		 *	@return	���K������
		 */
		Vector2D& Vector2D::Normalize()
		{
			float fLength = Length();
#ifdef _DEBUG
				_ASSERTE(std::numeric_limits<float>::epsilon() <= fLength && "���K���Ɏ��s���܂����B(CVector2D::Normalize)");
#endif;
			x /= fLength;
			y /= fLength;

			return *this;
		}

		/**
		 *	@brief	���ς��s��
		 *	@param	vector1:���̓x�N�g��
		 *	@param	vector2:���̓x�N�g��
		 *	@return	���ό���
		 */
		float Vector2D::DotProduct(const Vector2D& vector1, const Vector2D& vector2)
		{
			// ���ς͊e�v�f�̊|���Z�̘a
			return vector1.x * vector2.x + vector1.y * vector2.y;
		}

		/**
		 *	@brief	�O�ς��s��
		 *	@param	vector1:���̓x�N�g��
		 *	@param	vector2:���̓x�N�g��
		 *	@return	�O�ό���
		 */
		float Vector2D::CrossProduct(const Vector2D& vector1, const Vector2D& vector2)
		{
			return vector1.x * vector2.y - vector1.y * vector2.x;
		}
	}
}