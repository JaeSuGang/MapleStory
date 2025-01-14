#include "GamePch.h"
#include "Actors/CharacterBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Engine/KeyInputSubsystem.h"
#include "Actions/BP_MoveLeftAction.h"
#include "Actions/BP_MoveRightAction.h"


ACharacterBase::ACharacterBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitTextureAndPhysics();

	this->InitActions();

	this->BindKeys();
}

void ACharacterBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void ACharacterBase::BindKeys()
{
	GEngine->KeyInputSubsystem->BindKey('A', UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.MoveLeft" }));
	GEngine->KeyInputSubsystem->BindKey('D', UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.MoveRight" }));
}

void ACharacterBase::InitActions()
{
	ActionComponent->AddAction<BP_MoveLeftAction>();

	ActionComponent->AddAction<BP_MoveRightAction>();
}

void ACharacterBase::InitTextureAndPhysics()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(9);

	RenderComponent->SetTextureByName("Resources\\Textures\\Avatar\\stand_0.png");

	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeAsMobFoot(1.0f, Transform.Scale.y * -0.49f, MOB_COLLISION_FLAG);
}
