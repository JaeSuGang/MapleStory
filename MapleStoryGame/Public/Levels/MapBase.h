#pragma once
#include "Level/Level.h"

class UMapBase : public ULevel
{
public:
	/* �����ڿ� �������̵� */
	UMapBase();

	void BeginPlay() override;

	void Tick(float fDeltaTime) override;


public:
	void LoadXMLToMap(string strPath);


protected:
};

