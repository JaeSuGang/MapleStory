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
	void SetupUnrealStyleImGui();

	void MainDebugTab();

	void PlayerTab();
};

