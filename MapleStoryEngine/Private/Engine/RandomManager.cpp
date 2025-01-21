#include "EnginePch.h"
#include "Engine/RandomManager.h"

URandomManager::URandomManager()
{
	RandomDevice = std::make_shared<std::random_device>();

	Gen = std::make_shared<std::mt19937_64>(RandomDevice->operator()());
}

void URandomManager::Tick(float fDeltaTime)
{
}

void URandomManager::LateInit()
{

}

float URandomManager::GenerateRandomFloatValue(float RangeA, float RangeB)
{
	std::uniform_real_distribution<float> Distribution{RangeA, RangeB};

	return Distribution(*Gen.get());
}
