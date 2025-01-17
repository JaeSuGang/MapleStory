#include "GamePch.h"
#include "Actions/BP_TakeDamageAction.h"
#include "Actor/Actor.h"
#include "Attributes/AttributeComponent.h"

void BP_TakeDamageAction::StartAction(AActor* Instigator)
{
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->HasAttributeExact("Value.Hp"))
		{

		}
	}
}
