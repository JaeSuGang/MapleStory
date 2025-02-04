#include "GamePch.h"
#include "Widgets/BP_LucidHPWidget.h"
#include "RenderCore/Material.h"

void BP_LucidHPWidget::SetLifeGauge(int _nLife, float _fPercent)
{
	string _ImagePath = "Resources\\Textures\\Widgets\\" + std::to_string(_nLife) + ".png";
	SubImages[LifeSubimageIndex].Material->SetTextureByName(_ImagePath);

	if (_nLife <= 0)
		_nLife = 0;

	if (_fPercent <= 0.0f)
		_fPercent = 0.0f;

	SubImages[HPSubimageIndex].Size.x = HP_IMAGE_LENGTH * _fPercent / 100.0f;
	SubImages[HPSubimageIndex].Size.y = 12.0f;
	SubImages[HPSubimageIndex].Size.z = 1.0f;

	SubImages[HPSubimageIndex].Position.x = -360.0f + SubImages[HPSubimageIndex].Size.x / 2.0f;
	SubImages[HPSubimageIndex].Position.y = 375.0f;
}

BP_LucidHPWidget::BP_LucidHPWidget()
{
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.backgrnd.png", { -381.0f, 366.0f, 1.0f }, { 37.0f, 37.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.Mob.8880140.png", { -380.0f, 365.0f, 1.0f }, { 25.0f, 25.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.backgrnd2.png", { -360.0f - 1.0f, 375.0f, 1.0f }, { 4.5f, 20.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.backgrnd3.png", { -360.0f + HP_IMAGE_LENGTH / 2, 375.0f, 1.0f }, { HP_IMAGE_LENGTH + 2.0f, 20.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.backgrnd4.png", { -360.0f + HP_IMAGE_LENGTH + 2.0f, 375.0f, 1.0f }, { 4.5f, 20.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.backgrnd5.png", { -345.0f, 355.0f, 1.0f }, { 39.0f, 17.0f, 1.0f });
	HPSubimageIndex = this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MobGage.Gage.10.0.png", { -375.0f, 365.0f, 1.0f }, { 250.0f, 12.0f, 1.0f });

	LifeSubimageIndex = this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\9.png", { -340.0f, 356.0f, 1.0f }, { 12.0f, 17.0f, 1.0f });
}
