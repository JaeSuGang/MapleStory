#include "GamePch.h"
#include "Actors/CharacterBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Engine/KeyInputSubsystem.h"
#include "Actions/BP_MoveLeftAction.h"
#include "Actions/BP_MoveRightAction.h"
#include "Actions/BP_JumpAction.h"
#include "Actions/BP_FairyTurnAction.h"



ACharacterBase::ACharacterBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();
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

	this->CheckFalling();

	RenderComponent->PlayAnimation(fDeltaTime);
}

void ACharacterBase::BindKeys()
{
	GEngine->KeyInputSubsystem->BindKey(VK_LEFT, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.MoveLeft" }));

	GEngine->KeyInputSubsystem->BindKey(VK_RIGHT, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.MoveRight"}));

	GEngine->KeyInputSubsystem->BindKey(VK_SPACE, UKeyInputSubsystem::EKeyState::KeyDown, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.Jump"}));

	GEngine->KeyInputSubsystem->BindKey('S', UKeyInputSubsystem::EKeyState::KeyDown, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.FairyTurn"}));
}

void ACharacterBase::CheckFalling()
{
	if (PhysicsComponent->GetIsGrounded())
		AttributeComponent->RemoveAttribute("Status.Falling");
	else
		AttributeComponent->AddAttribute("Status.Falling");

}

void ACharacterBase::InitActions()
{
	ActionComponent->AddAction<BP_MoveLeftAction>();

	ActionComponent->AddAction<BP_MoveRightAction>();

	ActionComponent->AddAction<BP_JumpAction>();

	ActionComponent->AddAction<BP_FairyTurnAction>();
}

void ACharacterBase::InitTextureAndPhysics()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(9);

	RenderComponent->EnableMaterial();

	RenderComponent->SetTextureByName("Resources\\Textures\\Avatar\\Idle\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeFootCollider(Transform.Scale.y * -0.49f, MOB_COLLISION_FLAG);

}

void ACharacterBase::InitAnimations()
{
	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Avatar\\Idle", 500);

	RenderComponent->AddAnimationByFolder(EAnimationName::Walk, "Resources\\Textures\\Avatar\\Walk", 120);

	RenderComponent->AddAnimationByFolder(EAnimationName::Jump, "Resources\\Textures\\Avatar\\Jump", 0);

	RenderComponent->AddAnimationByFolder(EAnimationName::SwingT1, "Resources\\Textures\\Avatar\\SwingT1", 60);

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}
