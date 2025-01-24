#include "GamePch.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "World/World.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"

#include "Actions/BP_MistralSpringAction.h"
#include "Actors/Skills/BP_MistralSpringScreen.h"

BP_MistralSpringAction::BP_MistralSpringAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.MistralSpring");
}

void BP_MistralSpringAction::StartAction(AActor* Instigator)
{
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		AttributeComponent->AddAttribute("Status.Stunned");
	}

	BP_MistralSpringScreen* MistralSpringEffect0 = GetWorld()->SpawnActor<BP_MistralSpringScreen>();
}
