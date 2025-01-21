#include "GamePch.h"
#include "Levels/LachelnDreamForest.h"
#include "Actors/Characters/BP_WindBreaker.h"
#include "World/World.h"

void ULachelnDreamForest::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map4.450004750.img.xml", "Lacheln.img.xml");

	MainActor = GetWorld()->SpawnActorReturnShared<BP_WindBreaker>();
}

void ULachelnDreamForest::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}