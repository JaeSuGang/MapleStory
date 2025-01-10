#include "GamePch.h"
#include "Actors/FootholdBase.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"

AFootholdBase::AFootholdBase()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	RenderComponent->EnableMaterial();
	RenderComponent->SetSortingLayer(100);
}

void AFootholdBase::BeginPlay()
{
	Super::BeginPlay();

	RenderComponent->SetPixelShaderByName(GREEN_PIXEL_SHADER_NAME);
	RenderComponent->SetMeshIDByName("Line");
	RenderComponent->SetBlendMode(0);
}

void AFootholdBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	
}

void AFootholdBase::InitializeValues(float x1, float y1, float x2, float y2)
{
	PhysicsComponent->InitializeAsFoothold((float)x1, (float)y1, (float)x2, (float)y2);

	BodyID = PhysicsComponent->GetBodyID();


	Transform.Scale.x = std::pow(std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2), 0.5f);
	Transform.Scale.y = 1.0f;
	Transform.Scale.z = 1.0f;

	Transform.Rotation.z = DirectX::XMConvertToDegrees(std::atan2((y2 - y1), (x2 - x1)));
}
