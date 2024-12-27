#pragma once
#include "EnginePch.h"
#include "Math/Vertex.h"

struct FMesh
{
public:
	vector<FVertex> Vertices;
	vector<unsigned int> Indexes;
	D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
};