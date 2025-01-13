#include "GamePch.h"
#include "Actions/BP_MoveAction.h"
#include "GameplayTags/GameplayTagsManager.h"

BP_MoveAction::BP_MoveAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.Move");
}

void BP_MoveAction::StartAction(AActor* Instigator)
{

}
