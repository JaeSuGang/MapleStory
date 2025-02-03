#pragma once
#include "RenderCore/Widget.h"

#define HP_IMAGE_LENGTH 770.0f

class BP_LucidHPWidget : public UWidget
{
public:
	BP_LucidHPWidget();

public:
	void SetLifeGauge(int _nLife, float _fPercent);

protected:
	int HPSubimageIndex;
	int LifeSubimageIndex;
};

