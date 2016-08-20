/**
 *	@file		HelloWindow.h
 *	@brief		Direct3D12�E�B���h�E�Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2016/08/19
 *	@version	1.0
 */

#pragma once

// include
#include <wrl\client.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include "Application.h"

using namespace Microsoft::WRL;

/**
 *	@brief	�A�v���P�[�V�����N���X
 */
class HelloWindow : public Application
{
public:
	/**
	 *	@brief	�����t���R���X�g���N�^
	 *	@param	width:����
	 *	@param	height:�c��
	 *	@param	name:�A�v����
	 */
	HelloWindow(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	�f�X�g���N�^
	 */
	~HelloWindow();

	/**
	 *	@brief	�������������s��
	 */
	virtual void OnInit();

	/**
	 *	@brief	�X�V�������s��
	 */
	virtual void OnUpdate();

	/**
	 *	@brief	�`�揈�����s��
	 */
	virtual void OnRender();

	/**
	 *	@brief	�I���������s��
	 */
	virtual void OnDestroy();

private:
	/**
	 *	@brief	�R���X�g���N�^
	 */
	HelloWindow() = delete;

	/**
	 *	@brief	�R�s�[�R���X�g���N�^
	 *	@param	other:�R�s�[��
	 */
	HelloWindow(const HelloWindow& other) = delete;

	/**
	 *	@brief	������Z�q�I�y���[�^
	 *	@param	other:�����
	 */
	HelloWindow& operator = (const HelloWindow& other) = delete;

private:
	static const UINT FrameCount = 2;

	// Pipeline objects.
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12Device> m_device;
	ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	UINT m_rtvDescriptorSize;

	// Synchronization objects.
	UINT m_frameIndex;
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;

	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
	void WaitForPreviousFrame();
};