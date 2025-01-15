#include "GamePch.h"
#include "Levels/TestLevel.h"
#include "Levels/MapBase.h"
#include "World/World.h"
#include "Actors/CharacterBase.h"

void UTestLevel::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map4.450003000.img.xml", "Lacheln.img.xml");

	MainActor = GetWorld()->SpawnActor<ACharacterBase>();
}

void UTestLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
