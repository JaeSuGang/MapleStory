#pragma once
#include <Windows.h>
#include <memory>
#include "UObject/Object.h"

using std::shared_ptr;

class UEngine : public UObject
{
private:
	UEngine() = default;

public:
	~UEngine();
	shared_ptr<UEngine> GetInstance();

	void Tick();

private:
	static UEngine* Instance;

	LARGE_INTEGER StartCounter;
	LARGE_INTEGER LastCounter;
};

