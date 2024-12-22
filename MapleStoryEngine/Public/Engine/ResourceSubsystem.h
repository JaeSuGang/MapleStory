#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"

struct FMesh
{

};

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* 생성자와 오버라이드 */
	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

private:
	unordered_map<string, FMesh> Meshes;
};

