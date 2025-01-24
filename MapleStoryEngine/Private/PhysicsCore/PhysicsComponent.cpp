#include "EnginePch.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actor/Actor.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "Engine/TimeSubsystem.h"
#include "Math/Math.h"

UPhysicsComponent* UPhysicsComponent::GetPhysicsComponentByShapeId(b2ShapeId ShapeId)
{
	return reinterpret_cast<UPhysicsComponent*>(b2Body_GetUserData(b2Shape_GetBody(ShapeId)));
}

UPhysicsComponent::UPhysicsComponent()
	:
	B2ColliderID{},
	B2HitboxID{},
	B2FootID{},
	B2BodyID{}
{
	IsBodyInitialized = false;

	IsLine = false;

	PhysicsSubsystem = GEngine->GetWorld()->PhysicsSubsystem;
}

UPhysicsComponent::~UPhysicsComponent()
{
	if (B2BodyID.index1)
		b2DestroyBody(B2BodyID);
}

void UPhysicsComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);

	if (!IsBodyInitialized)
		return;

	if (IsLine)
		SyncPos();
	else
		SyncPosAndRot();
}

void UPhysicsComponent::FetchCircleOverlappedPhysicsComponents(float _fRadius, FVector3 _Pos, vector<UPhysicsComponent*>& _pVector)
{
	b2QueryFilter _B2QueryFilter{};
	_B2QueryFilter.categoryBits = -1;
	_B2QueryFilter.maskBits = -1;

	GEngine->GetWorld()->PhysicsSubsystem->FetchCircleOverlap(_fRadius, _Pos, _B2QueryFilter, _pVector);
}

void UPhysicsComponent::FetchOverlappedHitboxActors(vector<AActor*>& _pVector)
{
	_pVector.clear();

	this->FetchOverlappedHitboxes(TempShapeIds);

	for (b2ShapeId& _ShapeId : TempShapeIds)
	{
		if (_ShapeId.index1 == 0)
			continue;

		UPhysicsComponent* _PhysicsComponent = reinterpret_cast<UPhysicsComponent*>(b2Body_GetUserData(b2Shape_GetBody(_ShapeId)));
		_pVector.push_back(_PhysicsComponent->Owner);
	}
}

void UPhysicsComponent::FetchOverlappedHitboxes(vector<b2ShapeId>& pVector)
{
	b2QueryFilter _Filter{};
	_Filter.categoryBits = SKILL_COLLIDER_COLLISION_FLAG;
	_Filter.maskBits = MOB_HITBOX_COLLISION_FLAG;

	GEngine->GetWorld()->PhysicsSubsystem->FetchPlaneActorOverlap(Owner, _Filter, &pVector);
}

void UPhysicsComponent::SetRotation(FVector3 _Rotation)
{
	b2Transform Transform = b2Body_GetTransform(B2BodyID);

	Transform.q.c = std::cosf(DegreeToRadian(_Rotation.z));
	Transform.q.s = std::sinf(DegreeToRadian(_Rotation.z));

	b2Body_SetTransform(B2BodyID, Transform.p, Transform.q);
}

void UPhysicsComponent::AddZRotation(float _ZRotation)
{
 	b2Transform _Transform = b2Body_GetTransform(B2BodyID);

	float _OriginalRotation = RadianToDegree(std::atan2f(_Transform.q.s, _Transform.q.c));

	_Transform.q.c = std::cosf(DegreeToRadian(_OriginalRotation + _ZRotation));
	_Transform.q.s = std::sinf(DegreeToRadian(_OriginalRotation + _ZRotation));

	b2Body_SetTransform(B2BodyID, _Transform.p, _Transform.q);
}

void UPhysicsComponent::SetPosition(FVector3 _Position)
{
	b2Transform Transform = b2Body_GetTransform(B2BodyID);

	Transform.p.x = _Position.x * PIXEL_TO_METER_CONSTANT;
	Transform.p.y = _Position.y * PIXEL_TO_METER_CONSTANT;

	b2Body_SetTransform(B2BodyID, Transform.p, Transform.q);
}

