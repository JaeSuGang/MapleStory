#include "GamePch.h"
#include "Actors/Characters/BP_WindBreaker.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Engine/Engine.h"
#include "Engine/KeyInputSubsystem.h"

#include "Actions/BP_DoubleJumpAction.h"
#include "Actions/BP_GustShiftAction.h"
#include "Actions/BP_FairyTurnAction.h"
#include "Actions/BP_IdleWhimAction.h"

void BP_WindBreaker::InitActions()
{
	Super::InitActions();

	ActionComponent->AddAction<BP_DoubleJumpAction>();

	ActionComponent->AddAction<BP_GustShiftAction>();

	ActionComponent->AddAction<BP_FairyTurnAction>();

	ActionComponent->AddAction<BP_IdleWhimAction>();

}

void BP_WindBreaker::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Avatars\\WindBreaker\\Idle", 500);

	RenderComponent->AddAnimationByFolder(EAnimationName::Walk, "Resources\\Textures\\Avatars\\WindBreaker\\Walk", 120);

	RenderComponent->AddAnimationByFolder(EAnimationName::Jump, "Resources\\Textures\\Avatars\\WindBreaker\\Jump", 0);

	RenderComponent->AddAnimationByFolder(EAnimationName::SwingT1, "Resources\\Textures\\Avatars\\WindBreaker\\SwingT1", 60);

	RenderComponent->AddAnimationByFolder(EAnimationName::Prone, "Resources\\Textures\\Avatars\\WindBreaker\\Prone", 60);

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void BP_WindBreaker::InitTextures()
{
	Super::InitTextures();

	RenderComponent->SetTextureByName("Resources\\Textures\\Avatars\\WindBreaker\\Idle\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_WindBreaker::BindKeys()
{
	Super::BindKeys();

	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, 'S', UKeyInputSubsystem::EKeyState::KeyDown, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.FairyTurn" }));

	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, 'R', UKeyInputSubsystem::EKeyState::KeyDown, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.IdleWhim" }));
}
