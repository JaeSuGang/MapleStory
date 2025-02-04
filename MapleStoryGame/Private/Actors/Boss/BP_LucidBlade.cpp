#include "GamePch.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/RandomManager.h"
#include "Attributes/AttributeComponent.h"

#include "Actors/Boss/BP_LucidBlade.h"
#include "Actors/Characters/CharacterBase.h"

BP_LucidBlade::BP_LucidBlade()
{
	LifeTime = 8.0f;
}

void BP_LucidBlade::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	PhysicsComponent->FetchOverlappedCharacter(TempActorsVector);

	if (TempActorsVector.size() > 0)
	{
		for (AActor* _Actor : TempActorsVector)
		{
 			UAttributeComponent* _AttributeComponent = _Actor->GetComponentByClass<UAttributeComponent>();
			if (!_AttributeComponent || !_AttributeComponent->HasAttributeExact("ActorType.Character"))
				continue;

			if (std::find(AlreadyHitActors.begin(), AlreadyHitActors.end(), _AttributeComponent->GetOwner()) != AlreadyHitActors.end())
				continue;

			AlreadyHitActors.push_back(_AttributeComponent->GetOwner());

			ACharacterBase* Character = static_cast<ACharacterBase*>(_AttributeComponent->GetOwner());
			Character->TakeDamage(5000.0f);

			break;
		}
	}

	PhysicsComponent->SetForwardVelocity(-100.0f);
}

void BP_LucidBlade::BeginPlay()
{
	Super::BeginPlay();

	FTransform TransformToApply = Instigator->GetTransform();

	TransformToApply.Position.x += 0.0f;
	TransformToApply.Position.y += 100.0f;
	TransformToApply.Rotation = { 0.0f, 0.0f, GEngine->RandomManager->GenerateRandomFloatValue(0.0f, 360.0f) };

	SetPosition(TransformToApply.Position);
	SetRotation(TransformToApply.Rotation);
	Transform.Position = TransformToApply.Position;
	Transform.Rotation = TransformToApply.Rotation;
}

void BP_LucidBlade::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\3005743.img\\1.png");

	RenderComponent->SetActorScaleByTextureSize();

}

void BP_LucidBlade::InitAnimations()
{
	Super::InitAnimations();

	RenderComponent->AddAnimationByFolder(EAnimationName::Idle, "Resources\\Textures\\Monsters\\3005743.img", 100);
}

void BP_LucidBlade::InitPhysics()
{
	Super::InitPhysics();
}