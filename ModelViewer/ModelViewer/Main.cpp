/**
 *	@file		Main.cpp
 *	@brief		�A�v���Ɋւ��鏈�����s���v���O�����\�[�X
 *	@author		kkllPreciel
 *	@date		2017/01/26
 *	@version	1.0
 */

// include
#include <Windows.h>
#include <fbxsdk.h>

// �f�o�b�O���[�h�pinclude
#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#endif

// �f�o�b�O�p(���������[�N)
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

// ����̌x���̖���
#pragma warning ( disable : 4996 )
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// �}�N��( M_PI�g�p�̈� )
#define _USE_MATH_DEFINES

void Load(fbxsdk::FbxNode* pNode)
{
	int count = pNode->GetNodeAttributeCount();

	for (auto i = 0; i < count; ++i)
	{
		auto attribute = pNode->GetNodeAttributeByIndex(i);

		switch (attribute->GetAttributeType())
		{
		case fbxsdk::FbxNodeAttribute::eSkeleton:	// �{�[��
			break;
		case fbxsdk::FbxNodeAttribute::eMesh:		// ���b�V��
			break;
		default:
			// �{�[���ƃ��b�V���ȊO�͖�������
			break;
		}
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
#ifdef _CRTDBG_MAP_ALLOC
	// ���������[�N�����o������
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// �Ǘ��N���X�𐶐�
	auto manager = fbxsdk::FbxManager::Create();

	auto importer = FbxImporter::Create(manager, "Importer");

	auto scene = FbxScene::Create(manager, "Scene");

	if (false == importer->Initialize("resource/sample.fbx"))
	{
		// �ǂݍ��ݎ��s
		importer->Destroy();
		manager->Destroy();

		return E_FAIL;
	}

	// ���݂�scene��ǂݍ���
	importer->Import(scene);
	
	// �s�v�Ȃ̂ō폜
	importer->Destroy();

	// �W�I���g���R���o�[�^���쐬
	FbxGeometryConverter geometryConverter(manager);

	// �V�[���Ɋ܂܂��S�Ẵ|���S�����A�O�p�|���S���ɕϊ�����B
	geometryConverter.Triangulate(scene, true);

	// �}�e���A�����Ƀ��b�V���𕪊�����
	geometryConverter.SplitMeshesPerMaterial(scene, true);

	// FBX���̍\�����擾���Ă���
	auto root_node = scene->GetRootNode();

	Load(root_node);

	manager->Destroy();

	return S_OK;
}