/**
 *	@file		HelloTexture.h
 *	@brief		Direct3D12�e�N�X�`���Ɋւ���w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2016/10/18
 *	@version	1.0
 */

#pragma once

// include
#include <wrl\client.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <vector>
#include "Application.h"

using namespace Microsoft::WRL;

/**
 *	@brief	�A�v���P�[�V�����N���X
 */
class HelloTexture : public Application
{
public:
	/**
	 *	@brief	�����t���R���X�g���N�^
	 *	@param	width:����
	 *	@param	height:�c��
	 *	@param	name:�A�v����
	 */
	HelloTexture(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	�f�X�g���N�^
	 */
	~HelloTexture();

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
	HelloTexture() = delete;

	/**
	 *	@brief	�R�s�[�R���X�g���N�^
	 *	@param	other:�R�s�[��
	 */
	HelloTexture(const HelloTexture& other) = delete;

	/**
	 *	@brief	������Z�q�I�y���[�^
	 *	@param	other:�����
	 */
	HelloTexture& operator = (const HelloTexture& other) = delete;

private:

	/**
	 *	@brief	�t���[����
	 */
	static const UINT FrameCount = 2;

	/**
	 *	@brief	�e�N�X�`������
	 */
	static const UINT TextureWidth = 256;

	/**
	 *	@brief	�e�N�X�`���c��
	 */
	static const UINT TextureHeight = 256;

	/**
	 *	@brief	�e�N�X�`���s�N�Z���T�C�Y
	 */
	static const UINT TexturePixelSize = 4;

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
	ComPtr<ID3D12DescriptorHeap> m_srvHeap;
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
		DirectX::XMFLOAT2 uv;
	};

	// App resources.
	ComPtr<ID3D12Resource> m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	ComPtr<ID3D12Resource> m_texture;

	/**
	 *	@brief	�p�C�v���C�����쐬����
	 */
	void CreatePipeline();

	/**
	 *	@brief	�A�Z�b�g��ǂݍ���
	 */
	void LoadAssets();

	/**
	 *	@brief	�e�N�X�`���f�[�^���쐬����
	 */
	std::vector<UINT8> GenerateTextureData();

	/**
	 *	@brief	�R�}���h���X�g�𓊓�����(�쐬����)
	 */
	void PopulateCommandList();

	/**
	 *	@brief	�`��I���҂����s��
	 */
	void WaitForPreviousFrame();
};