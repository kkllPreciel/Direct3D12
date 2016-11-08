/**
 *	@file		Helper.h
 *	@brief		便利関数用ヘッダファイル
 *	@author		kkllPreciel
 *	@date		2016/10/09
 *	@version	1.0
 */

#pragma once

// include
#include <intsafe.h>

namespace helper
{
	// 例外チェック関数
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