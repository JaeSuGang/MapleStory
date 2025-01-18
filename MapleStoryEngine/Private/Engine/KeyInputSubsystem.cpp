#include "EnginePch.h"
#include "Engine/KeyInputSubsystem.h"

UKeyInputSubsystem::UKeyInputSubsystem()
{
	CurrentInputMappingContext = EInputMappingContext::Game;
	VKStates.resize(VK_F12 + 1);
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
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContext])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::KeyDown)
					KeyEvent.Function();
			}
		}

		/* 키를 누르고 있을 때 */
		if (VKStates[i] != 0x0000 && __KeyState != 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContext])
			{
				if (KeyEvent.KeyCode == i && KeyEvent.KeyState == EKeyState::Triggered)
					KeyEvent.Function();
			}
		}

		/* 키를 뗐을 때 */
		if (VKStates[i] != 0x0000 && __KeyState == 0x0000)
		{
			for (FKeyEvent& KeyEvent : InputMappingContexts[CurrentInputMappingContext])
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

	return false;
}

void UKeyInputSubsystem::SetCurrentMappingContext(EInputMappingContext _Context)
{
	CurrentInputMappingContext = _Context;
}

void UKeyInputSubsystem::ClearKeys(EInputMappingContext _Context)
{
	InputMappingContexts[_Context].clear();
}

void UKeyInputSubsystem::BindKey(EInputMappingContext _Context, int VKeyCode, EKeyState _KeyState, std::function<void()> _Function)
{
	InputMappingContexts[CurrentInputMappingContext].emplace_back(VKeyCode, _KeyState, _Function);
}
