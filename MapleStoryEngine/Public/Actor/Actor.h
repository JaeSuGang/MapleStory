#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"
#include "Engine/DebugSubsystem.h"
#include "Math/Transform.h"

class UActorComponent;

class AActor : public UObject
{
public:
	ENGINE_API AActor();

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
	unordered_map<string, shared_ptr<UActorComponent>> OwnedComponents;

	FTransform Transform;
};