bool UPhysicsComponent::GetIsGrounded()
{
	int ContactDataCount = b2Shape_GetContactCapacity(B2FootID);
	if (ContactDataCount == 0)
		return false;

	TempContactDatas.resize(ContactDataCount);
	b2Shape_GetContactData(B2FootID, &TempContactDatas[0], ContactDataCount);

	for (const b2ContactData& Data : TempContactDatas)
	{
		if (Data.shapeIdA.index1 == 0)
			continue;

		b2Filter Filter = b2Shape_GetFilter(Data.shapeIdA);
		if (Filter.categoryBits == FOOTHOLD_COLLISION_FLAG)
			return true;
	}

	return false;
}

void UPhysicsComponent::AddYPosition(float _y)
{
	b2Vec2 pos = b2Body_GetPosition(B2BodyID);
	pos.y += _y * PIXEL_TO_METER_CONSTANT;

	b2Rot rot = b2Body_GetRotation(B2BodyID);

	b2Body_SetTransform(B2BodyID, pos, rot);
}

void UPhysicsComponent::AddXVelocity(float _x)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	Velocity.x += _x * PIXEL_TO_METER_CONSTANT;

	b2Body_SetLinearVelocity(B2BodyID, Velocity);
}

void UPhysicsComponent::AddYVelocity(float _y)
{
	float fDeltaTime = GEngine->TimeSubsystem->GetDeltaTime();

	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	Velocity.y += _y * PIXEL_TO_METER_CONSTANT;

	b2Body_SetLinearVelocity(B2BodyID, Velocity);
}

FVector3 UPhysicsComponent::GetVelocity() const
{
	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	return { Velocity.x * METER_TO_PIXEL_CONSTANT, Velocity.y * METER_TO_PIXEL_CONSTANT, 0.0f };
}

void UPhysicsComponent::SetVelocity(FVector3 _Velocity)
{
	b2Vec2 VelocityToApply = b2Body_GetLinearVelocity(B2BodyID);

	VelocityToApply.x = _Velocity.x * PIXEL_TO_METER_CONSTANT;
	VelocityToApply.y = _Velocity.y * PIXEL_TO_METER_CONSTANT;

	b2Body_SetLinearVelocity(B2BodyID, VelocityToApply);
}

void UPhysicsComponent::SetXVelocity(float _x)
{
	b2Vec2 Velocity = b2Body_GetLinearVelocity(B2BodyID);

	Velocity.x = _x * PIXEL_TO_METER_CONSTANT;

	b2Body_SetLinearVelocity(B2BodyID, Velocity);
}

void UPhysicsComponent::AddForwardVelocity(float _Speed)
{
	_Speed = _Speed * PIXEL_TO_METER_CONSTANT;

	b2Vec2 _Velocity = b2Body_GetLinearVelocity(B2BodyID);
	b2Transform _Transform = b2Body_GetTransform(B2BodyID);

	_Velocity.x += _Transform.q.c * _Speed;
	_Velocity.y += _Transform.q.s * _Speed;

	b2Body_SetLinearVelocity(B2BodyID, _Velocity);
}

void UPhysicsComponent::SetForwardVelocity(float _Speed)
{
	_Speed = _Speed * PIXEL_TO_METER_CONSTANT;

	b2Vec2 _Velocity = b2Body_GetLinearVelocity(B2BodyID);
	b2Transform _Transform = b2Body_GetTransform(B2BodyID);

	_Velocity.x = _Transform.q.c * _Speed;
	_Velocity.y = _Transform.q.s * _Speed;

	b2Body_SetLinearVelocity(B2BodyID, _Velocity);
}

void UPhysicsComponent::InitializeAsFoothold(float x1, float y1, float x2, float y2)
{
	IsLine = true;
	IsBodyInitialized = true;

	x1 = x1 * PIXEL_TO_METER_CONSTANT;
	x2 = x2 * PIXEL_TO_METER_CONSTANT;
	y1 = y1 * PIXEL_TO_METER_CONSTANT;
	y2 = y2 * PIXEL_TO_METER_CONSTANT;


	b2BodyDef BodyDef = b2DefaultBodyDef();
	BodyDef.position.x = x1;
	BodyDef.position.y = y1;
	BodyDef.type = b2_staticBody;

	b2ShapeDef ShapeDef = b2DefaultShapeDef();

	b2ChainDef ChainDef = b2DefaultChainDef();

	b2Vec2 VecPoints[4] = { {x2 - x1, y2 - y1}, {x2 - x1, y2 - y1}, {0.0f, 0.0f}, {0.0f, 0.0f} };

	ChainDef.points = VecPoints;
	ChainDef.count = 4;
	ChainDef.filter.categoryBits = FOOTHOLD_COLLISION_FLAG;
	ChainDef.filter.maskBits = MOB_FOOT_COLLISION_FLAG | CHARACTER_FOOT_COLLISION_FLAG;

	ShapeDef.friction = 0.7f;

	B2BodyID = b2CreateBody(PhysicsSubsystem->B2WorldID, &BodyDef);

	b2CreateChain(B2BodyID, &ChainDef);
}

