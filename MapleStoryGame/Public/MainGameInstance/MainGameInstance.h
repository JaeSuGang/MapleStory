#pragma once
#include "GameInstance/GameInstance.h"

class UGameplayTagsManager;

class UMainGameInstance : public UGameInstance
{
	typedef UGameInstance Super;

public:
	/* Constructors and Overrides */
	UMainGameInstance();

	void BeginPlay() override;

public:
	

	UGameplayTagsManager* GetGameplayTagManager() { return GameplayTagManager; }
	

protected:
	UGameplayTagsManager* GameplayTagManager;
};

