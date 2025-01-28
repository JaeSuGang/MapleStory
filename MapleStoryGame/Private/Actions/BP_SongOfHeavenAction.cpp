#include "GamePch.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"
#include "World/World.h"

#include "Actions/BP_SongOfHeavenAction.h"
#include "Actors/Skills/BP_SongOfHeavenAtom.h"
#include "Actors/Skills/BP_SongOfHeavenEffect.h"

BP_SongOfHeavenAction::BP_SongOfHeavenAction()
	:
	Effect{}
{
	Cooldown = 0.0f;

	IsTickEnabled = true;

	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.SongOfHeaven");
}

void BP_SongOfHeavenAction::StartAction(AActor* Instigator)
{
	shared_ptr<BP_SongOfHeavenEffect> SharedEffect = Effect.lock();

	if (!SharedEffect.get())
	{
		Effect = GetWorld()->SpawnActor<BP_SongOfHeavenEffect>()->GetWeak<BP_SongOfHeavenEffect>();
		Effect.lock()->SetInstigator(Instigator);
	}

	if (SharedEffect.get())
		SharedEffect->AddLifeTime(0.1f);

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

	if (Cooldown <= 0.0f)
	{
		Cooldown = 0.05f;

		BP_SongOfHeavenAtom* _Atom = GetWorld()->SpawnActor<BP_SongOfHeavenAtom>();
		_Atom->SetInstigator(Instigator);
	}

	else
	{
		Cooldown -= GEngine->TimeSubsystem->GetDeltaTime();
	}
}

void BP_SongOfHeavenAction::Tick(float fDeltaTime)
{

}
