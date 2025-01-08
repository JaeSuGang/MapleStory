#pragma once
#include <memory>

using std::shared_ptr;
using std::weak_ptr;

class UObject : std::enable_shared_from_this<UObject>
{
public:
	UObject() = default;
	virtual ~UObject() = default;

	template <typename T>
	shared_ptr<T> GetShared()
	{
		return std::static_pointer_cast<T>(shared_from_this());
	}

	template <typename T>
	weak_ptr<T> GetWeak()
	{
		return weak_ptr<T>(GetShared<T>());
	}

	UObject(const UObject& Other) = delete;
	UObject(UObject&& Other) noexcept = delete;
	UObject& operator=(const UObject& Other) = delete;
	UObject& operator=(UObject&& Other) noexcept = delete;
};

