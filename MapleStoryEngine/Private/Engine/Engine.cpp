#include "pch.h"
#include "Engine/Engine.h"

UEngine::~UEngine()
{
	Instance = nullptr;
}

shared_ptr<UEngine> UEngine::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new UEngine{};
		shared_ptr<UEngine> Engine{ Instance };
	}
	else
	{
		shared_ptr<UEngine> Engine = shared_from_this();
	}

	return ;
}

void UEngine::Tick()
{

}

UEngine* UEngine::Instance = nullptr;
