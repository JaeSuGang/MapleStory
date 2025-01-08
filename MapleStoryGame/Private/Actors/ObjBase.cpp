#include "GamePch.h"
#include "Actors/ObjBase.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"

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

	if (ObjType == EObjType::Back)
	{
		FCamera& Camera = GEngine->RenderSubsystem->GetCamera();

		Transform.Position.x = this->OriginalX + Camera.Transform.Position.x * (100.0f + this->cx) / 100.0f;
		Transform.Position.y = this->OriginalY + Camera.Transform.Position.y * (100.0f + this->cy) / 100.0f;
	}
}

void AObjBase::SetObjType(EObjType _ObjType)
{
	this->ObjType = _ObjType;
}