void UPhysicsComponent::SyncPos()
{
	FTransform& OwnerTransfrom = Owner->GetTransform();
	b2Transform b2Trans = b2Body_GetTransform(B2BodyID);

	FVector3 Pos{ b2Trans.p.x * METER_TO_PIXEL_CONSTANT, b2Trans.p.y * METER_TO_PIXEL_CONSTANT, OwnerTransfrom.Position.z };

	OwnerTransfrom.Position = Pos;
}

void UPhysicsComponent::SyncPosAndRot()
{
	FTransform& OwnerTransfrom = Owner->GetTransform();
	b2Transform b2Trans = b2Body_GetTransform(B2BodyID);

	FVector3 Pos{ b2Trans.p.x * METER_TO_PIXEL_CONSTANT, b2Trans.p.y * METER_TO_PIXEL_CONSTANT, OwnerTransfrom.Position.z };
	FVector3 Rot{ OwnerTransfrom.Rotation.x, OwnerTransfrom.Rotation.y, RadianToDegree(std::atan2(b2Trans.q.s, b2Trans.q.c)) };

	OwnerTransfrom.Position = Pos;
	OwnerTransfrom.Rotation = Rot;
}

void UPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();
}

b2BodyId UPhysicsComponent::GetBodyID() const
{
	return B2BodyID;
}

void UPhysicsComponent::InitializeBodyWithNoGravity(b2BodyType _type)
{
	IsBodyInitialized = true;

	FTransform OwnerTransform = Owner->GetTransform();

	b2BodyDef BodyDef = b2DefaultBodyDef();
	BodyDef.type = _type;
	BodyDef.fixedRotation = true;
	BodyDef.gravityScale = 0.0f;
	BodyDef.linearDamping = 0.0f;
	BodyDef.position.x = OwnerTransform.Position.x * PIXEL_TO_METER_CONSTANT;
	BodyDef.position.y = OwnerTransform.Position.y * PIXEL_TO_METER_CONSTANT;
	BodyDef.userData = this;

	B2BodyID = b2CreateBody(PhysicsSubsystem->B2WorldID, &BodyDef);
}

void UPhysicsComponent::InitializeSkillCollider(float fWidth, float fHeight)
{
	b2Polygon Polygon = b2MakeBox(fWidth / 2.0f * PIXEL_TO_METER_CONSTANT, fHeight / 2.0f * PIXEL_TO_METER_CONSTANT);

	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 0.0f;
	ShapeDef.friction = 0.0f;
	ShapeDef.filter.categoryBits = SKILL_COLLIDER_COLLISION_FLAG;
	ShapeDef.filter.maskBits = MOB_HITBOX_COLLISION_FLAG;

	B2ColliderID = b2CreatePolygonShape(B2BodyID, &ShapeDef, &Polygon);
}

void UPhysicsComponent::InitializeBody(b2BodyType _type)
{
	IsBodyInitialized = true;

	FTransform OwnerTransform = Owner->GetTransform();

	b2BodyDef BodyDef = b2DefaultBodyDef();
	BodyDef.type = _type;
	BodyDef.fixedRotation = true;
	BodyDef.gravityScale = 1;
	BodyDef.linearDamping = 0.0f;
	BodyDef.position.x = OwnerTransform.Position.x * PIXEL_TO_METER_CONSTANT;
	BodyDef.position.y = OwnerTransform.Position.y * PIXEL_TO_METER_CONSTANT;
	BodyDef.userData = this;

	B2BodyID = b2CreateBody(PhysicsSubsystem->B2WorldID, &BodyDef);
}

