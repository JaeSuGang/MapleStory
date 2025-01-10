#include "GamePch.h"
#include "Actors/CharacterBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Components/FSMComponent.h"

ACharacterBase::ACharacterBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	FSMComponent = CreateDefaultSubobject<UFSMComponent>();
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(20);
}

void ACharacterBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void ACharacterBase::UIdleState::OnStateEnter()
{
}

void ACharacterBase::UIdleState::OnStateUpdate(float fDeltaTime)
{
}

void ACharacterBase::UIdleState::OnStateExit()
{
}

void ACharacterBase::UMoveState::OnStateEnter()
{
}

void ACharacterBase::UMoveState::OnStateUpdate(float fDeltaTime)
{
}

void ACharacterBase::UMoveState::OnStateExit()
{
}
