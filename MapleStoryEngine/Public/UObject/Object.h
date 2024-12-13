#pragma once
#include "EngineAPI.h"
#include <memory>

class UObject : std::enable_shared_from_this<UObject>
{
public:
	UObject() = default;
	virtual ~UObject() = default;

	UObject(const UObject& Other) = delete;
	UObject(UObject&& Other) noexcept = delete;
	UObject& operator=(const UObject& Other) = delete;
	UObject& operator=(UObject&& Other) noexcept = delete;
};

