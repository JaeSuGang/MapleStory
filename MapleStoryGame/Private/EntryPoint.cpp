#include "GamePch.h"
#include "Engine/Engine.h"

extern "C"
{
	__declspec(dllexport) int main()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		auto Engine = UEngine::GetShared();

		Engine->RunForever();
	}
}
