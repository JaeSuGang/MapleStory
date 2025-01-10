#pragma once
#include "Actor/Actor.h"
#include "Components/FSMComponent.h"

class URenderComponent;
class UPhysicsComponent;

class ACharacterBase : public AActor
{
	typedef AActor Super;

public:
	/* FSM ���� ���� */
	class UIdleState : public UBaseState
	{
		void OnStateEnter() override;
		void OnStateUpdate(float fDeltaTime) override;
		void OnStateExit() override;
	};

	class UMoveState : public UBaseState
	{
		void OnStateEnter() override;
		void OnStateUpdate(float fDeltaTime) override;
		void OnStateExit() override;
	};

public:
	/* �����ڿ� �������̵� */
	ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:

protected:
	UFSMComponent* FSMComponent;

	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;
};

