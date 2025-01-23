#include "GamePch.h"
#include "Actions/BP_IdleWhimAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "World/World.h"

#include "Actors/Skills/BP_IdleWhimAtom.h"
#include "Actors/Skills/BP_IdleWhimEffect.h"

BP_IdleWhimAction::BP_IdleWhimAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.IdleWhim");
}

void BP_IdleWhimAction::StartAction(AActor* Instigator)
{
	BP_IdleWhimEffect* IdleWhimActor = GetWorld()->SpawnActor<BP_IdleWhimEffect>();
	IdleWhimActor->SetInstigator(Instigator);
	IdleWhimActor->SetPosition(Instigator->GetTransform().Position);
}
