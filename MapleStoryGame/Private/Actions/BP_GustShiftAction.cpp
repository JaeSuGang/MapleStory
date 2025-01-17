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
	ASkillBase* Skill1 = GetWorld()->SpawnActor<BP_GustShiftSkill_0>();
	Skill1->SetInstigator(Instigator);
	ASkillBase* Skill2 = GetWorld()->SpawnActor<BP_GustShiftSkill_1>();
	Skill2->SetInstigator(Instigator);

	FTransform& CharacterTransform = Instigator->GetTransform();
	FTransform& Skill1Transform = Skill1->GetTransform();
	FTransform& Skill2Transform = Skill2->GetTransform();

	UPhysicsComponent* PhysicsComponent = Instigator->GetComponentByClass<UPhysicsComponent>();

	if (GEngine->KeyInputSubsystem->GetKey(VK_UP, UKeyInputSubsystem::EKeyState::Triggered))
	{
		Skill1Transform.Rotation.z = 270.0f;
		Skill2Transform.Rotation.z = 270.0f;

		PhysicsComponent->AddYVelocity(900.0f);
	}

	else
	{
		bool bIsLeftDirection = ((int)CharacterTransform.Rotation.y % 360 < 90 || (int)CharacterTransform.Rotation.y % 360 > 270);

		Skill1Transform.Rotation = CharacterTransform.Rotation;
		Skill2Transform.Rotation = CharacterTransform.Rotation;

		PhysicsComponent->AddYVelocity(350.0f);

		if (bIsLeftDirection)
			PhysicsComponent->SetXVelocity(-650.0f);
		else
			PhysicsComponent->SetXVelocity(650.0f);
	}


}
