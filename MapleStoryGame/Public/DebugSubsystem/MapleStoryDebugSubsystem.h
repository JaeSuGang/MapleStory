#pragma once
#include "Engine/DebugSubsystem.h"

class UMapleStoryDebugSubsystem : public UDebugSubsystem
{
public:
	/* �����ڿ� �������̵� */
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

