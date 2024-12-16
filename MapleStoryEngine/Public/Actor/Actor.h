#pragma once
#include "EnginePch.h"
#include "UObject/Object.h"

class UActorComponent;

class AActor : public UObject
{
public:
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
};

