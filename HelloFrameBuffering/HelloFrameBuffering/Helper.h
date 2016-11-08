/**
 *	@file		Helper.h
 *	@brief		�֗��֐��p�w�b�_�t�@�C��
 *	@author		kkllPreciel
 *	@date		2016/10/09
 *	@version	1.0
 */

#pragma once

// include
#include <intsafe.h>

namespace helper
{
	// ��O�`�F�b�N�֐�
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw;
		}
	}

	inline void GetAssetsPath(_Out_writes_(pathSize) WCHAR* path, UINT pathSize)
	{
		if (path == nullptr)
		{
			throw;
		}

		DWORD size = GetModuleFileName(nullptr, path, pathSize);
		if (size == 0 || size == pathSize)
		{
			// Method failed or path was truncated.
			throw;
		}

		WCHAR* lastSlash = wcsrchr(path, L'\\');
		if (lastSlash)
		{
			*(lastSlash + 1) = L'\0';
		}
	}
};