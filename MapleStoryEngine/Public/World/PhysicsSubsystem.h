#pragma once
#include "World/WorldSubsystem.h"

class UPhysicsSubsystem : public UWorldSubsystem
{
public:
	/* �����ڿ� �������̵� */
	~UPhysicsSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

private:
	b2WorldId B2WorldID;
};

