#pragma once
#include "World/WorldSubsystem.h"

class UPhysicsSubsystem : public UWorldSubsystem
{
	friend class UPhysicsComponent;

public:
	/* 생성자와 오버라이드 */
	~UPhysicsSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

private:
	b2WorldId B2WorldID;

	const float SimulationFrequencyTime = 1.0f / 60.0f;

	float AccumulatedDeltaTime;
};

