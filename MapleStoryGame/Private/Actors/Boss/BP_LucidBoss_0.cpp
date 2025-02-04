#include "GamePch.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Engine/RandomManager.h"
#include "World/World.h"

#include "Actors/Boss/BP_LucidBoss_0.h"
#include "Actions/BP_TakeDamageAction.h"
#include "Actors/Boss/BP_LucidBlade.h"

BP_LucidBoss_0::BP_LucidBoss_0()
{
	BossResourceName = "3005727.img";

	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();

	AttributeComponent->AddAttribute("ActorType.Boss");

	AttributeComponent->AddAttribute("Status.Hitable");

	Attack1Timer = GEngine->RandomManager->GenerateRandomFloatValue(1.0f, 1.0f);
}

void BP_LucidBoss_0::BeginPlay()
{
	Super::BeginPlay();

	this->InitAttributes();

	this->InitTexture();

	this->InitAnimations();

	this->InitActions();

	this->InitPhysics();

	RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
}

void BP_LucidBoss_0::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	CheckAttack1Logic(fDeltaTime);
	
	RenderComponent->PlayAnimation(fDeltaTime);

	if (Flower && RenderComponent->GetCurrentAnimation() == EAnimationName::Die)
	{
		Flower->Destroy();
		Flower = nullptr;
	}

	if (RenderComponent->GetHasPassedLastFrame())
	{
		if (RenderComponent->GetCurrentAnimation() == EAnimationName::Die)
			this->Destroy();

		else if (RenderComponent->GetCurrentAnimation() == EAnimationName::BossAttack1)
		{
			RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
		}
	}
}

void BP_LucidBoss_0::InitAttributes()
{
	AttributeComponent->AddAttribute("Value.Hp", 1200000000000.0f);

	AttributeComponent->AddAttribute("Value.MaxHp", 1200000000000.0f);

	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}

void BP_LucidBoss_0::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(RENDER_LAYER_MONSTER);

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\" + BossResourceName + "\\stand\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_LucidBoss_0::InitAnimations()
{
	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Stand, "Resources\\Textures\\Monsters\\" + BossResourceName + "\\stand", 100);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Monsters\\" + BossResourceName + "\\die", 110);

	RenderComponent->AddAnimationByFolder(EAnimationName::BossAttack1, "Resources\\Textures\\Monsters\\" + BossResourceName + "\\bossAttack1", 120);

}

void BP_LucidBoss_0::InitActions()
{
	ActionComponent->AddAction<BP_TakeDamageAction>();
}

void BP_LucidBoss_0::SetFlower(AActor* _Flower)
{
	Flower = _Flower;
}

void BP_LucidBoss_0::SpawnBlades()
{
	for (int i = 0; i < 8; i++)
		GetWorld()->SpawnActor<BP_LucidBlade>()->SetInstigator(this);
}

void BP_LucidBoss_0::CheckAttack1Logic(float fDeltaTime)
{
	if (Attack1Timer <= 0.0f)
	{
		Attack1Timer = GEngine->RandomManager->GenerateRandomFloatValue(15.0f, 25.0f);

		RenderComponent->AddAnimationEvent(EAnimationName::BossAttack1, 23, [this]() {this->SpawnBlades(); });

		RenderComponent->SetCurrentAnimation(EAnimationName::BossAttack1);
	}
	else
		Attack1Timer -= fDeltaTime;
}

void BP_LucidBoss_0::InitPhysics()
{
	PhysicsComponent->InitializeBodyWithNoGravity(b2BodyType::b2_staticBody);

	PhysicsComponent->InitializeHitbox(Transform.Scale.x * 0.6f, Transform.Scale.y * 0.8f);
}
