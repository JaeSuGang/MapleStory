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


		/* 키가 눌릴 때 바로 */
		if (__KeyState != 0x0000 && VKStates[i] == 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContextID])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::KeyDown)
					KeyEvent.Function();
			}
		}

		/* 키를 누르고 있을 때 */
		if (VKStates[i] != 0x0000 && __KeyState != 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContextID])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::Triggered)
					KeyEvent.Function();
			}
		}

		/* 키를 뗐을 때 */
		if (VKStates[i] != 0x0000 && __KeyState == 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContextID])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::KeyUp)
					KeyEvent.Function();
			}
		}

		/* 키값 기록 */
		VKStates[i] = __KeyState;
	}
}

void UKeyInputSubsystem::LateInit()
{
	Super::LateInit();


}

bool UKeyInputSubsystem::GetKey(int VKeyCode, EKeyState _KeyState) const
{
	switch (_KeyState)
	{
	case UKeyInputSubsystem::EKeyState::None:
		break;

	case UKeyInputSubsystem::EKeyState::Triggered:
		return VKStates[VKeyCode];

	case UKeyInputSubsystem::EKeyState::KeyDown:
		break;

	case UKeyInputSubsystem::EKeyState::KeyUp:
		break;

	default:
		break;
	}
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
