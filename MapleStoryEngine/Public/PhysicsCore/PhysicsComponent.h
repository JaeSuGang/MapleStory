#pragma once
#include "ActorComponent/ActorComponent.h"
#include "Math/Vector3.h"

/* 50px = 1m */
#define METER_TO_PIXEL_CONSTANT 50
#define PIXEL_TO_METER_CONSTANT 1 / 50

/* Collision Flag */
#define NO_COLLISION_FLAG 0x1
#define FOOTHOLD_COLLISION_FLAG 0x2
#define MOB_FOOT_COLLISION_FLAG 0x4
#define MOB_HITBOX_COLLISION_FLAG 0x8

class UPhysicsSubsystem;

class UPhysicsComponent : public UActorComponent
{
	typedef UActorComponent Super;

	friend class UPhysicsSubsystem;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API UPhysicsComponent();
	ENGINE_API ~UPhysicsComponent();

	ENGINE_API void BeginPlay() override;

	ENGINE_API void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API bool GetIsGrounded();

	ENGINE_API void AddYPosition(float _y);

	ENGINE_API void AddXVelocity(float _x);

	ENGINE_API void AddYVelocity(float _y);

	ENGINE_API FVector3 GetVelocity() const;

	ENGINE_API void SetXVelocity(float _x);

	ENGINE_API b2BodyId GetBodyID() const;

	ENGINE_API void InitializeBody(b2BodyType _type);

	ENGINE_API void InitializeBodyWithNoGravity(b2BodyType _type);

	ENGINE_API void InitializeHitbox(float fWidth, float fHeight);

	ENGINE_API void InitializeFootCollider(float fYOffsetFromCenter);

	ENGINE_API void InitializeNPCFootCollider();

	ENGINE_API void InitializeAsFoothold(float x1, float y1, float x2, float y2);

protected:
	void SyncPos();

	void SyncPosAndRot();

protected:
	UPhysicsSubsystem* PhysicsSubsystem;
		
	b2BodyId B2BodyID;

	b2ShapeId B2FootID;

	b2ShapeId B2HitboxID;

	bool IsLine;

	bool IsBodyInitialized;
};

