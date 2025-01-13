#pragma once
#include "EnginePch.h"
#include "ActorComponent/ActorComponent.h"

struct FGameplayTag;

class AActor;
class UGameplayAction;

class UActionComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* 생성자와 오버라이드 */
	ENGINE_API void BeginPlay() override;

	ENGINE_API void TickComponent(float fDeltaTime) override;


public:
	ENGINE_API void StartActionByName(AActor* Instigator, string& Name);

	ENGINE_API void StartActionByTag(AActor* Instigator, FGameplayTag& ActionTag);

	template <typename T>
	T* AddAction()
	{
		T* pAction = new T{};

		shared_ptr<UGameplayAction> Action{ pAction };

		Actions.push_back(Action);

		return pAction;
	}

protected:
	vector<shared_ptr<UGameplayAction>> Actions;

};

