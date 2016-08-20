/**
 *	@file		HelloWindow.h
 *	@brief		Direct3D12ウィンドウに関するヘッダファイル
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
 *	@brief	アプリケーションクラス
 */
class HelloWindow : public Application
{
public:
	/**
	 *	@brief	引数付きコンストラクタ
	 *	@param	width:横幅
	 *	@param	height:縦幅
	 *	@param	name:アプリ名
	 */
	HelloWindow(unsigned int width, unsigned int height, std::wstring name);

	/**
	 *	@brief	デストラクタ
	 */
	~HelloWindow();

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
	HelloWindow() = delete;

	/**
	 *	@brief	コピーコンストラクタ
	 *	@param	other:コピー元
	 */
	HelloWindow(const HelloWindow& other) = delete;

	/**
	 *	@brief	代入演算子オペレータ
	 *	@param	other:代入元
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