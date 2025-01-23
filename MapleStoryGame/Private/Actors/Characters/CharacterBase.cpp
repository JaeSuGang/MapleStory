#include "GamePch.h"
#include "Actors/Characters/CharacterBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Engine/KeyInputSubsystem.h"
#include "Actions/BP_MoveLeftAction.h"
#include "Actions/BP_MoveRightAction.h"
#include "Actions/BP_JumpAction.h"
#include "Actions/BP_ProneAction.h"
#include "Components/MapleCameraComponent.h"



ACharacterBase::ACharacterBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();

	CameraComponent = CreateDefaultSubobject<UMapleCameraComponent>();
	CameraComponent->SetMainCamera(true);
}

ACharacterBase::~ACharacterBase()
{
	GEngine->KeyInputSubsystem->ClearKeys(UKeyInputSubsystem::EInputMappingContext::Game);
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitTextures();

	this->InitPhysics();

	this->InitActions();

	this->InitAnimations();

	this->BindKeys();
}

void ACharacterBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->CheckFalling();

	this->DecideAnimation();

	RenderComponent->PlayAnimation(fDeltaTime);
}

void ACharacterBase::LateTick(float fDeltaTime)
{
	AttributeComponent->RemoveAttribute("Status.Walking");

	AttributeComponent->RemoveAttribute("Status.Proning");
}

void ACharacterBase::BindKeys()
{
	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, VK_LEFT, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{ "Action.MoveLeft" }));

	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, VK_RIGHT, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.MoveRight"}));

	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, VK_DOWN, UKeyInputSubsystem::EKeyState::Triggered, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.Prone"}));

	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, VK_SPACE, UKeyInputSubsystem::EKeyState::KeyDown, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.Jump"}));

	GEngine->KeyInputSubsystem->BindKey(UKeyInputSubsystem::EInputMappingContext::Game, VK_SPACE, UKeyInputSubsystem::EKeyState::KeyDown, std::bind(&UActionComponent::StartActionByName, ActionComponent, this, string{"Action.DoubleJump"}));

	
}

void ACharacterBase::DecideAnimation()
{
	if (AttributeComponent->ContainsAttribute("Status.Attacking"))
		return;

	if (AttributeComponent->HasAttributeExact("Status.Falling"))
		RenderComponent->SetCurrentAnimation(EAnimationName::Jump);

	else if (AttributeComponent->HasAttributeExact("Status.Proning"))
		RenderComponent->SetCurrentAnimation(EAnimationName::Prone);

	else if (AttributeComponent->HasAttributeExact("Status.Walking"))
		RenderComponent->SetCurrentAnimation(EAnimationName::Walk);

	else
		RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void ACharacterBase::CheckFalling()
{
	bool bIsGrounded = PhysicsComponent->GetIsGrounded();

	if (bIsGrounded)
	{
		FVector3 Vel = PhysicsComponent->GetVelocity();
		if (abs(Vel.y) < 5.0f)
		{
			AttributeComponent->RemoveAttribute("Status.Falling");
			AttributeComponent->AddAttribute("Status.CanDoubleJump");
		}
	}
	else
		AttributeComponent->AddAttribute("Status.Falling");

}

void ACharacterBase::InitActions()
{
	ActionComponent->AddAction<BP_ProneAction>();

	ActionComponent->AddAction<BP_MoveLeftAction>();

	ActionComponent->AddAction<BP_MoveRightAction>();

	ActionComponent->AddAction<BP_JumpAction>();

}

void ACharacterBase::InitTextures()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(RENDER_LAYER_CHARACTER);

	RenderComponent->EnableMaterial();
}

void ACharacterBase::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeCharacterFootCollider(Transform.Scale.y * -0.49f);
}

void ACharacterBase::InitAnimations()
{
	RenderComponent->EnableAnimation();
}

void ACharacterBase::SetPosition(FVector3 _Position)
{
	PhysicsComponent->SetPosition(_Position);
}