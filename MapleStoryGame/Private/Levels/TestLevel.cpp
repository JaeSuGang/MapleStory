#include "GamePch.h"
#include "Levels/TestLevel.h"
#include "Levels/MapBase.h"

void UTestLevel::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map4.450003000.img.xml", "Resources\\XMLs\\Map.Obj.Lacheln.img.xml");
}

void UTestLevel::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
