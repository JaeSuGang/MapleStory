#include "EnginePch.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actor/Actor.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"

#define GRAVITY_SCALE 600.0f

UPhysicsComponent::UPhysicsComponent()
{
	PhysicsSubsystem = GEngine->GetWorld()->PhysicsSubsystem;
}

UPhysicsComponent::~UPhysicsComponent()
{
	if (B2BodyID.index1)
	{
		b2DestroyBody(B2BodyID);
	}
}

void UPhysicsComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);

	FTransform& OwnerTransfrom = Owner->GetTransform();
	b2Vec2 B2Position = b2Body_GetPosition(this->B2BodyID);
	OwnerTransfrom.Position.x = B2Position.x;
	OwnerTransfrom.Position.y = B2Position.y;
}

void UPhysicsComponent::InitializeAsDynamicRigidBody()
{
	FTransform OwnerTransform = Owner->GetTransform();
	b2WorldId B2WorldID = PhysicsSubsystem->B2WorldID;

	b2BodyDef BodyDef = b2DefaultBodyDef();

	BodyDef.type = b2_dynamicBody;
	BodyDef.gravityScale = GRAVITY_SCALE;
	BodyDef.linearDamping = 0.0f;
	BodyDef.position.x = OwnerTransform.Position.x;
	BodyDef.position.y = OwnerTransform.Position.y;

	this->B2BodyID = b2CreateBody(B2WorldID, &BodyDef);

	b2Polygon dynamicBox = b2MakeBox(500.0f, 100.0f);
	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1000.0f;
	shapeDef.friction = 0.3f;

	b2CreatePolygonShape(B2BodyID, &shapeDef, &dynamicBox);
}

void UPhysicsComponent::InitializeAsStatic()
{
	FTransform OwnerTransform = Owner->GetTransform();
	b2WorldId B2WorldID = PhysicsSubsystem->B2WorldID;

	b2BodyDef BodyDef = b2DefaultBodyDef();

	BodyDef.type = b2_staticBody;
	BodyDef.position.x = OwnerTransform.Position.x ;
	BodyDef.position.y = OwnerTransform.Position.y ;

	this->B2BodyID = b2CreateBody(B2WorldID, &BodyDef);

	b2Polygon Box = b2MakeBox(1.0f, 1.0f);
	b2ShapeDef shapeDef = b2DefaultShapeDef();

	b2CreatePolygonShape(B2BodyID, &shapeDef, &Box);
}

void UPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();
}
