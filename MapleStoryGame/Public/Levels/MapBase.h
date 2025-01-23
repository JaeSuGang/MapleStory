#pragma once
#include "Level/Level.h"

enum TileMode
{
	None = 0,
	Horizontal = 1,
	Vertical = 2,
	BothTile = Horizontal | Vertical,
	ScrollHorizontal = 4,
	ScrollVertical = 8
};

class UMapBase : public ULevel
{
	typedef ULevel Super;

	friend class UMapleCameraComponent;

public:
	/* 생성자와 오버라이드 */
	UMapBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;

public:
	AActor* GetMainActor() const;

	void LoadXMLToMap(string strMapPath, string strImgName);

protected:
	weak_ptr<AActor> MainActor;

	float VRTopInverted;
	float VRLeft;
	float VRBottomInverted;
	float VRRight;
};

