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

#include "Widgets/BP_HPWidget.h"


ACharacterBase::ACharacterBase()
{
	HPFlickerIndex = 1;

	LastInterpolatedHP = 0.0f;

	LastInterpolatedMP = 0.0f;

	GaugeInterpolateTimer = 0.0f;

	FlickerTimer = 0.0f;

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

	this->InitAttributes();

	this->BindKeys();

	HPWidget = GEngine->GetGameInstance()->AddWidget<BP_HPWidget>(0);
}

void ACharacterBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->CheckFalling();

	this->DecideAnimation();

	this->InterpolateDamageAnimation(fDeltaTime);

	this->DamageFlickerAnimation(fDeltaTime);

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

void ACharacterBase::TakeDamage(float _fValue)
{
	AttributeComponent->AddAttributeValue("Value.Hp", -1.0f * _fValue);
	FlickerTimer = 2.0f;
}

float ACharacterBase::GetDamage() const
{
	return AttributeComponent->GetAttributeValue("Value.Damage");
}

void ACharacterBase::DamageFlickerAnimation(float _fDeltaTime)
{
	FlickerTimer -= _fDeltaTime;

	if (FlickerTimer > 0.0f)
	{
		float _Temp1 = std::fmodf(FlickerTimer, 0.1f);

		if (_Temp1 < 0.05f)
			RenderComponent->SetPixelShaderByName(DARK_PIXEL_SHADER_NAME);
		else
			RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	}
	else
	{
		RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	}
}

void ACharacterBase::InterpolateDamageAnimation(float _fDeltaTime)
{
	float _MaxHP = AttributeComponent->GetAttributeValue("Value.MaxHp");

	float _HP = AttributeComponent->GetAttributeValue("Value.Hp");

	if (GaugeInterpolateTimer <= 0.0f && abs(_HP - LastInterpolatedHP) > 1)
	{
		GaugeInterpolateTimer = 0.05f;

		float _fLerpRatio = 0.536f;

		LastInterpolatedHP = _HP * _fLerpRatio + (LastInterpolatedHP * (1.0f - _fLerpRatio));

		HPWidget->SetLifeGauge(LastInterpolatedHP / _MaxHP);
	}
	else
	{
		GaugeInterpolateTimer -= _fDeltaTime;
	}
}

void ACharacterBase::DecideAnimation()
{
	if (AttributeComponent->ContainsAttribute("Status.Attacking"))
	{
		if (AttributeComponent->ContainsAttribute("Status.Attacking.ShootMoving"))
		{
			AttributeComponent->RemoveAttribute("Status.Attacking.ShootMoving");
		}
		return;
	}


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

void ACharacterBase::InitAttributes()
{
	AttributeComponent->AddAttribute("ActorType.Character");

	AttributeComponent->AddAttribute("Value.Hp");
	AttributeComponent->SetAttributeValue("Value.Hp", 50000);

	AttributeComponent->AddAttribute("Value.MaxHp");
	AttributeComponent->SetAttributeValue("Value.MaxHp", 50000);

	AttributeComponent->AddAttribute("Value.Damage");
	AttributeComponent->SetAttributeValue("Value.Damage", 52'000'000);
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