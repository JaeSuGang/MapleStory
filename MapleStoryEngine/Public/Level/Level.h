#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class AActor;
class UWorld;

class ULevel : public UObject
{
	friend class UWorld;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API ULevel();

	ENGINE_API virtual void BeginPlay() = 0;

	ENGINE_API virtual void Tick(float fDeltaTime) = 0;

public:
	ENGINE_API UWorld* GetWorld() const;

	ENGINE_API void SetWorld(UWorld* _World);

protected:
	UWorld* World;
	vector<shared_ptr<AActor>> Actors;
	vector<AActor*> ActorsToDestroy;
	vector<AActor*> ActorsToBeginPlay;
};

