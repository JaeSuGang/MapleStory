#pragma once
#include "GameInstance/GameInstanceSubsystem.h"
#include "Engine/Engine.h"
#include "World/World.h"
#include "Level/Level.h"

class UGameplaySubsystem : public UGameInstanceSubsystem
{
public:
	/* 생성자와 오버라이드 */


public:
	template <typename T>
	void OpenLevel()
	{
		static_assert(std::is_base_of<ULevel, T>::value);

		GEngine->ActiveWorld = std::make_shared<UWorld>();

		GEngine->ActiveWorld->PersistentLevel = std::static_pointer_cast<ULevel>(std::make_shared<T>());

		GEngine->ActiveWorld->LateInit();
	}

private:

};

