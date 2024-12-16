#include "EnginePch.h"
#include "Engine/Engine.h"
#include "Engine/DebugSubsystem.h"
#include "Utils.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "GameplayTags/GameplayTag.h"

UGameplayTagsManager::UGameplayTagsManager()
{
	RegisteredTags.reserve(REGISTERED_TAGS_RESERVE_COUNT);

	ParentIDs.reserve(REGISTERED_TAGS_RESERVE_COUNT);

	StringMappedIDs.reserve(REGISTERED_TAGS_RESERVE_COUNT);

	RegisterTag("Null");
}

void UGameplayTagsManager::ExtractParentsFromString(const string StringToParse, vector<string>& Parents)
{
	vector<string> SplittedString;
	Utils::ParseString(StringToParse, '.', SplittedString);

	for (int i = 0; i < SplittedString.size(); i++)
	{
		string ParentString{};
		for (int j = 0; j <= i; j++)
		{
			ParentString += SplittedString[j];
			ParentString += '.';
		}
		ParentString.pop_back();

		Parents.push_back(ParentString);
	}
}

FGameplayTag UGameplayTagsManager::FindRegisteredTagExact(string TagName)
{
	int ID = FindRegisteredTagIDExact(TagName);

	return RegisteredTags[ID];
}

int UGameplayTagsManager::FindRegisteredTagIDExact(string TagName)
{
	unordered_map<string, int>::iterator FindIter = StringMappedIDs.find(TagName);

	if (FindIter == StringMappedIDs.end())
		return 0;

	return FindIter->second;
}

ENGINE_API void UGameplayTagsManager::RegisterTag(string TagName)
{
	if (FindRegisteredTagIDExact(TagName) != 0)
		return;


	vector<int> TempParentsInt{};
	vector<string> TempParentsString{};

	ExtractParentsFromString(TagName, TempParentsString);

	for (string& ParentString : TempParentsString)
	{
		RegisterTag(ParentString);
		int ParentID = FindRegisteredTagIDExact(ParentString);
		TempParentsInt.push_back(ParentID);
	}

	int NewID = (int)RegisteredTags.size();

	FGameplayTag NewTag{};
	NewTag.ID = NewID;
	NewTag.TagName = TagName;

	RegisteredTags.push_back(NewTag);

	ParentIDs.push_back(TempParentsInt);

	StringMappedIDs.insert(std::make_pair(TagName, NewID));

}
