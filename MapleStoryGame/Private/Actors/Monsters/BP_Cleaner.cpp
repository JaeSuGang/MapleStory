#include "GamePch.h"
#include "Actors/Monsters/BP_Cleaner.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"

BP_Cleaner::BP_Cleaner()
{
	MobResourcePath = "8643000.img";
}

void BP_Cleaner::InitAttributes()
{
	Super::InitAttributes();

	AttributeComponent->AddAttribute("Value.Hp", 10000.0f);
	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}
