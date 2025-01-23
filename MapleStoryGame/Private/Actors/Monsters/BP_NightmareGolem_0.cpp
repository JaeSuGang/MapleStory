#include "GamePch.h"
#include "Actors/Monsters/BP_NightmareGolem_0.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"

BP_NightmareGolem_0::BP_NightmareGolem_0()
{
	MobResourcePath = "8880161.img";
}

void BP_NightmareGolem_0::InitAttributes()
{
	Super::InitAttributes();

	AttributeComponent->AddAttribute("Value.Hp", 150000000.0f);
	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}

void BP_NightmareGolem_0::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeFootCollider(Transform.Scale.y * -0.49f);

	PhysicsComponent->InitializeHitboxUnpassable(Transform.Scale.x, Transform.Scale.y);
}
