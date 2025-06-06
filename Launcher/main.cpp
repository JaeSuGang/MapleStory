#include <Windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	INT_PTR(*lpfnDllEntry)();

	HMODULE hModule = LoadLibraryA("MapleStoryGame.dll");

	if (!hModule)
	{
		MessageBoxA(0, "MapleStoryGame.dll을 불러오지 못했습니다.", "DLL 로드 에러", MB_OK);
	}

	lpfnDllEntry = GetProcAddress(hModule, "main");

	if (!lpfnDllEntry)
	{
		MessageBoxA(0, "잘못된 Dll입니다.", "DLL 로드 에러", MB_OK);
	}
		
	lpfnDllEntry();
}
