/**
 *	@file		HelloTriangle.cpp
 *	@brief		アプリケーションに関する処理を行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2016/10/09
 *	@version	1.0
 */

#include <d3dcompiler.h>
#include "HelloTriangle.h"
#include "Win32Frame.h"
#include "Helper.h"

/**
 *	@brief	引数付きコンストラクタ
 *	@param	width:横幅
 *	@param	height:縦幅
 *	@param	name:アプリ名
 */
HelloTriangle::HelloTriangle(unsigned int width, unsigned int height, std::wstring name) : Application(width, height, name)
{

}

/**
 *	@brief	デストラクタ
 */
HelloTriangle::~HelloTriangle()
{

}

/**
 *	@brief	初期化処理を行う
 */
void HelloTriangle::OnInit()
{
	CreatePipeline();
}

/**
 *	@brief	パイプラインを作成する
 */
void HelloTriangle::CreatePipeline()
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
 *	@brief	アセットを読み込む
 */
void HelloTriangle::LoadAssets()
{
	// Create an empty root signature.
	{
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;

		rootSignatureDesc.NumParameters = 0;
		rootSignatureDesc.pParameters = nullptr;
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pStaticSamplers = nullptr;
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ComPtr<ID3DBlob> signature;
		ComPtr<ID3DBlob> error;

		helper::ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
		helper::ThrowIfFailed(m_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootSignature)));
	}

	// Create the pipeline state, which includes compiling and loading shaders.
	{
		ComPtr<ID3DBlob> vertexShader;
		ComPtr<ID3DBlob> pixelShader;

#if defined(_DEBUG)
		// Enable better shader debugging with the graphics debugging tools.
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif

		helper::ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"shaders.hlsl").c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
		helper::ThrowIfFailed(D3DCompileFromFile(GetAssetFullPath(L"shaders.hlsl").c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = m_rootSignature.Get();

		D3D12_SHADER_BYTECODE vs;
		vs.pShaderBytecode = vertexShader.Get()->GetBufferPointer();
		vs.BytecodeLength = vertexShader.Get()->GetBufferSize();
		psoDesc.VS = vs;

		D3D12_SHADER_BYTECODE ps;
		ps.pShaderBytecode = pixelShader.Get()->GetBufferPointer();
		ps.BytecodeLength = pixelShader.Get()->GetBufferSize();
		psoDesc.PS = ps;

		D3D12_RASTERIZER_DESC rasterizer_desc;
		rasterizer_desc.FillMode = D3D12_FILL_MODE_SOLID;
		rasterizer_desc.CullMode = D3D12_CULL_MODE_BACK;
		rasterizer_desc.FrontCounterClockwise = FALSE;
		rasterizer_desc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
		rasterizer_desc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
		rasterizer_desc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
		rasterizer_desc.DepthClipEnable = TRUE;
		rasterizer_desc.MultisampleEnable = FALSE;
		rasterizer_desc.AntialiasedLineEnable = FALSE;
		rasterizer_desc.ForcedSampleCount = 0;
		rasterizer_desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
		psoDesc.RasterizerState = rasterizer_desc;

		D3D12_BLEND_DESC blend_desc;
		blend_desc.AlphaToCoverageEnable = FALSE;
		blend_desc.IndependentBlendEnable = FALSE;
		const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
		{
			FALSE,FALSE,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
			D3D12_LOGIC_OP_NOOP,
			D3D12_COLOR_WRITE_ENABLE_ALL,
		};
		for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
			blend_desc.RenderTarget[i] = defaultRenderTargetBlendDesc;

		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		helper::ThrowIfFailed(m_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)));
	}

	// Create the command list.
	helper::ThrowIfFailed(m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), m_pipelineState.Get(), IID_PPV_ARGS(&m_commandList)));

	// Command lists are created in the recording state, but there is nothing
	// to record yet. The main loop expects it to be closed, so close it now.
	helper::ThrowIfFailed(m_commandList->Close());

	// Create the vertex buffer.
	{
		float aspect = GetAspect();

		// Define the geometry for a triangle.
		Vertex triangleVertices[] =
		{
			{ { 0.0f, 0.25f * aspect, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 0.25f, -0.25f * aspect, 0.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.25f, -0.25f * aspect, 0.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } }
		};

		const UINT vertexBufferSize = sizeof(triangleVertices);

		D3D12_HEAP_PROPERTIES properties;
		properties.Type = D3D12_HEAP_TYPE_UPLOAD;
		properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		properties.CreationNodeMask = 1;
		properties.VisibleNodeMask = 1;

		D3D12_RESOURCE_DESC resource_desc;
		resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resource_desc.Alignment = 0;
		resource_desc.Width = vertexBufferSize;
		resource_desc.Height = 1;
		resource_desc.DepthOrArraySize = 1;
		resource_desc.MipLevels = 1;
		resource_desc.Format = DXGI_FORMAT_UNKNOWN;
		resource_desc.SampleDesc.Count = 1;
		resource_desc.SampleDesc.Quality = 0;
		resource_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resource_desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		D3D12_RANGE range;
		range.Begin = range.End = 0;

		// Note: using upload heaps to transfer static data like vert buffers is not 
		// recommended. Every time the GPU needs it, the upload heap will be marshalled 
		// over. Please read up on Default Heap usage. An upload heap is used here for 
		// code simplicity and because there are very few verts to actually transfer.
		helper::ThrowIfFailed(m_device->CreateCommittedResource(
			&properties,
			D3D12_HEAP_FLAG_NONE,
			&resource_desc,
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&m_vertexBuffer)));

		// Copy the triangle data to the vertex buffer.
		UINT8* pVertexDataBegin;
		// We do not intend to read from this resource on the CPU.
		helper::ThrowIfFailed(m_vertexBuffer->Map(0, &range, reinterpret_cast<void**>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
		m_vertexBuffer->Unmap(0, nullptr);

		// Initialize the vertex buffer view.
		m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
		m_vertexBufferView.StrideInBytes = sizeof(Vertex);
		m_vertexBufferView.SizeInBytes = vertexBufferSize;
	}
}

/**
 *	@brief	更新処理を行う
 */
void HelloTriangle::OnUpdate()
{

}

/**
 *	@brief	描画処理を行う
 */
void HelloTriangle::OnRender()
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
void HelloTriangle::OnDestroy()
{
	CloseHandle(m_fenceEvent);
}