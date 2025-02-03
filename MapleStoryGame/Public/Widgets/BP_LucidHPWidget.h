#pragma once
#include "RenderCore/Widget.h"

class BP_LucidHPWidget : public UWidget
{
public:
	BP_LucidHPWidget()
	{
		this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.backgrnd.png", { -400.0f, 360.0f, 1.0f }, { 37.0f, 37.0f, 1.0f});
		this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.Mob.8880140.png", { -400.0f, 360.0f, 1.0f }, { 25.0f, 25.0f, 1.0f});
	}
};

