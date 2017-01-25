/**
 *	@file		HelloThreeDimensions.h
 *	@brief		Direct3D123D�\���Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2017/01/25
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
class HelloThreeDimensions : public Application
{
public:
	/**
	 *	@brief	�����t���R���X�g���N�^
	 *	@param	width:����
	 *	@param	height:�c��
	 *	@param	name:�A�v����
	 */
	HelloThreeDimensions(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	�f�X�g���N�^
	 */
	~HelloThreeDimensions();

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
	HelloThreeDimensions() = delete;

	/**
	 *	@brief	�R�s�[�R���X�g���N�^
	 *	@param	other:�R�s�[��
	 */
	HelloThreeDimensions(const HelloThreeDimensions& other) = delete;

	/**
	 *	@brief	������Z�q�I�y���[�^
	 *	@param	other:�����
	 */
	HelloThreeDimensions& operator = (const HelloThreeDimensions& other) = delete;

private:
	static const UINT FrameCount = 2;	///< �t���[����

	// Pipeline objects.
	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissorRect;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12Device> m_device;
	ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12CommandAllocator> m_bundleAllocator;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12DescriptorHeap> m_cbvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	ComPtr<ID3D12GraphicsCommandList> m_bundle;
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

	/**
	 *	@brief	�R���X�^���g�o�b�t�@�p�\����
	 */
	struct ConstantBuffer
	{
		DirectX::XMMATRIX matrix;
	};

	// App resources.
	ComPtr<ID3D12Resource> m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	ComPtr<ID3D12Resource> m_constantBuffer;
	ConstantBuffer m_constantBufferData;
	UINT8* m_pCbvDataBegin;

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