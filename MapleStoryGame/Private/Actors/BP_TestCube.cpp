#include "GamePch.h"
#include "Actors/BP_TestCube.h"
#include "RenderCore/RenderComponent.h"

BP_TestCube::BP_TestCube()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_TestCube::BeginPlay()
{
	Super::BeginPlay();
	string strMeshName = "Cube";
	string strTextureName = "None";
	Transform.Scale.x = 100.0f;
	Transform.Scale.y = 100.0f;
	Transform.Scale.z = 100.0f;
	RenderComponent->SetMeshIDByName(strMeshName);
	RenderComponent->SetTextureByName(strTextureName);
	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetBlendMode(0);
}

void BP_TestCube::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}
