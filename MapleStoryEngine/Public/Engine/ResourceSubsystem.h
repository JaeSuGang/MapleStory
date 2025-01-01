#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Mesh.h"

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* �����ڿ� �������̵� */
	UResourceSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:

	FMesh& GetMesh(string strKey);

private:
	void SetWorkingDirectory();

	void GenerateDefaultMeshes();

	void GeneratePlaneMesh();

	void GenerateCubeMesh();

public:
	unordered_map<string, FMesh>& GetMeshes();

private:

private:
	/* �׷��� ���ҽ� */
	unordered_map<string, FMesh> Meshes;
};

