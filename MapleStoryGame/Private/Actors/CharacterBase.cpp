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

ACharacterBase::~ACharacterBase()
{
	GEngine->KeyInputSubsystem->ClearKeys();
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitTextureAndPhysics();

	this->InitActions();

	this->InitAnimations();

	this->BindKeys();
}

void ACharacterBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->CheckVelocity();

	RenderComponent->PlayAnimation(fDeltaTime);
}

void ACharacterBase::BindKeys()
{
	GEngine->KeyInputSubsystem->BindKey(VK_LEFT, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.MoveLeft" }));

	GEngine->KeyInputSubsystem->BindKey(VK_RIGHT, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.MoveRight"}));
}

void ACharacterBase::CheckVelocity()
{
	FVector3 Velocity = PhysicsComponent->GetVelocity();

	if (abs(Velocity.x) < 0.01f && abs(Velocity.y) < 0.01f)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
	}
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

	RenderComponent->SetTextureByName("Resources\\Textures\\Avatar\\Idle\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeAsMobFoot(1.0f, Transform.Scale.y * -0.49f, MOB_COLLISION_FLAG);

	RenderComponent->EnableMaterial();
}

void ACharacterBase::InitAnimations()
{
	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Avatar\\Idle", 500);

	RenderComponent->AddAnimationByFolder(EAnimationName::Walk, "Resources\\Textures\\Avatar\\Walk", 100);

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}
