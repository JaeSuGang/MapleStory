#include "GamePch.h"
#include "Actions/BP_GustShiftAction.h"
#include "Actors/Skills/BP_GustShiftSkill_0.h"
#include "Actors/Skills/BP_GustShiftSkill_1.h"
#include "World/World.h"
#include "Engine/KeyInputSubsystem.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "PhysicsCore/PhysicsComponent.h"

BP_GustShiftAction::BP_GustShiftAction()
{
	Tag = GameplayTagsManager->FindRegisteredTagExact("Action.GustShift");
}

void BP_GustShiftAction::StartAction(AActor* Instigator)
{
	if (GEngine->KeyInputSubsystem->GetKey(VK_UP, UKeyInputSubsystem::EKeyState::Triggered))
	{

	}
	else
	{
		AActor* Skill1 = GetWorld()->SpawnActor<BP_GustShiftSkill_0>();
		AActor* Skill2 = GetWorld()->SpawnActor<BP_GustShiftSkill_1>();

		FTransform& CharacterTransform = Instigator->GetTransform();
		FTransform& Skill1Transform = Skill1->GetTransform();
		FTransform& Skill2Transform = Skill2->GetTransform();

		bool bIsLeftDirection = ((int)CharacterTransform.Rotation.y % 360 < 90 || (int)CharacterTransform.Rotation.y % 360 > 270);

		Skill1Transform.Position = CharacterTransform.Position;
		Skill1Transform.Rotation = CharacterTransform.Rotation;
		Skill1Transform.Position.y += 1.0f;

		Skill2Transform.Position = CharacterTransform.Position;
		Skill2Transform.Rotation = CharacterTransform.Rotation;
		Skill2Transform.Position.y += 1.0f;

		UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();
		PhysicsComponent->AddYVelocity(7.0f);

		if (bIsLeftDirection)
			PhysicsComponent->SetXVelocity(-13.0f);
		else
			PhysicsComponent->SetXVelocity(13.0f);
	}


}
