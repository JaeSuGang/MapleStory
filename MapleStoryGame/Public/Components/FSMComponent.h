#pragma once
#include "GamePch.h"
#include "ActorComponent/ActorComponent.h"

class UFSMComponent;

class UBaseState abstract
{
public:
	/* 생성자와 오버라이드 */
	virtual void OnStateEnter() = 0;

	virtual void OnStateUpdate(float fDeltaTime) = 0;

	virtual void OnStateExit() = 0;

public:
	void SetOwner(AActor* OwnerToSet);

	void SetFSM(UFSMComponent* FSMToSet);

protected:
	AActor* Owner;
	UFSMComponent* FSM;

};

class UFSMComponent : public UActorComponent
{
public:
	/* 생성자와 오버라이드 */
	void BeginPlay() override;

	void TickComponent(float fDeltaTime) override;

public:
	template<typename T>
	T* ChangeState()
	{
		auto FindIter = States.find(typeid(T).name());

		if (FindIter == States.end())
			return nullptr;

		T* NewState = FindIter->second.get();
		CurrentState = NewState;
		return NewState;
	}

	template<typename T>
	T* CreateState()
	{
		UBaseState* pState = new T{};
		shared_ptr<UBaseState> sharedState{ pState };
		States.insert(std::make_pair(typeid(T).name(), sharedState));
		return pState;
	}

protected:
	UBaseState* CurrentState;

	unordered_map<string, shared_ptr<UBaseState>> States;
};

