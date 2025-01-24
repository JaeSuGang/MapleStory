#include "GamePch.h"
#include "Actors/Skills/AtomBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "World/World.h"

AAtomBase::AAtomBase()
{
	IsHit = false;

	LifeTime = 0.0f;

	ElapsedTime = 0.0f;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
}

void AAtomBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitTexture();

	this->InitAnimations();

	this->InitPhysics();

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void AAtomBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	ElapsedTime += fDeltaTime;
	LifeTime -= fDeltaTime;

	RenderComponent->PlayAnimation(fDeltaTime);

	if (LifeTime < 0.0f)
		this->Destroy();

	else if (LifeTime < 1.0f)
		RenderComponent->AddAlphaValue(-fDeltaTime);
}

void AAtomBase::SetPosition(FVector3 _Position)
{
	if (PhysicsComponent->GetBodyID().index1 == 0)
		Super::SetPosition(_Position);

	else
		PhysicsComponent->SetPosition(_Position);
}

void AAtomBase::SetRotation(FVector3 _Rotation)
{
	if (PhysicsComponent->GetBodyID().index1 == 0)
		Super::SetRotation(_Rotation);

	else
		PhysicsComponent->SetRotation(_Rotation);
}

void AAtomBase::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(1);

	RenderComponent->SetSortingLayer(RENDER_LAYER_FRONT_SKILL);
}

void AAtomBase::InitAnimations()
{
	RenderComponent->EnableAnimation();
}

void AAtomBase::InitPhysics()
{
	PhysicsComponent->InitializeBodyWithNoGravity(b2BodyType::b2_dynamicBody);
}

