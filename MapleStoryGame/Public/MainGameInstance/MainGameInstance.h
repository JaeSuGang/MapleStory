#pragma once
#include "GameInstance/GameInstance.h"

class UGameplayTagsManager;

class UMainGameInstance : public UGameInstance
{
public:
	/* Constructors and Overrides */
	UMainGameInstance();

public:
	UGameplayTagsManager* GetGameplayTagManager() { return GameplayTagManager; }
	

protected:
	UGameplayTagsManager* GameplayTagManager;
};

