/**
 *	@file		Vector2D.h
 *	@brief		2�����x�N�g���Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2017/01/16
 *	@version	1.0
 *  @copyright	(c) 2017, kkllPreciel
 */

// 2�dinclude�̖h�~
#pragma once

namespace Sein
{
	namespace Math
	{
		/**
		 *	@brief	2�����x�N�g���\����
		 */
		struct Vector2D
		{
		public:
			/**
			 *	@brief	�R���X�g���N�^
			 */
			Vector2D();

			/**
			 *	@brief	�����t���R���X�g���N�^
			 *	@param	x:x����
			 *	@param	y:y����
			 */
			Vector2D(float x, float y);

			/**
			 *	@brief	�R�s�[�R���X�g���N�^
			 *	@param	vector:�R�s�[���̃C���X�^���X
			 */
			Vector2D(const Vector2D& vector);

			/**
			 *	@brief	�f�X�g���N�^
			 */
			~Vector2D();

			/**
			 *	@brief	������Z�q
			 *	@param	vector:�������l
			 *	@return	�������
			 */
			Vector2D& operator = (const Vector2D& vector);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z�������
			 */
			Vector2D& operator += (const Vector2D& vector);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z�������
			 */
			Vector2D& operator -= (const Vector2D& vector);

			/**
			 *	@brief	��Z������Z�q
			 *	@param	multiplier:��Z����l
			 *	@return	��Z�������
			 */
			Vector2D& operator *= (float multiplier);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	divisor:���Z����l
			 *	@return	���Z�������
			 */
			Vector2D& operator /= (float divisor);

			/**
			 *	@brief	���Z���Z�q
			 *	@param	vector:���Z����l
			 *	@retun	���Z����
			 */
			Vector2D operator + (const Vector2D& vector) const;

			/**
			 *	@brief	���Z���Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z����
			 */
			Vector2D operator - (const Vector2D& vector) const;

			/**
			 *	@brief	��Z���Z�q
			 *	@param	multiplier:��Z����l
			 *	@return	��Z����
			 */
			Vector2D operator * (float multiplier) const;

			/**
			 *	@brief	���Z���Z�q
			 *	@param	divisor:���Z����l
			 *	@return	���Z����
			 */
			Vector2D operator / (float divisor) const;

			/**
			 *	@brief	������r���Z�q
			 *	@param	vector:��r����l
			 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
			 */
			bool operator == (const Vector2D& vector) const;

			/**
			 *	@brief	�񓙉���r���Z�q
			 *	@param	vector:��r����l
			 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
			 */
			bool operator != (const Vector2D& vector) const;

			/**
			 *	@brief	�������擾����
			 *	@return	����
			 */
			float Length() const;

			/**
			 *	@brief	���K�����s��
			 *	@return	���K������
			 */
			Vector2D& Normalize();

			/**
			 *	@brief	���ς��s��
			 *	@param	vector1:���̓x�N�g��
			 *	@param	vector2:���̓x�N�g��
			 *	@return	���ό���
			 */
			static float DotProduct(const Vector2D& vector1, const Vector2D& vector2);

			/**
			 *	@brief	�O�ς��s��
			 *	@param	vector1:���̓x�N�g��
			 *	@param	vector2:���̓x�N�g��
			 *	@return	�O�ό���
			 */
			static float CrossProduct(const Vector2D& vector1, const Vector2D& vector2);

			// ���\�b�h
			// ��x�N�g��
			// ���`���
			// �e����(��������)

			float x; ///< x����
			float y; ///< y����
		};
	}
}