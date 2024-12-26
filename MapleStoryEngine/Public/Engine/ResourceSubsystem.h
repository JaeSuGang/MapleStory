#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Vector3.h"

struct FMesh
{
public:
	vector<FVector3> Vertices;
	vector<int> Indexes;
};

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* 생성자와 오버라이드 */
	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	unordered_map<string, FMesh>& GetMeshes();

private:
	unordered_map<string, FMesh> Meshes;
};

