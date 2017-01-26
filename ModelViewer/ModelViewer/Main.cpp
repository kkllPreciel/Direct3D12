/**
 *	@file		Main.cpp
 *	@brief		アプリに関する処理を行うプログラムソース
 *	@author		kkllPreciel
 *	@date		2017/01/26
 *	@version	1.0
 */

// include
#include <Windows.h>
#include <fbxsdk.h>

// デバッグモード用include
#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#endif

// デバッグ用(メモリリーク)
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

// 特定の警告の無視
#pragma warning ( disable : 4996 )
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// マクロ( M_PI使用の為 )
#define _USE_MATH_DEFINES

void Load(fbxsdk::FbxNode* pNode)
{
	int count = pNode->GetNodeAttributeCount();

	for (auto i = 0; i < count; ++i)
	{
		auto attribute = pNode->GetNodeAttributeByIndex(i);

		switch (attribute->GetAttributeType())
		{
		case fbxsdk::FbxNodeAttribute::eSkeleton:	// ボーン
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:		// メッシュ
			break;
		default:
			// ボーンとメッシュ以外は無視する
			break;
		}
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
#ifdef _CRTDBG_MAP_ALLOC
	// メモリリークを検出させる
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// 管理クラスを生成
	auto manager = fbxsdk::FbxManager::Create();

	auto importer = FbxImporter::Create(manager, "Importer");

	auto scene = FbxScene::Create(manager, "Scene");

	if (false == importer->Initialize("resource/sample.fbx"))
	{
		// 読み込み失敗
		importer->Destroy();
		manager->Destroy();

		return E_FAIL;
	}

	// 現在のsceneを読み込む
	importer->Import(scene);
	
	// 不要なので削除
	importer->Destroy();

	// ジオメトリコンバータを作成
	FbxGeometryConverter geometryConverter(manager);

	// シーンに含まれる全てのポリゴンを、三角ポリゴンに変換する。
	geometryConverter.Triangulate(scene, true);

	// マテリアル毎にメッシュを分割する
	geometryConverter.SplitMeshesPerMaterial(scene, true);

	// FBX内の構造を取得しておく
	auto root_node = scene->GetRootNode();

	Load(root_node);

	manager->Destroy();

	return S_OK;
}