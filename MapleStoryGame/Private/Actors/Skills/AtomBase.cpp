#include "GamePch.h"
#include "Actors/Skills/AtomBase.h"
#include "RenderCore/RenderComponent.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "PhysicsCore/PhysicsSubsystem.h"
#include "World/World.h"
#include "Attributes/AttributeComponent.h"
#include "Actions/ActionComponent.h"
#include "Engine/Engine.h"
#include "Engine/RandomManager.h"

AAtomBase::AAtomBase()
{
	IsHit = false;

	LifeTime = 0.0f;

	ElapsedTime = 0.0f;

	FindTargetCooldown = 0.0f;

	DamageCooldown = 0.0f;

	RenderComponent = CreateDefaultSubobject<URenderComponent>();

	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>();
}

void AAtomBase::BeginPlay()
{
	Super::BeginPlay();

	this->InitTexture();

	this->InitAnimations();

	this->InitPhysics();

	RenderComponent->SetCurrentAnimation(EAnimationName::Idle);
}

void AAtomBase::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	ElapsedTime += fDeltaTime;
	LifeTime -= fDeltaTime;

	RenderComponent->PlayAnimation(fDeltaTime);

	if (LifeTime < 0.0f)
		this->Destroy();

	else if (LifeTime < 1.0f)
		RenderComponent->AddAlphaValue(-fDeltaTime);
}

void AAtomBase::SetPosition(FVector3 _Position)
{
	if (PhysicsComponent->GetBodyID().index1 == 0)
		Super::SetPosition(_Position);

	else
		PhysicsComponent->SetPosition(_Position);
}

void AAtomBase::SetRotation(FVector3 _Rotation)
{
	if (PhysicsComponent->GetBodyID().index1 == 0)
		Super::SetRotation(_Rotation);

	else
		PhysicsComponent->SetRotation(_Rotation);
}

void AAtomBase::AddZRotation(float _ZRotation)
{
	if (PhysicsComponent->GetBodyID().index1 == 0)
		Super::AddZRotation(_ZRotation);

	else
		PhysicsComponent->AddZRotation(_ZRotation);
}

void AAtomBase::InitTexture()
{
	RenderComponent->SetMeshIDByName("Plane");

	RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);

	RenderComponent->SetBlendMode(1);

	RenderComponent->SetSortingLayer(RENDER_LAYER_FRONT_SKILL);
}

void AAtomBase::InitAnimations()
{
	RenderComponent->EnableAnimation();
}

void AAtomBase::InitPhysics()
{
	PhysicsComponent->InitializeBodyWithNoGravity(b2BodyType::b2_dynamicBody);
}

bool AAtomBase::FindTarget(float _fRadius)
{
	PhysicsComponent->FetchCircleOverlappedPhysicsComponents(_fRadius, Transform.Position, TempPhysicsComponentVector);

	TempActorsVector.clear();

	for (UPhysicsComponent* _PhysicsComponent : TempPhysicsComponentVector)
	{
		AActor* _Owner = _PhysicsComponent->GetOwner();

		if (UAttributeComponent* _Attribute = _Owner->GetComponentByClass<UAttributeComponent>())
		{
			if (_Attribute->HasAttributeExact("Status.Hitable"))
			{
				TempActorsVector.push_back(_PhysicsComponent->GetOwner());
			}
		}
	}

	int _nSize = (int)TempActorsVector.size();
	if (_nSize <= 0)
	{
		Target = shared_ptr<AActor>();
		return false;
	}

	int _nRandomIndex = std::rand() % _nSize;

	Target = TempActorsVector[_nRandomIndex]->GetShared<AActor>();
	return true;
}

void AAtomBase::SetInstigator(AActor* _Instigator)
{
	Instigator = _Instigator;
}

void AAtomBase::SetRandomRotation()
{
	SetRotation({ 0.0f, 0.0f, GEngine->RandomManager->GenerateRandomFloatValue(0.0f, 360.0f) });
}

void AAtomBase::SetRandomPosition(FVector3 _Position, float _Range)
{
	_Position.x += GEngine->RandomManager->GenerateRandomFloatValue(-_Range, _Range);
	_Position.y += GEngine->RandomManager->GenerateRandomFloatValue(-_Range, _Range);
	SetPosition(_Position);
}

void AAtomBase::SetPositionRelativeToInstigator(float fLeft, float fUp)
{
	if (Instigator)
	{
		FTransform& InstigatorTransform = Instigator->GetTransform();

		bool bIsLeftDirection = ((int)InstigatorTransform.Rotation.y % 360 < 90 || (int)InstigatorTransform.Rotation.y % 360 > 270);

		Transform.Position = InstigatorTransform.Position;
		if (bIsLeftDirection)
		{
			Transform.Position.x -= fLeft;
			Transform.Position.y += fUp;
		}
		else
		{
			Transform.Position.x += fLeft;
			Transform.Position.y += fUp;
		}
	}
}