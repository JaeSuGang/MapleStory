#include "GamePch.h"
#include "Levels/TestLevel2.h"

void UTestLevel2::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map1.120040000.img.xml", "Lacheln.img.xml");
}

void UTestLevel2::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}