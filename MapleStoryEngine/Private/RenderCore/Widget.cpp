#include "EnginePch.h"
#include "RenderCore/Widget.h"
#include "RenderCore/Material.h"

void UWidget::AddSubImageByTextureName(string _Name, FVector3 _Pos, FVector3 _Size)
{
	FWidgetSubImage _SubImage{};

	_SubImage.Material = std::make_shared<UMaterial>();
	_SubImage.Material->SetTextureByName(_Name);
	_SubImage.Material->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
	_SubImage.Position = _Pos;
	_SubImage.Size = _Size;

	SubImages.push_back(_SubImage);
}
