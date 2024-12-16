#pragma once
#include "EnginePch.h"

namespace Utils
{
	void ParseString(string StringToParse, char SplitChar, vector<string>& ReturnVector)
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
}