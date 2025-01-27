#include "GamePch.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"
#include "World/World.h"

#include "Actions/BP_SongOfHeavenAction.h"
#include "Actors/Skills/BP_SongOfHeavenAtom.h"

BP_SongOfHeavenAction::BP_SongOfHeavenAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.SongOfHeaven");
}

void BP_SongOfHeavenAction::StartAction(AActor* Instigator)
{
	URenderComponent* RenderComponent = Instigator->GetComponentByClass<URenderComponent>();
	if (RenderComponent)
	{
		RenderComponent->SetCurrentAnimation(EAnimationName::Shoot1);
		// RenderComponent->SetTextureByName("Resources\\Textures\\Avatars\\WindBreaker\\Shoot1\\3.png");
		// RenderComponent->SetActorScaleByTextureSize();
	}

	UAttributeComponent* AttributeComponent = Instigator->GetComponentByClass<UAttributeComponent>();
	if (RenderComponent && AttributeComponent)
	{
		AttributeComponent->AddAttribute("Status.Attacking.ShootMoving");
	}

	BP_SongOfHeavenAtom* _Atom = GetWorld()->SpawnActor<BP_SongOfHeavenAtom>();
	_Atom->SetInstigator(Instigator);


}
