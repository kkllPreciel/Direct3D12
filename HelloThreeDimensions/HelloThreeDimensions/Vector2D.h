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
			explicit Vector2D(const Vector2D& vector);

			/**
			 *	@brief	�f�X�g���N�^
			 */
			~Vector2D();

			/**
			 *	@brief	������Z�q
			 *	@param	vector:�������l
			 *	@return	�������
			 */
			Vector2D operator = (const Vector2D& vector);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z�������
			 */
			Vector2D operator += (const Vector2D& vector);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	vector:���Z����l
			 *	@return	���Z�������
			 */
			Vector2D operator -= (const Vector2D& vector);

			/**
			 *	@brief	��Z������Z�q
			 *	@param	multiplier:�搔
			 *	@return	��Z�������
			 */
			Vector2D operator *= (float multiplier);

			/**
			 *	@brief	���Z������Z�q
			 *	@param	divisor:����
			 *	@return	���Z�������
			 */
			Vector2D operator /= (float divisor);

			// �I�y���[�^
			// ���Z
			// ���Z
			// ��Z
			// ���Z
			// ��r

			// ���\�b�h
			// ����
			// ��x�N�g��
			// ���K��
			// ����
			// �O��
			// ���`���
			// ��r
			// �e����(��������)

			// 
			float x; ///< x����
			float y; ///< y����
		};
	}
}