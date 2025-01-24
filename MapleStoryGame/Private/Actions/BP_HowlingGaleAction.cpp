#include "GamePch.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "World/World.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"

#include "Actions/BP_HowlingGaleAction.h"
#include "Actors/Skills/BP_HowlingGaleBall.h"

BP_HowlingGaleAction::BP_HowlingGaleAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.HowlingGale");
}

void BP_HowlingGaleAction::StartAction(AActor* Instigator)
{
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Shoot1);
	}
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (RenderComponent && AttributeComponent)
	{
		AttributeComponent->AddAttribute("Status.Attacking.Shoot1");
		RenderComponent->AddAnimationEvent(EAnimationName::Shoot1, 5, std::bind((void(UAttributeComponent::*)(string))(&UAttributeComponent::RemoveAttribute), AttributeComponent, "Status.Attacking.Shoot1"));
	}

	BP_HowlingGaleBall* HowlingGaleBall = GetWorld()->SpawnActor<BP_HowlingGaleBall>();
	FVector3 _BallPos = Instigator->GetTransform().Position;
	_BallPos.y += 400.0f;
	HowlingGaleBall->SetPosition(_BallPos);
}
