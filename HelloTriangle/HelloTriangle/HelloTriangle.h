/**
 *	@file		HelloTriangle.h
 *	@brief		Direct3D12�g���C�A���O���Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2016/10/15
 *	@version	1.0
 */

#pragma once

// include
#include <wrl\client.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include "Application.h"

using namespace Microsoft::WRL;

/**
 *	@brief	�A�v���P�[�V�����N���X
 */
class HelloTriangle : public Application
{
public:
	/**
	 *	@brief	�����t���R���X�g���N�^
	 *	@param	width:����
	 *	@param	height:�c��
	 *	@param	name:�A�v����
	 */
	HelloTriangle(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	�f�X�g���N�^
	 */
	~HelloTriangle();

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
	HelloTriangle() = delete;

	/**
	 *	@brief	�R�s�[�R���X�g���N�^
	 *	@param	other:�R�s�[��
	 */
	HelloTriangle(const HelloTriangle& other) = delete;

	/**
	 *	@brief	������Z�q�I�y���[�^
	 *	@param	other:�����
	 */
	HelloTriangle& operator = (const HelloTriangle& other) = delete;

private:
	static const UINT FrameCount = 2;

	// Pipeline objects.
	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissorRect;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12Device> m_device;
	ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	UINT m_rtvDescriptorSize;

	// Synchronization objects.
	UINT m_frameIndex;
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;

	/**
	 *	@brief	���_�t�H�[�}�b�g
	 */
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
	};

	// App resources.
	ComPtr<ID3D12Resource> m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	/**
	 *	@brief	�p�C�v���C�����쐬����
	 */
	void CreatePipeline();

	/**
	 *	@brief	�A�Z�b�g��ǂݍ���
	 */
	void LoadAssets();

	/**
	 *	@brief	�R�}���h���X�g�𓊓�����(�쐬����)
	 */
	void PopulateCommandList();

	/**
	 *	@brief	�`��I���҂����s��
	 */
	void WaitForPreviousFrame();
};