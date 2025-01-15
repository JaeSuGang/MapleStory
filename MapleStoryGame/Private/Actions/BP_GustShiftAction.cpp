#include "GamePch.h"
#include "Actions/BP_GustShiftAction.h"
#include "Actors/Skills/BP_GustShiftSkill_0.h"
#include "Actors/Skills/BP_GustShiftSkill_1.h"
#include "World/World.h"
#include "Engine/KeyInputSubsystem.h"
#include "GameplayTags/GameplayTagsManager.h"

BP_GustShiftAction::BP_GustShiftAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.GustShift");
}

void BP_GustShiftAction::StartAction(AActor* Instigator)
{
	if (GEngine->KeyInputSubsystem->GetKey(VK_UP, UKeyInputSubsystem::EKeyState::Triggered))
	{
	}
	else
	{
		GetWorld()->SpawnActor<BP_GustShiftSkill_0>();
		GetWorld()->SpawnActor<BP_GustShiftSkill_1>();

		FTransform Transform = Instigator->GetTransform();

		if (Transform.Rotation.y >= 0 && Transform.Rotation.y < 180)
		{

		}
	}
}