void UPhysicsComponent::InitializeMobCollider(float fWidth, float fHeight)
{
	b2Polygon Polygon = b2MakeBox(fWidth / 2.0f * PIXEL_TO_METER_CONSTANT, fHeight / 2.0f * PIXEL_TO_METER_CONSTANT);

	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 10000.0f;
	ShapeDef.friction = 0.0f;
	ShapeDef.filter.categoryBits = MOB_COLLIDER_COLLISION_FLAG;
	ShapeDef.filter.maskBits = CHARACTER_FOOT_COLLISION_FLAG;

	B2HitboxID = b2CreatePolygonShape(B2BodyID, &ShapeDef, &Polygon);
}

void UPhysicsComponent::InitializeHitbox(float fWidth, float fHeight)
{
	b2Polygon Polygon = b2MakeBox(fWidth / 2.0f * PIXEL_TO_METER_CONSTANT, fHeight / 2.0f * PIXEL_TO_METER_CONSTANT);

	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.isSensor = true;
	ShapeDef.density = 0.0f;
	ShapeDef.friction = 0.0f;
	ShapeDef.filter.categoryBits = MOB_HITBOX_COLLISION_FLAG;
	ShapeDef.filter.maskBits = SKILL_COLLIDER_COLLISION_FLAG;

	B2HitboxID = b2CreatePolygonShape(B2BodyID, &ShapeDef, &Polygon);
}

void UPhysicsComponent::InitializeCharacterFootCollider(float fYOffsetFromCenter)
{
	b2Circle Circle = { {0.0f, fYOffsetFromCenter * PIXEL_TO_METER_CONSTANT}, 1.0f * PIXEL_TO_METER_CONSTANT };

	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 0.1f;
	ShapeDef.friction = 0.7f;
	ShapeDef.filter.categoryBits = CHARACTER_FOOT_COLLISION_FLAG;
	ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG | MOB_COLLIDER_COLLISION_FLAG;

	B2FootID = b2CreateCircleShape(B2BodyID, &ShapeDef, &Circle);
}

void UPhysicsComponent::InitializeMobFootCollider(float fYOffsetFromCenter)
{
	b2Circle Circle = { {0.0f, fYOffsetFromCenter * PIXEL_TO_METER_CONSTANT}, 1.0f * PIXEL_TO_METER_CONSTANT };

	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 0.1f;
	ShapeDef.friction = 0.7f;
	ShapeDef.filter.categoryBits = MOB_FOOT_COLLISION_FLAG;
	ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG;

	B2FootID = b2CreateCircleShape(B2BodyID, &ShapeDef, &Circle);
}

void UPhysicsComponent::InitializeNPCFootCollider()
{
	FTransform& Transform = Owner->GetTransform();

	b2Circle Circle = { {0.0f, -1.0f * Transform.Scale.y * 0.49f * PIXEL_TO_METER_CONSTANT}, 1.0f * PIXEL_TO_METER_CONSTANT };

	b2ShapeDef ShapeDef = b2DefaultShapeDef();
	ShapeDef.density = 0.1f;
	ShapeDef.friction = 0.7f;
	ShapeDef.filter.categoryBits = MOB_FOOT_COLLISION_FLAG;
	ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG;

	B2FootID = b2CreateCircleShape(B2BodyID, &ShapeDef, &Circle);
}

/* Obsolete Codes
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
	ShapeDef.friction = 0.7f;

	switch (nCollisionFlag)
	{
	case FOOTHOLD_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = FOOTHOLD_COLLISION_FLAG;
		ShapeDef.filter.maskBits = MOB_FOOT_COLLISION_FLAG;
		break;

	case MOB_FOOT_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = MOB_FOOT_COLLISION_FLAG;
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
		ShapeDef.filter.maskBits = MOB_FOOT_COLLISION_FLAG;
		break;

	case MOB_FOOT_COLLISION_FLAG:
		ShapeDef.filter.categoryBits = MOB_FOOT_COLLISION_FLAG;
		ShapeDef.filter.maskBits = FOOTHOLD_COLLISION_FLAG;
		break;
	default:
		break;
	}

	b2CreatePolygonShape(B2BodyID, &ShapeDef, &Box);
}
*/