#include <Windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	INT_PTR(*EntryFunctionPtr)();

	HMODULE hModule = LoadLibraryA("MapleStoryGame.dll");

	if (!hModule)
	{
		MessageBoxA(0, "MapleStoryGame.dll�� �ҷ����� ���߽��ϴ�.", "DLL �ε� ����", MB_OK);
	}

	EntryFunctionPtr = GetProcAddress(hModule, "main");

	if (!EntryFunctionPtr)
	{
		MessageBoxA(0, "�߸��� Dll�Դϴ�.", "DLL �ε� ����", MB_OK);
	}
		
	EntryFunctionPtr();
}
