#include "EnginePch.h"
#include "RenderCore/Widget.h"

void UWidget::SetPSShaderID(int _ID)
{
	PSShaderID = _ID;
}

void UWidget::SetTextureID(int _ID)
{
	TextureID = _ID;
}

int UWidget::GetPSShaderID() const
{
	return PSShaderID;
}

int UWidget::GetTextureID() const
{
	return TextureID;
}

FVector3 UWidget::GetPosition() const
{
	return Position;
}

FVector3 UWidget::GetSize() const
{
	return Size;
}

void UWidget::SetPosition(FVector3 _Pos)
{
	Position = _Pos;
}

void UWidget::SetSize(FVector3 _Size)
{
	Size = _Size;
}
