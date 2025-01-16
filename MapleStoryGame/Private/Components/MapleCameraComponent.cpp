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

		FVector3 ActorPos = Owner->GetTransform().Position;
		FVector3 CameraPos = Camera.Transform.Position;

		float fLerpRatio = 2.5f * fDeltaTime;

		Camera.Transform.Position.x = ActorPos.x * fLerpRatio + CameraPos.x * (1 - fLerpRatio);
		Camera.Transform.Position.y = (ActorPos.y + 130.0f) * fLerpRatio + CameraPos.y * (1 - fLerpRatio);

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
