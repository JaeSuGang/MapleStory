#pragma once
#include "ActorComponent/ActorComponent.h"

class UPhysicsSubsystem;

class UPhysicsComponent : public UActorComponent
{
	typedef UActorComponent Super;

	friend class UPhysicsSubsystem;

public:
	/* �����ڿ� �������̵� */
	ENGINE_API UPhysicsComponent();
	ENGINE_API ~UPhysicsComponent();

	ENGINE_API void BeginPlay() override;

	ENGINE_API void TickComponent(float fDeltaTime) override;

public:
	ENGINE_API void InitializeAsDynamicRigidBody(float fWidth, float fHeight);

	ENGINE_API void InitializeAsStatic(float fWidth, float fHeight);


private:
	UPhysicsSubsystem* PhysicsSubsystem;
		
	b2BodyId B2BodyID;
};

