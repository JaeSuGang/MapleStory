#include "EnginePch.h"
#include "Engine/KeyInputSubsystem.h"

UKeyInputSubsystem::UKeyInputSubsystem()
{
	VKStates.resize(VK_F12 + 1);
	InputMappingContexts.resize(1);
}

void UKeyInputSubsystem::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	for (int i = 0; i <= VK_F12; i++)
	{
		unsigned short __KeyState = static_cast<unsigned short>(GetAsyncKeyState(i));


		/* Ű�� ������ ���� �� */
		if (__KeyState != 0x0000 && VKStates[i] == 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContextID])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::KeyDown)
					KeyEvent.Function();
			}
		}

		/* Ű�� ���� �� �ٷ� */
		if (VKStates[i] != 0x0000 && __KeyState != 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContextID])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::Triggered)
					KeyEvent.Function();
			}
		}

		/* Ű�� ���� �� */
		if (VKStates[i] != 0x0000 && __KeyState == 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContextID])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::KeyUp)
					KeyEvent.Function();
			}
		}

		/* Ű�� ��� */
		VKStates[i] = __KeyState;
	}
}

void UKeyInputSubsystem::LateInit()
{
	Super::LateInit();


}

void UKeyInputSubsystem::SetCurrentInputMappingContextID(int nID)
{
	CurrentInputMappingContextID = nID;

	if (nID >= InputMappingContexts.size())
		InputMappingContexts.resize(nID + 1);
}

void UKeyInputSubsystem::ClearKeys()
{
	InputMappingContexts[CurrentInputMappingContextID].clear();
}

void UKeyInputSubsystem::BindKey(int VKeyCode, EKeyState _KeyState, std::function<void()> _Function)
{
	InputMappingContexts[CurrentInputMappingContextID].emplace_back(VKeyCode, _KeyState, _Function);
}
