/**
 *	@file		Vector3D.h
 *	@brief		3�����x�N�g���Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2017/01/17
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
		struct Vector2D;

		/**
		 *	@brief	3�����x�N�g���\����
		 */
		struct Vector3D
		{
			/**
			 *	@brief	�R���X�g���N�^
			 */
			Vector3D();

			/**
			 *	@brief	�����t���R���X�g���N�^
			 *	@param	x:x����
			 *	@param	y:y����
			 *	@param	z:z����
			 */
			Vector3D(float x, float y, float z);

			/**
			 *	@brief	�����t���R���X�g���N�^
			 *	@param	vector:2�����x�N�g��
			 *	@param	z:z����
			 */
			Vector3D(const Vector2D& vector, float z);

			/**
			 *	@brief	�R�s�[�R���X�g���N�^
			 *	@param	vector:�R�s�[���̃C���X�^���X
			 */
			Vector3D(const Vector3D& vector);

			/**
			 *	@brief	�f�X�g���N�^
			 */
			~Vector3D();

			/**
			 *	@brief	������Z�q
			 *	@param	vector:�������l
			 *	@return	�������
			 */
			Vector3D& operator = (const Vector3D& vector);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z�������
			 */
			Vector3D& operator += (const Vector3D& vector);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z�������
			 */
			Vector3D& operator -= (const Vector3D& vector);

			/**
			 *	@brief	��Z������Z�q
			 *	@param	multiplier:��Z����l
			 *	@return	��Z�������
			 */
			Vector3D& operator *= (float multiplier);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	divisor:���Z����l
			 *	@return	���Z�������
			 */
			Vector3D& operator /= (float divisor);

			/**
			 *	@brief	���Z���Z�q
			 *	@param	vector:���Z����l
			 *	@retun	���Z����
			 */
			Vector3D operator + (const Vector3D& vector) const;

			/**
			 *	@brief	���Z���Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z����
			 */
			Vector3D operator - (const Vector3D& vector) const;

			/**
			 *	@brief	��Z���Z�q
			 *	@param	multiplier:��Z����l
			 *	@return	��Z����
			 */
			Vector3D operator * (float multiplier) const;

			/**
			 *	@brief	���Z���Z�q
			 *	@param	divisor:���Z����l
			 *	@return	���Z����
			 */
			Vector3D operator / (float divisor) const;

			/**
			 *	@brief	������r���Z�q
			 *	@param	vector:��r����l
			 *	@return	bool�B�����Ȃ�true, �񓙉��Ȃ�false
			 */
			bool operator == (const Vector3D& vector) const;

			/**
			 *	@brief	�񓙉���r���Z�q
			 *	@param	vector:��r����l
			 *	@return	bool�B�񓙉��Ȃ�true,�����Ȃ�false
			 */
			bool operator != (const Vector3D& vector) const;

			/**
			 *	@brief	�������擾����
			 *	@return	����
			 */
			float Length() const;

			/**
			 *	@brief	���K�����s��
			 *	@return	���K������
			 */
			Vector3D& Normalize();

			/**
			 *	@brief	���ς��s��
			 *	@param	vector1:���̓x�N�g��
			 *	@param	vector2:���̓x�N�g��
			 *	@return	���ό���
			 */
			static float DotProduct(const Vector3D& vector1, const Vector3D& vector2);

			/**
			 *	@brief	�O�ς��s��
			 *	@param	vector1:���̓x�N�g��
			 *	@param	vector2:���̓x�N�g��
			 *	@return	�O�ό���
			 */
			static Vector3D CrossProduct(const Vector3D& vector1, const Vector3D& vector2);

			// ���\�b�h
			// ��x�N�g��
			// ���`���
			// �e����(��������)

			float x; ///< x����
			float y; ///< y����
			float z; ///< z����
		};
	}
}