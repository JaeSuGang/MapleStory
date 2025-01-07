#pragma once
#include "Level/Level.h"

class UMapBase : public ULevel
{
public:
	/* 생성자와 오버라이드 */
	UMapBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;


public:
	void LoadXMLToMap(string strPath);


protected:
};

