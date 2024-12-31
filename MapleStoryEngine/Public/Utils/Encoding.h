#pragma once
#include "EnginePch.h"

static std::wstring StringToWString(string strInput)
{
	if (strInput.size() == 0)
		return std::wstring();

	int SizeNeeded = MultiByteToWideChar(CP_ACP, 0, strInput.data(), -1, nullptr, 0);

	std::wstring NewWString{};

	NewWString.resize(SizeNeeded);

	int Size = MultiByteToWideChar(CP_ACP, 0, strInput.data(), -1, &NewWString[0], SizeNeeded);

	return NewWString;
}