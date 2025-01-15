#include "GamePch.h"
#include "Actions/BP_DoubleJumpAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"

BP_DoubleJumpAction::BP_DoubleJumpAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.DoubleJump");
}

void BP_DoubleJumpAction::StartAction(AActor* Instigator)
{
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent && !AttributeComponent->HasAttributeExact("Status.Falling"))
		return;

	if (!AttributeComponent->HasAttributeExact("Status.CanDoubleJump"))
		return;

	AttributeComponent->RemoveAttribute("Status.CanDoubleJump");

	UActionComponent* ActionComponent = Instigator->GetComponentByClass<UActionComponent>();
	if (ActionComponent)
	{
		ActionComponent->StartActionByName(Instigator, "Action.GustShift");
	}

}
