#include "GamePch.h"
#include "Levels/LachelnDreamForest.h"
#include "Actors/Characters/BP_WindBreaker.h"
#include "Actors/Boss/BP_LucidBoss_0.h"
#include "World/World.h"

void ULachelnDreamForest::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map4.450004750.img.xml", "Lacheln.img.xml");

	MainActor = GetWorld()->SpawnActorReturnShared<BP_WindBreaker>();

	BP_LucidBoss_0* LucidPhase1 = GetWorld()->SpawnActor<BP_LucidBoss_0>();
	LucidPhase1->SetPosition({1000.0f, 250.0f, 0.0f});

	
}

void ULachelnDreamForest::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}