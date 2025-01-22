#include "GamePch.h"
#include "Actors/ObjBase.h"
#include "World/World.h"
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

	RenderComponent->SetBlendMode(0);
}

void AObjBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	switch (ObjType)
	{
	case EObjType::Back:
	{
		FCamera& Camera = GEngine->RenderSubsystem->GetCamera();

		Transform.Position.x = this->OriginalX + Camera.Transform.Position.x * (100.0f + this->rx) / 100.0f;
		Transform.Position.y = this->OriginalY + Camera.Transform.Position.y * (100.0f + this->ry) / 100.0f;
		break;
	}

	case EObjType::BackScrollHorizontal:
	{
		FCamera& Camera = GEngine->RenderSubsystem->GetCamera();
		Transform.Position.x += fDeltaTime * 50.0f;
		if (Transform.Position.x > Camera.Width * 4.0f)
			Transform.Position.x -= (int)(Camera.Width * 8.0f / cx) * cx;
		Transform.Position.y = this->OriginalY + Camera.Transform.Position.y * (100.0f + this->ry) / 100.0f;
		break;
	}

	default:
		break;
	}

}

void AObjBase::SetObjType(EObjType _ObjType)
{
	this->ObjType = _ObjType;
}
