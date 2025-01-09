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

public:
	/* �����ڿ� �������̵� */
	UMapBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;


public:
	void LoadXMLToMap(string strMapPath, string strImgName);


protected:
};

