#include "GamePch.h"
#include "Engine/Engine.h"
#include "MainGameInstance/MainGameInstance.h"

extern "C"
{
	__declspec(dllexport) int main()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		auto Engine = UEngine::Instantiate();

		Engine->SetGameInstance<UMainGameInstance>();

		Engine->RunForever();
	}
}
