#include "EnginePch.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actor/Actor.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "Engine/TimeSubsystem.h"

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

	OwnerTransfrom.Position.x = B2Position.x * METER_TO_PIXEL_CONSTANT;
	OwnerTransfrom.Position.y = B2Position.y * METER_TO_PIXEL_CONSTANT;
}

void UPhysicsComponent::AddXVelocity(float _x)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	Velocity.x += _x;

	b2Body_SetLinearVelocity(B2BodyID, Velocity);
}

void UPhysicsComponent::AddYVelocity(float _y)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	Velocity.y += _y;

	b2Body_SetLinearVelocity(B2BodyID, Velocity);
}

FVector3 UPhysicsComponent::GetVelocity() const
{
	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	return { Velocity.x, Velocity.y, 0.0f };
}

void UPhysicsComponent::SetXVelocity(float _x)
{
	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	Velocity.x = _x;

	b2Body_SetLinearVelocity(B2BodyID, Velocity);
}

void UPhysicsComponent::InitializeAsFoothold(float x1, float y1, float x2, float y2)
{
	IsLine = true;

	x1 = x1 * PIXEL_TO_METER_CONSTANT;
	x2 = x2 * PIXEL_TO_METER_CONSTANT;
	y1 = y1 * PIXEL_TO_METER_CONSTANT;
	y2 = y2 * PIXEL_TO_METER_CONSTANT;

	b2BodyDef BodyDef = b2DefaultBodyDef();
	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	b2Segment Segment{ {0.0f, 0.0f}, {x2 - x1, y2 - y1} };

	BodyDef.position.x = x1;
	BodyDef.position.y = y1;
	BodyDef.type = b2_staticBody;
	ShapeDef.filter.categoryBits = FOOTHOLD_COLLISION_FLAG;
	ShapeDef.filter.maskBits = MOB_COLLISION_FLAG;
	ShapeDef.friction = 0.65f;

	B2BodyID = b2CreateBody(PhysicsSubsystem->B2WorldID, &BodyDef);
	b2CreateSegmentShape(B2BodyID, &ShapeDef, &Segment);
}

void UPhysicsComponent::InitializeAsDynamicRigidBody(float fWidth, float fHeight, int nCollisionFlag)
{
	FTransform OwnerTransform = Owner->GetTransform();
	b2WorldId B2WorldID = PhysicsSubsystem->B2WorldID;

	b2BodyDef BodyDef = b2DefaultBodyDef();

	BodyDef.type = b2_dynamicBody;
	BodyDef.gravityScale = 1;
	BodyDef.linearDamping = 0.0f;
	BodyDef.position.x = OwnerTransform.Position.x * PIXEL_TO_METER_CONSTANT;
	BodyDef.position.y = OwnerTransform.Position.y * PIXEL_TO_METER_CONSTANT;

	this->B2BodyID = b2CreateBody(B2WorldID, &BodyDef);

	b2Polygon DynamicBox = b2MakeBox(fWidth * PIXEL_TO_METER_CONSTANT / 2.0f, fHeight * PIXEL_TO_METER_CONSTANT / 2.0f);
	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 1.0f;
	ShapeDef.friction = 0.65f;

	switch (nCollisionFlag)
	{
	case FOOTHOLD_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = FOOTHOLD_COLLISION_FLAG;
		ShapeDef.filter.maskBits = MOB_COLLISION_FLAG;
		break;

	case MOB_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = MOB_COLLISION_FLAG;
		ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG;
		break;
	default:
		break;
	}

	b2CreatePolygonShape(B2BodyID, &ShapeDef, &DynamicBox);
}

void UPhysicsComponent::InitializeAsStatic(float fWidth, float fHeight, int nCollisionFlag)
{
	FTransform OwnerTransform = Owner->GetTransform();
	b2WorldId B2WorldID = PhysicsSubsystem->B2WorldID;

	b2BodyDef BodyDef = b2DefaultBodyDef();

	BodyDef.type = b2_staticBody;
	BodyDef.position.x = OwnerTransform.Position.x * PIXEL_TO_METER_CONSTANT;
	BodyDef.position.y = OwnerTransform.Position.y * PIXEL_TO_METER_CONSTANT;

	this->B2BodyID = b2CreateBody(B2WorldID, &BodyDef);

	b2Polygon Box = b2MakeBox(fWidth * PIXEL_TO_METER_CONSTANT / 2.0f, fHeight * PIXEL_TO_METER_CONSTANT / 2.0f);
	b2ShapeDef ShapeDef = b2DefaultShapeDef();

	switch (nCollisionFlag)
	{
	case FOOTHOLD_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = FOOTHOLD_COLLISION_FLAG;
		ShapeDef.filter.maskBits = MOB_COLLISION_FLAG;
		break;

	case MOB_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = MOB_COLLISION_FLAG;
		ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG;
		break;
	default:
		break;
	}

	b2CreatePolygonShape(B2BodyID, &ShapeDef, &Box);
}

void UPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();
}

b2BodyId UPhysicsComponent::GetBodyID() const
{
	return B2BodyID;
}

void UPhysicsComponent::InitializeAsMobFoot(float fWidth, float fYOffsetFromCenter, int nCollisionFlag)
{
	FTransform OwnerTransform = Owner->GetTransform();
	b2WorldId B2WorldID = PhysicsSubsystem->B2WorldID;

	b2BodyDef BodyDef = b2DefaultBodyDef();

	BodyDef.type = b2_dynamicBody;
	BodyDef.fixedRotation = true;
	BodyDef.gravityScale = 1;
	BodyDef.linearDamping = 0.0f;
	BodyDef.position.x = OwnerTransform.Position.x * PIXEL_TO_METER_CONSTANT;
	BodyDef.position.y = OwnerTransform.Position.y * PIXEL_TO_METER_CONSTANT;

	this->B2BodyID = b2CreateBody(B2WorldID, &BodyDef);
	b2Circle Circle = { {0.0f, fYOffsetFromCenter * PIXEL_TO_METER_CONSTANT}, fWidth * PIXEL_TO_METER_CONSTANT };
	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 0.0001f;
	ShapeDef.friction = 0.65f;

	switch (nCollisionFlag)
	{
	case FOOTHOLD_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = FOOTHOLD_COLLISION_FLAG;
		ShapeDef.filter.maskBits = MOB_COLLISION_FLAG;
		break;

	case MOB_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = MOB_COLLISION_FLAG;
		ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG;
		break;
	default:
		break;
	}

	b2CreateCircleShape(B2BodyID, &ShapeDef, &Circle);
}

