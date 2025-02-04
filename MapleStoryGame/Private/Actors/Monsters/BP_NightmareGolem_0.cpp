#include "GamePch.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Engine/RandomManager.h"

#include "Actors/Monsters/BP_NightmareGolem_0.h"

BP_NightmareGolem_0::BP_NightmareGolem_0()
{
	MobResourcePath = "8880161.img";
}

void BP_NightmareGolem_0::BeginPlay()
{
	Super::BeginPlay();

	SetPosition({ GEngine->RandomManager->GenerateRandomFloatValue(100.0f, 1500.0f), 200.0f, 0.0f });
}

void BP_NightmareGolem_0::InitAttributes()
{
	Super::InitAttributes();

	AttributeComponent->AddAttribute("Value.Hp", 15'000'000'000.0f);
	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}

void BP_NightmareGolem_0::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeMobFootCollider(Transform.Scale.y * -0.49f);

	PhysicsComponent->InitializeMobCollider(Transform.Scale.x, Transform.Scale.y);

	PhysicsComponent->InitializeHitbox(Transform.Scale.x, Transform.Scale.y);
}
