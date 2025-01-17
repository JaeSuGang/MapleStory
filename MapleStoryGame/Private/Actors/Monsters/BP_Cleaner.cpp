#include "GamePch.h"
#include "Actors/Monsters/BP_Cleaner.h"
#include "Attributes/AttributeComponent.h"

void BP_Cleaner::SetTexture()
{
	Super::SetTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\3003249.img\\stand\\1.png");
	RenderComponent->SetActorScaleByTextureSize();
}

void BP_Cleaner::SetAttributes()
{
	Super::SetAttributes();

	AttributeComponent->AddAttribute("Value.Hp", 10000.0f);
	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}
