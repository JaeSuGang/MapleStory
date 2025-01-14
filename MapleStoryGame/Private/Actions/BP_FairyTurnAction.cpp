#include "GamePch.h"
#include "Actions/BP_FairyTurnAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"

BP_FairyTurnAction::BP_FairyTurnAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.FairyTurn");
}

void BP_FairyTurnAction::StartAction(AActor* Instigator)
{
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::SwingT1);
	}
}
