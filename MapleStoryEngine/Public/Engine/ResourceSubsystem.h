#pragma once
#include "EnginePch.h"
#include "EngineSubsystem.h"
#include "Math/Mesh.h"

class UResourceSubsystem : public UEngineSubsystem
{
public:
	/* 생성자와 오버라이드 */
	UResourceSubsystem();

	void Tick(float fDeltaTime) override;

	void LateInit() override;

public:
	void AddNewMesh(string strKey, FMesh NewMesh);

	FMesh& GetMeshByID(int ID);

	int GetMeshIDByName(string strKey);

private:
	void SetWorkingDirectory();

	void LoadFolder(string strDirectoryName);

	void LoadTextureFile(string strPath);

	void SetMissingTexture();

	void GenerateDefaultMeshes();

	void GeneratePlaneMesh();

	void GenerateCubeMesh();


private:
	/* 그래픽 리소스 */
	unordered_map<string, int> StringMappedMeshIDs;
	vector<FMesh> Meshes;
};

