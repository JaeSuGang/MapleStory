#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"

struct FMesh
{

};

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* �����ڿ� �������̵� */
	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

private:
	unordered_map<string, FMesh> Meshes;
};

