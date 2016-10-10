/**
 *	@file		Application.h
 *	@brief		�A�v���P�[�V�����Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2016/10/10
 *	@version	1.0
 */

#pragma once

// include
#include <Windows.h>
#include <string>

/**
 *	@brief	�A�v���P�[�V�����x�[�X�N���X
 */
class Application
{
public:
	/**
	 *	@brief	�����t���R���X�g���N�^
	 *	@param	width:����
	 *	@param	height:�c��
	 *	@param	name:�A�v����
	 */
	Application(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	�f�X�g���N�^
	 */
	virtual ~Application();

	/**
	 *	@brief	�������������s��
	 */
	virtual void OnInit() = 0;

	/**
	 *	@brief	�X�V�������s��
	 */
	virtual void OnUpdate() = 0;

	/**
	 *	@brief	�`�揈�����s��
	 */
	virtual void OnRender() = 0;

	/**
	 *	@brief	�I���������s��
	 */
	virtual void OnDestroy() = 0;

	/**
	 *	@brief	�������擾����
	 */
	unsigned int GetWidth() const;

	/**
	 *	@brief	�c�����擾����
	 */
	unsigned int GetHeight() const;

	/**
	 *	@brief	�A�X�y�N�g����擾����
	 */
	float GetAspect() const;

	/**
	 *	@brief	�^�C�g�����擾����
	 */
	const WCHAR* GetTitle() const;

protected:
	/**
	 *	@brief	�A�Z�b�g�̃t���p�X���擾����
	 *	@param	asset_name:�t���p�X���擾����A�Z�b�g��
	 *	@return	�A�Z�b�g�̃t���p�X
	 */
	std::wstring GetAssetFullPath(LPCWSTR asset_name);

private:
	/**
	 *	@brief	�R���X�g���N�^
	 */
	Application() = delete;

	/**
	 *	@brief	�R�s�[�R���X�g���N�^
	 *	@param	other:�R�s�[��
	 */
	Application(const Application& other) = delete;

	/**
	 *	@brief	������Z�q�I�y���[�^
	 *	@param	other:�����
	 */
	Application& operator = (const Application& other) = delete;

	unsigned int	width;			///< ����
	unsigned int	height;			///< �c��
	float			aspect;			///< �A�X�y�N�g��
	std::wstring	title;			///< �^�C�g��
	std::wstring	assets_path;	///< �A�Z�b�g�p�X
};