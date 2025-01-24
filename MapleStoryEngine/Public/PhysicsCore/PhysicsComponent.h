#pragma once
#include "ActorComponent/ActorComponent.h"
#include "Math/Vector3.h"

/* 50px = 1m */
#define METER_TO_PIXEL_CONSTANT 50
#define PIXEL_TO_METER_CONSTANT 1 / 50

/* Collision Flag */
#define NO_COLLISION_FLAG 0x1
#define FOOTHOLD_COLLISION_FLAG 0x2
#define CHARACTER_FOOT_COLLISION_FLAG 0x4
#define MOB_FOOT_COLLISION_FLAG 0x8
#define MOB_HITBOX_COLLISION_FLAG 0x10
#define MOB_COLLIDER_COLLISION_FLAG 0x20
#define SKILL_COLLIDER_COLLISION_FLAG 0x40

class UPhysicsSubsystem;

class UPhysicsComponent : public UActorComponent
{
	typedef UActorComponent Super;

	friend class UPhysicsSubsystem;

public:
	ENGINE_API static UPhysicsComponent* GetPhysicsComponentByShapeId(b2ShapeId ShapeId);

public:
	/* 생성자와 오버라이드 */
	ENGINE_API UPhysicsComponent();

	ENGINE_API ~UPhysicsComponent();

	ENGINE_API void BeginPlay() override;

	ENGINE_API void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void FetchCircleOverlappedPhysicsComponents(float _fRadius, FVector3 _Pos, vector<UPhysicsComponent*>& _pVector);

	ENGINE_API void FetchOverlappedHitboxActors(vector<AActor*>& _pVector);

	ENGINE_API void FetchOverlappedHitboxes(vector<b2ShapeId>& pVector);

	ENGINE_API void SetPosition(FVector3 _Position);

	ENGINE_API void SetRotation(FVector3 _Rotation);

	ENGINE_API void AddZRotation(float _ZRotation);

	ENGINE_API bool GetIsGrounded();

	ENGINE_API void AddYPosition(float _y);

	ENGINE_API void AddXVelocity(float _x);

	ENGINE_API void AddYVelocity(float _y);

	ENGINE_API FVector3 GetVelocity() const;

	ENGINE_API void SetVelocity(FVector3 _Velocity);

	ENGINE_API void SetXVelocity(float _x);

	ENGINE_API void AddForwardVelocity(float _Speed);

	ENGINE_API void SetForwardVelocity(float _Speed);

	ENGINE_API b2BodyId GetBodyID() const;

	ENGINE_API void InitializeBody(b2BodyType _type);

	ENGINE_API void InitializeBodyWithNoGravity(b2BodyType _type);

	ENGINE_API void InitializeSkillCollider(float fWidth, float fHeight);

	ENGINE_API void InitializeMobCollider(float fWidth, float fHeight);

	ENGINE_API void InitializeHitbox(float fWidth, float fHeight);

	ENGINE_API void InitializeCharacterFootCollider(float fYOffsetFromCenter);

	ENGINE_API void InitializeMobFootCollider(float fYOffsetFromCenter);

	ENGINE_API void InitializeNPCFootCollider();

	ENGINE_API void InitializeAsFoothold(float x1, float y1, float x2, float y2);

protected:
	void SyncPos();

	void SyncPosAndRot();

protected:
	UPhysicsSubsystem* PhysicsSubsystem;

	b2BodyId B2BodyID;

	b2ShapeId B2FootID;

	b2ShapeId B2ColliderID;

	b2ShapeId B2SearchRangeID;

	b2ShapeId B2HitboxID; /* IsSensor = true */

	vector<b2ContactData> TempContactDatas;

	vector<b2ShapeId> TempShapeIds;

	bool IsLine;

	bool IsBodyInitialized;
};

