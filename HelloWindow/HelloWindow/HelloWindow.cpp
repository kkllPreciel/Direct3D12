/**
*	@file		HelloWindow.cpp
*	@brief		アプリケーションに関する処理を行うプログラムソース
*	@author		kkllPreciel
*	@date		2016/08/20
*	@version	1.0
*/

#include "HelloWindow.h"
#include "Win32Frame.h"

/**
 *	@brief	引数付きコンストラクタ
 *	@param	width:横幅
 *	@param	height:縦幅
 *	@param	name:アプリ名
 */
HelloWindow::HelloWindow(unsigned int width, unsigned int height, std::wstring name) : Application(width, height, name)
{

}

/**
 *	@brief	デストラクタ
 */
HelloWindow::~HelloWindow()
{

}

/**
 *	@brief	初期化処理を行う
 */
void HelloWindow::OnInit()
{
#if defined(_DEBUG)
	// Enable the D3D12 debug layer.
	// デバッグレイヤーを有効化
	{
		ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
	}
#endif

	ComPtr<IDXGIFactory4> factory;

	// ファクトリの作成
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
		throw;

	// デバイスの生成
	{
		if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))))
			throw;
	}

	// コマンドキューの生成
	{
		// Describe and create the command queue.
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue))))
			throw;
	}

	// コマンドアロケータの生成
	{
		if (FAILED(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator))))
			throw;
	}

	// コマンドリストの生成
	{
		// Create the command list.
		if (FAILED(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_commandList))))
			throw;

		// Command lists are created in the recording state, but there is nothing
		// to record yet. The main loop expects it to be closed, so close it now.
		// コマンドリストを一旦閉じる
		if (FAILED(m_commandList->Close()))
			throw;
	}

	// スワップチェインの生成
	// ウインドウへの表示やダブルバッファリングなどを行うクラス。
	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = FrameCount;
	swapChainDesc.Width = GetWidth();
	swapChainDesc.Height = GetHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	ComPtr<IDXGISwapChain1> swapChain;

	if (FAILED(factory->CreateSwapChainForHwnd(
		m_commandQueue.Get(),		// Swap chain needs the queue so that it can force a flush on it.
		Win32Frame::GetHwnd(),
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapChain
	)))
		throw;

	// This sample does not support fullscreen transitions.
	if (FAILED(factory->MakeWindowAssociation(Win32Frame::GetHwnd(), DXGI_MWA_NO_ALT_ENTER)))
		throw;

	if (FAILED(swapChain.As(&m_swapChain)))
		throw;

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	// スワップチェインをRenderTargetとして使用するためのDescriptorHeapを作成
	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = FrameCount;				// ダブルバッファリング(フレーム、バック)をするので2つ作成
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;		// 種別はレンダーターゲット
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;	// シェーダからアクセスしない
		if (FAILED(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap))))
			throw;

		// レンダーターゲット分のDescriptorのサイズを取得する
		m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// スワップチェインのバッファを先に作成したDescriptorHeapに登録する
	// Create frame resources.
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

		// Create a RTV for each frame.
		for (UINT n = 0; n < FrameCount; n++)
		{
			if (FAILED(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n]))))
				throw;
			m_device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
			rtvHandle.ptr += 1 * m_rtvDescriptorSize;
		}
	}

	// アセットの読み込み

	// Directx12では描画の終了待ちを自動で行わない(同期が取れず画面がおかしくなる)
	// そのため同期を取るためのオブジェクト(フェンス)を作成する
	// Create synchronization objects.
	{
		if (FAILED(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence))))
			throw;

		m_fenceValue = 1;

		// Create an event handle to use for frame synchronization.
		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (m_fenceEvent == nullptr)
		{
			if (FAILED(HRESULT_FROM_WIN32(GetLastError())))
				throw;
		}
	}
}

/**
 *	@brief	更新処理を行う
 */
void HelloWindow::OnUpdate()
{

}

/**
 *	@brief	描画処理を行う
 */
void HelloWindow::OnRender()
{
	// Command list allocators can only be reset when the associated 
	// command lists have finished execution on the GPU; apps should use 
	// fences to determine GPU execution progress.
	// コマンドアロケータをリセットする(バッファを全て開放する)
	if (FAILED(m_commandAllocator->Reset()))
		throw;

	// However, when ExecuteCommandList() is called on a particular command 
	// list, that command list can then be reset at any time and must be before 
	// re-recording.
	// コマンドリストをリセットする
	if (FAILED(m_commandList->Reset(m_commandAllocator.Get(), m_pipelineState.Get())))
		throw;

	D3D12_RESOURCE_BARRIER barrier;
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = m_renderTargets[m_frameIndex].Get();
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	// Indicate that the back buffer will be used as a render target.
	m_commandList->ResourceBarrier(1, &barrier);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	rtvHandle.ptr = m_rtvHeap->GetCPUDescriptorHandleForHeapStart().ptr + m_frameIndex * m_rtvDescriptorSize;

	// Record commands.
	// コマンドを積む(レンダーターゲットを指定した色でクリアする)
	const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	D3D12_RESOURCE_BARRIER barrier2;
	barrier2.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier2.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier2.Transition.pResource = m_renderTargets[m_frameIndex].Get();
	barrier2.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier2.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	barrier2.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	// Indicate that the back buffer will now be used to present.
	m_commandList->ResourceBarrier(1, &barrier2);

	// コマンドを積み終わったので閉じる
	if (FAILED(m_commandList->Close()))
		throw;

	// Execute the command list.
	// コマンドリストをコマンドキューに実行させる(コマンドキューに移している?)
	ID3D12CommandList* ppCommandLists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

	// Present the frame.
	if (FAILED(m_swapChain->Present(1, 0)))
		throw;

	// WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
	// This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
	// sample illustrates how to use fences for efficient resource usage and to
	// maximize GPU utilization.

	// Signal and increment the fence value.
	// 現在のFence値がコマンド終了後にFenceに書き込まれるようにする
	const UINT64 fence = m_fenceValue;
	if (FAILED(m_commandQueue->Signal(m_fence.Get(), fence)))
		throw;
	m_fenceValue++;

	// Wait until the previous frame is finished.
	// まだコマンドキューが終了していないことを確認する
	// ここまででコマンドキューが終了してしまうとイベントが一切発火されなくなるのでチェックしている
	if (m_fence->GetCompletedValue() < fence)
	{
		// このFenceにおいて、fvalue の値になったらイベントを発火させる
		if (FAILED(m_fence->SetEventOnCompletion(fence, m_fenceEvent)))
			throw;

		// イベントが発火するまで待つ
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

/**
 *	@brief	終了処理を行う
 */
void HelloWindow::OnDestroy()
{
	CloseHandle(m_fenceEvent);
}