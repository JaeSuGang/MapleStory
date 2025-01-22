#include "GamePch.h"
#include "Actors/Boss/BP_LucidBoss_0.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Actions/BP_TakeDamageAction.h"

BP_LucidBoss_0::BP_LucidBoss_0()
{
	BossResourceName = "3005727.img";

	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();
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

	RenderComponent->PlayAnimation(fDeltaTime);

	if (RenderComponent->GetHasPassedLastFrame())
	{
		if (RenderComponent->GetCurrentAnimation() == EAnimationName::Die)
			this->Destroy();
		else
			RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
	}
}

void BP_LucidBoss_0::InitAttributes()
{
	AttributeComponent->AddAttribute("Value.Hp", 6000000000000.0f);

	AttributeComponent->AddAttribute("Value.Speed", 100.0f);
}

void BP_LucidBoss_0::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(8);

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\" + BossResourceName + "\\stand\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void BP_LucidBoss_0::InitAnimations()
{
	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Stand, "Resources\\Textures\\Monsters\\" + BossResourceName + "\\stand", 100);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Monsters\\" + BossResourceName + "\\die", 110);

}

void BP_LucidBoss_0::InitActions()
{
	ActionComponent->AddAction<BP_TakeDamageAction>();
}

void BP_LucidBoss_0::SetResourcePath(string strPath)
{
	BossResourceName = strPath;
}

void BP_LucidBoss_0::InitPhysics()
{
	PhysicsComponent->InitializeBodyWithNoGravity(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeFootCollider(Transform.Scale.y * -0.49f);

	PhysicsComponent->InitializeHitbox(Transform.Scale.x, Transform.Scale.y);
}
