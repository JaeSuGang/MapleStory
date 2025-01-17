#include "GamePch.h"
#include "Actions/BP_ProneAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"

BP_ProneAction::BP_ProneAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.Prone");
}

void BP_ProneAction::StartAction(AActor* Instigator)
{
	/* TagComponent */
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->HasAttributeExact("Status.Falling"))
			return;

		if (AttributeComponent->ContainsAttribute("Status.Walking"))
			return;

		AttributeComponent->AddAttribute("Status.Proning");
	}

	/* RenderComponent */
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Prone);
	}
}
