#pragma once
#include "EnginePch.h"
#include "ActorComponent/ActorComponent.h"
#include "Engine/Engine.h"
#include "GameInstance/GameInstance.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actions/GameplayAction.h"

struct FGameplayTag;

class AActor;
class UGameplayAction;

class UActionComponent : public UActorComponent
{
	typedef UActorComponent Super;

public:
	/* �����ڿ� �������̵� */
	ENGINE_API void BeginPlay() override;

	ENGINE_API void TickComponent(float fDeltaTime) override;


public:
	ENGINE_API void StartActionByNameWithParameter(AActor* Instigator, string Name, void* pParameter);

	ENGINE_API void StartActionByName(AActor* Instigator, string Name);

	ENGINE_API void StartActionByTag(AActor* Instigator, FGameplayTag& ActionTag, void* pParameter);

	ENGINE_API void StartActionByTag(AActor* Instigator, FGameplayTag& ActionTag);

	/* ���� nullptr �˻��� ��� */
	template <typename T>
	T* GetAction()
	{
		static_assert(std::is_base_of<UGameplayAction, T>::value);

		UGameplayAction* Action = static_cast<UGameplayAction*>(new T{});

		for (shared_ptr<UGameplayAction>& LoopAction : Actions)
		{
			if (LoopAction->Tag.ID == Action->Tag.ID)
			{
				delete Action;
				return LoopAction.get();
			}
		}

		delete Action;
		return nullptr;
	}

	template <typename T>
	T* AddAction()
	{
		T* pAction = new T{};

		pAction->ActionComponent = this;

		shared_ptr<UGameplayAction> Action{ pAction };

		Actions.push_back(Action);

		return pAction;
	}

protected:
	vector<shared_ptr<UGameplayAction>> Actions;
};

