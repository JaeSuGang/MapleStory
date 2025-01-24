#include "GamePch.h"
#include "Actors/Monsters/MobBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Actions/BP_TakeDamageAction.h"

AMobBase::AMobBase()
{
	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>();

	ActionComponent = CreateDefaultSubobject<UActionComponent>();

	AttributeComponent->AddAttribute("ActorType.Monster");
}

void AMobBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitAttributes();

	this->InitTexture();

	this->InitAnimations();

	this->InitActions();

	this->InitPhysics();

	RenderComponent->SetCurrentAnimation(EAnimationName::Stand);
}

void AMobBase::Tick(float fDeltaTime)
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

void AMobBase::InitAttributes()
{

}

void AMobBase::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(0);

	RenderComponent->SetSortingLayer(RENDER_LAYER_MONSTER);

	RenderComponent->SetTextureByName("Resources\\Textures\\Monsters\\" + MobResourcePath + "\\stand\\1.png");

	RenderComponent->SetActorScaleByTextureSize();
}

void AMobBase::InitAnimations()
{
	RenderComponent->EnableAnimation();

	RenderComponent->AddAnimationByFolder(EAnimationName::Stand, "Resources\\Textures\\Monsters\\" + MobResourcePath + "\\stand", 150);

	RenderComponent->AddAnimationByFolder(EAnimationName::Move, "Resources\\Textures\\Monsters\\" + MobResourcePath + "\\move", 150);

	RenderComponent->AddAnimationByFolder(EAnimationName::Hit, "Resources\\Textures\\Monsters\\" + MobResourcePath + "\\hit", 250);

	RenderComponent->AddAnimationByFolder(EAnimationName::Die, "Resources\\Textures\\Monsters\\" + MobResourcePath + "\\die", 100);

}

void AMobBase::InitActions()
{
	ActionComponent->AddAction<BP_TakeDamageAction>();
}

void AMobBase::SetResourcePath(string strPath)
{
	MobResourcePath = strPath;
}

void AMobBase::InitPhysics()
{
	PhysicsComponent->InitializeBody(b2BodyType::b2_dynamicBody);

	PhysicsComponent->InitializeMobFootCollider(Transform.Scale.y * -0.49f);

	PhysicsComponent->InitializeHitbox(Transform.Scale.x, Transform.Scale.y);
}

void AMobBase::SetPosition(FVector3 _Position)
{
	PhysicsComponent->SetPosition(_Position);
}
