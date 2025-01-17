#include "GamePch.h"
#include "Actors/Monsters/MobBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Attributes/AttributeComponent.h"

AMobBase::AMobBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();
}

void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	this->SetAttributes();

	this->SetTexture();

	this->InitPhysics();
}

void AMobBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

}

void AMobBase::SetAttributes()
{

}

void AMobBase::SetTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(8);
}

void AMobBase::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeFootCollider(Transform.Scale.y * -0.49f);

	PhysicsComponent->InitializeHitbox(Transform.Scale.x, Transform.Scale.y);
}
