#pragma once
#include "World/WorldSubsystem.h"

class UPhysicsSubsystem : public UWorldSubsystem
{
public:
	/* 생성자와 오버라이드 */
	~UPhysicsSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

private:
	b2WorldId B2WorldID;
};

