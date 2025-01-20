#include "GamePch.h"
#include "Actors/Monsters/MobBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Actions/BP_TakeDamageAction.h"

AMobBase::AMobBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();
}

void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitAttributes();

	this->InitTexture();

	this->InitAnimations();

	this->InitActions();

	this->InitPhysics();

	RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
}

void AMobBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	RenderComponent->PlayAnimation(fDeltaTime);
}

void AMobBase::InitAttributes()
{

}

void AMobBase::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(8);
}

void AMobBase::InitAnimations()
{
	RenderComponent->EnableAnimation();

}

void AMobBase::InitActions()
{
	ActionComponent->AddAction<BP_TakeDamageAction>();
}

void AMobBase::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeFootCollider(Transform.Scale.y * -0.49f);

	PhysicsComponent->InitializeHitbox(Transform.Scale.x, Transform.Scale.y);
}
