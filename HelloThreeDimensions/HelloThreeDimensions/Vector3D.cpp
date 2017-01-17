/**
 *	@file		Vector3D.cpp
 *	@brief		3�����x�N�g���Ɋւ��鏈���s���v���O�����\�[�X
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
		 *	@brief	�R���X�g���N�^
		 */
		Vector3D::Vector3D()
		{

		}
		
		/**
		 *	@brief	�����t���R���X�g���N�^
		 *	@param	x:x����
		 *	@param	y:y����
		 *	@param	z:z����
		 */
		Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z)
		{

		}
		
		/**
		 *	@brief	�����t���R���X�g���N�^
		 *	@param	vector:2�����x�N�g��
		 *	@param	z:z����
		 */
		Vector3D::Vector3D(const Vector2D& vector, float z) : x(vector.x), y(vector.y), z(z)
		{

		}
		
		/**
		 *	@brief	�R�s�[�R���X�g���N�^
		 *	@param	vector:�R�s�[���̃C���X�^���X
		 */
		Vector3D::Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z)
		{

		}
		
		/**
		 *	@brief	�f�X�g���N�^
		 */
		Vector3D::~Vector3D()
		{

		}
		
		/**
		 *	@brief	������Z�q
		 *	@param	vector:�������l
		 *	@return	�������
		 */
		Vector3D& Vector3D::operator = (const Vector3D& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;

			return *this;
		}

		/**
		 *	@brief	���Z������Z�q
		 *	@param	vector:���Z����l
		 *	@return	���Z�������
		 */
		Vector3D& Vector3D::operator += (const Vector3D& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;

			return *this;
		}

		/**
		 *	@brief	���Z������Z�q
		 *	@param	vector:���Z����l
		 *	@return	���Z�������
		 */
		Vector3D& Vector3D::operator -= (const Vector3D& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;

			return *this;
		}

		/**
		 *	@brief	��Z������Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z�������
		 */
		Vector3D& Vector3D::operator *= (float multiplier)
		{
			x *= multiplier;
			y *= multiplier;
			z *= multiplier;

			return *this;
		}

		/**
		 *	@brief	���Z������Z�q
		 *	@param	divisor:���Z����l
		 *	@return	���Z�������
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
		 *	@brief	���Z���Z�q
		 *	@param	vector:���Z����l
		 *	@retun	���Z����
		 */
		Vector3D Vector3D::operator + (const Vector3D& vector) const
		{
			return Vector3D(x + vector.x, y + vector.y, z + vector.z);
		}

		/**
		 *	@brief	���Z���Z�q
		 *	@param	vector:���Z����l
		 *	@return	���Z����
		 */
		Vector3D Vector3D::operator - (const Vector3D& vector) const
		{
			return Vector3D(x - vector.x, y - vector.y, z - vector.z);
		}

		/**
		 *	@brief	��Z���Z�q
		 *	@param	multiplier:��Z����l
		 *	@return	��Z����
		 */
		Vector3D Vector3D::operator * (float multiplier) const
		{
			return Vector3D(x * multiplier, y * multiplier, z * multiplier);
		}

		/**
		 *	@brief	���Z���Z�q
		 *	@param	divisor:���Z����l
		 *	@return	���Z����
		 */
		Vector3D Vector3D::operator / (float divisor) const
		{
#ifdef _DEBUG
			_ASSERTE(std::numeric_limits<float>::epsilon() <= divisor && "division by zero.(Vector3D::operator/)");
#endif;
			return Vector3D(x / divisor, y / divisor, z / divisor);
		}

		/**
		 *	@brief	������r���Z�q
		 *	@param	vector:��r����l
		 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
		 */
		bool Vector3D::operator == (const Vector3D& vector) const
		{
			// ������epsilon��菬����
			return fabsf(x - vector.x) <= std::numeric_limits<float>::epsilon()
				&& fabsf(y - vector.y) <= std::numeric_limits<float>::epsilon()
				&& fabsf(z - vector.z) <= std::numeric_limits<float>::epsilon();
		}

		/**
		 *	@brief	�񓙉���r���Z�q
		 *	@param	vector:��r����l
		 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
		 */
		bool Vector3D::operator != (const Vector3D& vector) const
		{
			// ������epsilon���傫��
			return std::numeric_limits<float>::epsilon() < fabsf(x - vector.x)
				|| std::numeric_limits<float>::epsilon() < fabsf(y - vector.y)
				|| std::numeric_limits<float>::epsilon() < fabsf(z - vector.z);
		}

		/**
		 *	@brief	�������擾����
		 *	@return	����
		 */
		float Vector3D::Length() const
		{
			return sqrtf(x * x + y * y + z * z);
		}
		
		/**
		 *	@brief	���K�����s��
		 *	@return	���K������
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
		 *	@brief	���ς��s��
		 *	@param	vector1:���̓x�N�g��
		 *	@param	vector2:���̓x�N�g��
		 *	@return	���ό���
		 */
		float Vector3D::DotProduct(const Vector3D& vector1, const Vector3D& vector2)
		{
			// ���ς͊e�v�f�̊|���Z�̘a
			return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
		}
		
		/**
		 *	@brief	�O�ς��s��
		 *	@param	vector1:���̓x�N�g��
		 *	@param	vector2:���̓x�N�g��
		 *	@return	�O�ό���
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