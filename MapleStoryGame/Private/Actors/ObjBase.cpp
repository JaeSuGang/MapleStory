#include "GamePch.h"
#include "Actors/ObjBase.h"
#include "RenderCore/RenderComponent.h"

AObjBase::AObjBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void AObjBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	RenderComponent->SetBlendMode(0);
}

void AObjBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);
}

void AObjBase::SetObjType(EObjType _ObjType)
{
	this->ObjType = _ObjType;
}
