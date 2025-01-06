#pragma once
#include "ActorComponent/ActorComponent.h"

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
	ENGINE_API void InitializeAsDynamicRigidBody();

	ENGINE_API void InitializeAsStatic();


private:
	UPhysicsSubsystem* PhysicsSubsystem;
		
	b2BodyId B2BodyID;
};

