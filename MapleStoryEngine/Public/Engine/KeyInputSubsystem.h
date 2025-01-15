#pragma once
#include "EnginePch.h"
#include "Engine/EngineSubsystem.h"

class UKeyInputSubsystem : public UEngineSubsystem
{
	typedef UEngineSubsystem Super;

public:
	enum class EKeyState
	{
		None,
		Triggered,
		KeyDown,
		KeyUp
	};

	struct FKeyEvent
	{
		int KeyCode;
		EKeyState KeyState;
		std::function<void()> Function;
	};

public:
	/* 생성자와 오버라이드 */
	UKeyInputSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	ENGINE_API bool GetKey(int VKeyCode, EKeyState _KeyState) const;

	ENGINE_API void SetCurrentInputMappingContextID(int nID);

	ENGINE_API void ClearKeys();

	ENGINE_API void BindKey(int VKeyCode, EKeyState _KeyState, std::function<void()> _Function);

protected:
	vector<vector<FKeyEvent>> InputMappingContexts;

	vector<unsigned short> VKStates;

	int CurrentInputMappingContextID;
};

