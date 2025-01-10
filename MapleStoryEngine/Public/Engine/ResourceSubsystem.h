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
	ENGINE_API void LoadFolder(string strDirectoryName);

	ENGINE_API void LoadFolderRecursively(string strDirectoryName);

	ENGINE_API int LoadTextureFile(string strPath);

	void AddNewMesh(string strKey, FMesh NewMesh);

	FMesh& GetMeshByID(int ID);

	int GetMeshIDByName(string strKey);

private:
	void SetWorkingDirectory();

	void SetMissingTexture();

	void GenerateDefaultMeshes();

	void GeneratePlaneMesh();

	void GenerateCubeMesh();

	void GenerateLineMesh();


private:
	/* �׷��� ���ҽ� */
	unordered_map<string, int> StringMappedMeshIDs;
	vector<FMesh> Meshes;
};

