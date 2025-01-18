#include "GamePch.h"
#include "Components/MapleCameraComponent.h"
#include "Engine/Engine.h"
#include "RenderCore/RenderSubsystem.h"
#include "Actor/Actor.h"
#include "World/World.h"
#include "Levels/MapBase.h"

void UMapleCameraComponent::TickComponent(float fDeltaTime)
{
	UActorComponent::TickComponent(fDeltaTime);

	if (IsMainCamera)
	{
		FCamera& Camera = GEngine->RenderSubsystem->GetCamera();

		if (Camera.IsFreeMode)
			return;

		Camera.Transform.Rotation = { 0.0f, 0.0f, 0.0f };
		Camera.Transform.Position.z = -450.0f;

		FVector3 ActorPos = Owner->GetTransform().Position;
		FVector3 CameraPos = Camera.Transform.Position;
		FVector3 PosOffset = { 0.0f, 130.0f, 0.0f };
		FVector3 DestPos = { ActorPos.x + PosOffset.x, ActorPos.y + PosOffset.y, 0.0f };

		if (std::abs(DestPos.x - CameraPos.x) > 2.0f || std::abs(DestPos.y - CameraPos.y) > 2.0f)
		{
			float fLerpRatio = 2.5f * fDeltaTime;

			Camera.Transform.Position.x = DestPos.x * fLerpRatio + CameraPos.x * (1 - fLerpRatio);
			Camera.Transform.Position.y = DestPos.y * fLerpRatio + CameraPos.y * (1 - fLerpRatio);

			UMapBase* MapLevel = static_cast<UMapBase*>(Owner->GetWorld()->GetLevel());
			if (Camera.Transform.Position.x - Camera.Width / 2 < MapLevel->VRLeft)
				Camera.Transform.Position.x = MapLevel->VRLeft + Camera.Width / 2;

			if (Camera.Transform.Position.x + Camera.Width / 2 > MapLevel->VRRight)
				Camera.Transform.Position.x = MapLevel->VRRight - Camera.Width / 2;

			if (Camera.Transform.Position.y - Camera.Height / 2 < MapLevel->VRBottomInverted)
				Camera.Transform.Position.y = MapLevel->VRBottomInverted + Camera.Height / 2;

			if (Camera.Transform.Position.y + Camera.Height / 2 > MapLevel->VRTopInverted)
				Camera.Transform.Position.y = MapLevel->VRTopInverted - Camera.Height / 2;

		}
	}
}
