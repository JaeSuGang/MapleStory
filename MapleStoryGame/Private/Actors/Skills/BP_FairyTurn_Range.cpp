#include "GamePch.h"
#include "Actors/Skills/BP_FairyTurn_Range.h"
#include "RenderCore/RenderComponent.h"
#include "Engine/Engine.h"
#include "World/World.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actions/ActionComponent.h"
#include "Actions/BP_TakeDamageAction.h"

BP_FairyTurn_Range::BP_FairyTurn_Range()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();
}

void BP_FairyTurn_Range::BeginPlay()
{
	Super::BeginPlay();

	SetPositionRelativeToInstigator(300.0f, 100.0f);

	vector<b2ShapeId> OverlappedShapeIds;
	b2QueryFilter Filter{};
	Filter.categoryBits = -1;
	Filter.maskBits = MOB_HITBOX_COLLISION_FLAG;
	GEngine->GetWorld()->PhysicsSubsystem->FetchBoxOverlap(Transform.Scale.x, Transform.Scale.y, Transform, Filter, &OverlappedShapeIds);

	for (b2ShapeId& ShapeID : OverlappedShapeIds)
	{
		UPhysicsComponent* PhysicsComponent = GEngine->GetWorld()->PhysicsSubsystem->GetPhysicsComponentByShapeID(ShapeID);
		UActionComponent* ActionComponent = PhysicsComponent->GetOwner()->GetComponentByClass<UActionComponent>();

		if (ActionComponent)
		{
			FDamageInfo DamageInfo{};
			DamageInfo.Damage = 1000.0f;
			DamageInfo.HitCountLeft = 5;
			DamageInfo.HitDelay = 0.2f;

			ActionComponent->StartActionByNameWithParameter(ActionComponent->GetOwner(), "Action.TakeDamage", &DamageInfo);
		}
	}


	this->Destroy();
}

void BP_FairyTurn_Range::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->SetPositionRelativeToInstigator(200.0f, 0.0f);
}

void BP_FairyTurn_Range::InitAttributes()
{
	Super::InitAttributes();
}

void BP_FairyTurn_Range::InitTexture()
{
	Super::InitTexture();

	RenderComponent->SetPixelShaderByName(TRANSPARENT_PIXEL_SHADER_NAME);

	Transform.Scale = { 550.0f, 300.0f, 1.0f };
}

