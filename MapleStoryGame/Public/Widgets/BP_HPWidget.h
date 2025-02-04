#pragma once
#include "RenderCore/Widget.h"

#define HP_IMAGE_LENGTH 172.0f

class BP_HPWidget : public UWidget
{
public:
	BP_HPWidget();

public:
	void SetLifeGauge(float _fRate);
	void SetMPGauge(float _fRate);

	void SetHPFlickerIndex(int _nIndex);

protected:
	int HPSubimageIndex;
	int MPSubimageIndex;
};

