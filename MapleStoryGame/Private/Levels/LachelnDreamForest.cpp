#include "GamePch.h"
#include "Levels/LachelnDreamForest.h"
#include "World/World.h"
#include "Attributes/AttributeComponent.h"
#include "Engine/RandomManager.h"

#include "Actors/Characters/BP_WindBreaker.h"
#include "Actors/Boss/BP_LucidBoss_0.h"
#include "Actors/Boss/BP_LucidFlower.h"
#include "Actors/Screen/BP_LucidIntro.h"
#include "Widgets/BP_LucidHPWidget.h"
#include "Actors/Monsters/BP_NightmareGolem_0.h"

ULachelnDreamForest::ULachelnDreamForest()
{
	BossHPWidget = nullptr;

	GolemSpawnTimer = 5.0f;
}

ULachelnDreamForest::~ULachelnDreamForest()
{
	GEngine->GetGameInstance()->ClearWidgets(1);
}

void ULachelnDreamForest::BeginPlay()
{
	Super::BeginPlay();

	this->LoadXMLToMap("Resources\\XMLs\\Map.Map.Map4.450004750.img.xml", "Lacheln.img.xml");

	BossHPWidget = GEngine->GetGameInstance()->AddWidget<BP_LucidHPWidget>(1);

	MainActor = GetWorld()->SpawnActorReturnShared<BP_WindBreaker>();
	BP_LucidFlower* _Flower = GetWorld()->SpawnActor<BP_LucidFlower>();
	Flower = _Flower->GetWeak<BP_LucidFlower>();

	BP_LucidBoss_0* _LucidPhase1 = GetWorld()->SpawnActor<BP_LucidBoss_0>();
	LucidPhase1 = _LucidPhase1->GetWeak<BP_LucidBoss_0>();

	_LucidPhase1->SetFlower(_Flower);
	_Flower->SetPosition({995.0f, 132.0f, 0.0f});
	_LucidPhase1->SetPosition({1000.0f, 235.0f, 0.0f});

}

void ULachelnDreamForest::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	this->CheckGolemSpawn(fDeltaTime);

	if (BP_LucidBoss_0* _LucidPhase1 = LucidPhase1.lock().get())
	{
		UAttributeComponent* AttributeComponent = _LucidPhase1->GetComponentByClass<UAttributeComponent>();

		int _nLife = 9;
		float _Percent = 100.0f;
	
		if (AttributeComponent->HasAttributeExact("Value.MaxHp"))
		{
			float MaxHp = AttributeComponent->GetAttributeValue("Value.MaxHp");
			float Hp = AttributeComponent->GetAttributeValue("Value.Hp");
			_Percent = (std::fmod(Hp, MaxHp / 10)) / (MaxHp / 10) * 100;
			_nLife = (int)(Hp / (MaxHp / 10));

			if (MaxHp == Hp)
			{
				_nLife = 9;
				_Percent = 100.0f;
			}
		}

		BossHPWidget->SetLifeGauge(_nLife, _Percent);
	}
}

void ULachelnDreamForest::CheckGolemSpawn(float _fDeltaTime)
{
	if (GolemSpawnTimer <= 0.0f)
	{
		GolemSpawnTimer = GEngine->RandomManager->GenerateRandomFloatValue(10.0f, 20.0f);

		BP_NightmareGolem_0* Golem = GEngine->GetWorld()->SpawnActor<BP_NightmareGolem_0>();
	}
	else
		GolemSpawnTimer -= _fDeltaTime;
}
