#pragma once
#include "Engine/DebugSubsystem.h"

class UMapleStoryDebugSubsystem : public UDebugSubsystem
{
public:
	/* 생성자와 오버라이드 */
	UMapleStoryDebugSubsystem();

	void CustomCode() override;

	void CustomInit() override;

protected:
	void BindFreeCameraKeys();

	void MainDebugTab();

	void PlayerTab();

	void SetupUnrealStyleImGui();

protected:
	void ToggleFreeCamera();
};

