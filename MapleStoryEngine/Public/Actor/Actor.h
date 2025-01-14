#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"
#include "Engine/DebugSubsystem.h"
#include "Math/Transform.h"
#include "GameplayTags/GameplayTagContainer.h"

class UActorComponent;

class AActor : public UObject
{
public:
	/* 생성자와 오버라이드 */
	ENGINE_API AActor();

	ENGINE_API virtual void BeginPlay() = 0;

	ENGINE_API virtual void Tick(float fDeltaTime) = 0;

public:
	ENGINE_API bool HasTagExact(FGameplayTag& _Tag) const;

	ENGINE_API bool HasTagExact(string _Name) const;

	ENGINE_API bool GetIsTickEnabled() const;

	ENGINE_API void SetIsTickEnabled(bool bValue);

	ENGINE_API void SetPosition(FVector3 _Position);

	ENGINE_API void Destroy();

	ENGINE_API UWorld* GetWorld() const;

	ENGINE_API bool GetIsBeginPlayed() const;

	ENGINE_API void SetWorld(UWorld* pWorld);

	ENGINE_API void MultiplyScale(float x, float y, float z);

	ENGINE_API void SetRotation(FVector3 _Vector);

	ENGINE_API void SetScale(FVector3 _Vector);

	ENGINE_API FTransform& GetTransform();

	template <typename T>
	T* CreateDefaultSubobject()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		if (T* ExistedComponent = GetComponentByClass<T>())
		{
			return ExistedComponent;
		}

		shared_ptr<UActorComponent> NewComponent{ new T{} };
		NewComponent->SetOwner(this);
		OwnedComponents.insert(std::make_pair(typeid(T).name(), NewComponent));
		return static_cast<T*>(NewComponent.get());
	}

	template <typename T>
	T* GetComponentByClass()
	{
		static_assert(std::is_base_of<UActorComponent, T>::value);

		auto FindIter = OwnedComponents.find(typeid(T).name());

		if (FindIter == OwnedComponents.end())
			return nullptr;

		return static_cast<T*>(FindIter->second.get());
	}

protected:
	UWorld* World;

	unordered_map<string, shared_ptr<UActorComponent>> OwnedComponents;

	FGameplayTagContainer TagContainer;

	FTransform Transform;

	bool IsBeginPlayed;

	bool IsTickEnabled;
};

