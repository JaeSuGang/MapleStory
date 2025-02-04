#include "GamePch.h"
#include "RenderCore/Material.h"

#include "Widgets/BP_HPWidget.h"

BP_HPWidget::BP_HPWidget()
{
	/* 스테이터스 바 */
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\Player_StatusBar_Back.png", { 0.0f, -349.0f, 1.0f }, { 199.0f, 37.0f, 1.0f });

	HPSubimageIndex = this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\HPBar\\1.png", { 10.0f, -340.0f, 1.0f }, { 172.0f, 13.0f, 1.0f });

	MPSubimageIndex = this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\MPBar\\1.png", { 10.0f, -357.0f, 1.0f }, { 172.0f, 13.0f, 1.0f });

	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\Player_StatusBar_Front.png", { 0.0f, -340.0f, 1.0f }, { 205.0f, 70.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\Lv.png", { -55.0f, -317.0f, 1.0f }, { 41.0f, 10.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\mainBar.EXPBar.1366.layerback.png", { 0.0f, -380.0f, 1.0f }, { 1366.0f, 10.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\mainBar.EXPBar.1366.layerrelaxExp.png", { -317.0f, -381.0f, 1.0f }, { 700.0f, 7.0f, 1.0f });
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\mainBar.EXPBar.1366.layercover.png", { 0.0f, -380.0f, 1.0f }, { 1366.0f, 10.0f, 1.0f });

	/* 스킬 슬릇 */
	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\mainBar.quickSlot.backgrnd.png", { 400.0f, -337.0f, 1.0f }, { 557.0f, 67.0f, 1.0f });

	this->AddSubImageByTextureName("Resources\\Textures\\Widgets\\mainBar.quickSlot.layercover.png", { 400.0f, -337.0f, 1.0f }, { 562.0f, 73.0f, 1.0f });



}	

void BP_HPWidget::SetLifeGauge(float _fRate)
{
	if (_fRate <= 0.0f)
		_fRate = 0.0f;

	SubImages[HPSubimageIndex].Size.x = HP_IMAGE_LENGTH * _fRate;

	SubImages[HPSubimageIndex].Position.x = -76.0f + SubImages[HPSubimageIndex].Size.x / 2.0f;
}

void BP_HPWidget::SetMPGauge(float _fRate)
{
	if (_fRate <= 0.0f)
		_fRate = 0.0f;

	SubImages[MPSubimageIndex].Size.x = HP_IMAGE_LENGTH * _fRate;

	SubImages[MPSubimageIndex].Position.x = -335.0f + SubImages[MPSubimageIndex].Size.x / 2.0f;
}

void BP_HPWidget::SetHPFlickerIndex(int _nIndex)
{
	SubImages[HPSubimageIndex].Material->SetTextureByName("Resources\\Textures\\Widgets\\HPBar\\" + std::to_string(_nIndex) + ".png");
}
