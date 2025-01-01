#pragma once
#include "EnginePch.h"

namespace Utils
{
	static void ParseString(string StringToParse, char SplitChar, vector<string>& ReturnVector)
	{
		string TempParentName;

		for (char c : StringToParse)
		{
			if (c == SplitChar)
			{
				ReturnVector.push_back(TempParentName);
				TempParentName.clear();
			}

			else
				TempParentName.push_back(c);
		}
	}

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
}