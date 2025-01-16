#include "EnginePch.h"
#include "ActorComponent/CameraComponent.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"
#include "Actor/Actor.h"

void UCameraComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCameraComponent::TickComponent(float fDeltaTime)
{
	Super::TickComponent(fDeltaTime);

	if (IsMainCamera)
	{
		FCamera& Camera = GEngine->RenderSubsystem->GetCamera();

		FVector3 ActorPos = Owner->GetTransform().Position;
		FVector3 CameraPos = Camera.Transform.Position;

		float fLerpRatio = 2.5f * fDeltaTime;

		Camera.Transform.Position.x = ActorPos.x * fLerpRatio + CameraPos.x * (1 - fLerpRatio);
		Camera.Transform.Position.y = (ActorPos.y + 130.0f) * fLerpRatio + CameraPos.y * (1 - fLerpRatio);
	}
}

void UCameraComponent::SetMainCamera(bool _Value)
{
	IsMainCamera = _Value;
}