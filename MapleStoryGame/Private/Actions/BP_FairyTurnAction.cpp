#include "GamePch.h"
#include "Actions/BP_FairyTurnAction.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Actor/Actor.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"
#include "Attributes/AttributeComponent.h"
#include "Actors/Skills/BP_FairyTurn_0.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"

BP_FairyTurnAction::BP_FairyTurnAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.FairyTurn");
}

void BP_FairyTurnAction::StartAction(AActor* Instigator)
{
	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (AttributeComponent)
	{
		if (AttributeComponent->HasAttributeExact("Status.Proning"))
			return;
	}

	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::SwingT1);
	}

	if (RenderComponent && AttributeComponent)
	{
		AttributeComponent->AddAttribute("Status.Attacking.SwingT1");
		RenderComponent->AddAnimationEvent(EAnimationName::SwingT1, 6, std::bind((void(UAttributeComponent::*)(string))(&UAttributeComponent::RemoveAttribute), AttributeComponent, "Status.Attacking.SwingT1"));
	}

	

	ASkillBase* Skill1 = GetWorld()->SpawnActor<BP_FairyTurn_0>();
	Skill1->SetInstigator(Instigator);

	FTransform& CharacterTransform = Instigator->GetTransform();
	FTransform& Skill1Transform = Skill1->GetTransform();

	Skill1Transform.Rotation = CharacterTransform.Rotation;	

	/*  */
	


}
