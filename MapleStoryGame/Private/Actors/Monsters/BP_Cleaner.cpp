#include "GamePch.h"
#include "Actors/Monsters/BP_Cleaner.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"

void BP_Cleaner::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\8643000.img\\stand\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_Cleaner::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Stand, "Resources\\Textures\\Monsters\\8643000.img\\stand", 150);

	RenderComponent->AddAnimationByFolder(EAnimationName::Move, "Resources\\Textures\\Monsters\\8643000.img\\move", 150);

	RenderComponent->AddAnimationByFolder(EAnimationName::Hit, "Resources\\Textures\\Monsters\\8643000.img\\hit", 500);
}

void BP_Cleaner::InitActions()
{
	Super::InitActions();
}

void BP_Cleaner::InitAttributes()
{
	Super::InitAttributes();

	AttributeComponent->AddAttribute("Value.Hp", 10000.0f);
	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}
