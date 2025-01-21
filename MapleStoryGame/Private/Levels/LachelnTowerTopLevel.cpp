#include "GamePch.h"
#include "Levels/LachelnTowerTopLevel.h"
#include "Actors/Characters/BP_WindBreaker.h"
#include "World/World.h"

void ULachelnTowerTopLevel::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map4.450004000.img.xml", "Lacheln.img.xml");

	MainActor = GetWorld()->SpawnActorReturnShared<BP_WindBreaker>();
}

void ULachelnTowerTopLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}