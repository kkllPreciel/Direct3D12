/**
 *	@file		HelloTexture.h
 *	@brief		Direct3D12テクスチャに関するヘッダファイル
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
 *	@brief	アプリケーションクラス
 */
class HelloTexture : public Application
{
public:
	/**
	 *	@brief	引数付きコンストラクタ
	 *	@param	width:横幅
	 *	@param	height:縦幅
	 *	@param	name:アプリ名
	 */
	HelloTexture(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	デストラクタ
	 */
	~HelloTexture();

	/**
	 *	@brief	初期化処理を行う
	 */
	virtual void OnInit();

	/**
	 *	@brief	更新処理を行う
	 */
	virtual void OnUpdate();

	/**
	 *	@brief	描画処理を行う
	 */
	virtual void OnRender();

	/**
	 *	@brief	終了処理を行う
	 */
	virtual void OnDestroy();

private:
	/**
	 *	@brief	コンストラクタ
	 */
	HelloTexture() = delete;

	/**
	 *	@brief	コピーコンストラクタ
	 *	@param	other:コピー元
	 */
	HelloTexture(const HelloTexture& other) = delete;

	/**
	 *	@brief	代入演算子オペレータ
	 *	@param	other:代入元
	 */
	HelloTexture& operator = (const HelloTexture& other) = delete;

private:

	/**
	 *	@brief	フレーム数
	 */
	static const UINT FrameCount = 2;

	/**
	 *	@brief	テクスチャ横幅
	 */
	static const UINT TextureWidth = 256;

	/**
	 *	@brief	テクスチャ縦幅
	 */
	static const UINT TextureHeight = 256;

	/**
	 *	@brief	テクスチャピクセルサイズ
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
	 *	@brief	頂点フォーマット
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
	 *	@brief	パイプラインを作成する
	 */
	void CreatePipeline();

	/**
	 *	@brief	アセットを読み込む
	 */
	void LoadAssets();

	/**
	 *	@brief	テクスチャデータを作成する
	 */
	std::vector<UINT8> GenerateTextureData();

	/**
	 *	@brief	コマンドリストを投入する(作成する)
	 */
	void PopulateCommandList();

	/**
	 *	@brief	描画終了待ちを行う
	 */
	void WaitForPreviousFrame();
};