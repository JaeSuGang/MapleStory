#pragma once
#include "Actor/Actor.h"
#include "Components/FSMComponent.h"

class URenderComponent;
class UPhysicsComponent;

class ACharacterBase : public AActor
{
	typedef AActor Super;

public:
	/* FSM 상태 선언 */
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
	/* 생성자와 오버라이드 */
	ACharacterBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:

protected:
	UFSMComponent* FSMComponent;

	URenderComponent* RenderComponent;

	UPhysicsComponent* PhysicsComponent;
};

