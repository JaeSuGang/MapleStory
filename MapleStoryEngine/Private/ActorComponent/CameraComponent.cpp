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
		FVector3 PosOffset = {0.0f, 130.0f, 0.0f};
		FVector3 DestPos = { ActorPos.x + PosOffset.x, ActorPos.y + PosOffset.y, 0.0f };

		if (std::abs(DestPos.x - CameraPos.x) > 1.0f || std::abs(DestPos.y - CameraPos.y) > 1.0f)
		{
			float fLerpRatio = 2.5f * fDeltaTime;

			Camera.Transform.Position.x = DestPos.x * fLerpRatio + CameraPos.x * (1 - fLerpRatio);
			Camera.Transform.Position.y = DestPos.y * fLerpRatio + CameraPos.y * (1 - fLerpRatio);
		}
	}
}

void UCameraComponent::SetMainCamera(bool _Value)
{
	IsMainCamera = _Value;
}