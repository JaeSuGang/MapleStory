#include "GamePch.h"
#include "Levels/MapBase.h"
#include "TinyXML2/tinyxml2.h"
#include "Engine/Engine.h"
#include "World/World.h"
#include "Actors/ObjBase.h"
#include "RenderCore/RenderComponent.h"

UMapBase::UMapBase()
{

}

void UMapBase::BeginPlay()
{

}

void UMapBase::Tick(float fDeltaTime)
{

}

void UMapBase::LoadXMLToMap(string strMapPath, string strImgPath)
{
	tinyxml2::XMLDocument MapDocument;
	tinyxml2::XMLDocument ImgDocument;
	tinyxml2::XMLError Error;
	Error = MapDocument.LoadFile(strMapPath.data());
	if (Error)
		GEngine->DebugLog("XML 로드 실패", 2);

	Error = ImgDocument.LoadFile(strImgPath.data());
	if (Error)
		GEngine->DebugLog("XML 로드 실패", 2);

	tinyxml2::XMLElement* RootElement = MapDocument.FirstChildElement();

	tinyxml2::XMLElement* MapElement = RootElement->FirstChildElement();
	while (MapElement != nullptr)
	{
		const tinyxml2::XMLAttribute* MapElement_Attribute = MapElement->FindAttribute("name");

		string a = MapElement_Attribute->Value();

		tinyxml2::XMLError Error;

		int nNumberAttribute;

		Error = MapElement_Attribute->QueryIntValue(&nNumberAttribute);

		if (!Error)
		{
			tinyxml2::XMLElement* ObjElement = MapElement->FirstChildElement();

			while (ObjElement != nullptr)
			{
				string strName = ObjElement->FindAttribute("name")->Value();

				if (strName == "obj")
					break;

				ObjElement = ObjElement->NextSiblingElement();
			}

			if (ObjElement == nullptr)
			{
				MapElement = MapElement->NextSiblingElement();
				continue;
			}

			tinyxml2::XMLElement* ObjSubElement = ObjElement->FirstChildElement();


			while (ObjSubElement != nullptr)
			{
				string ObjPath{ TEXTURES_FOLDER_NAME };
				string strImageOffset{};
				string TextureFileName{};
				ObjPath += "\\";

				float ObjX = 0;
				float ObjY = 0;
				float ObjZ = 0;
				int Flipped = 0;


				tinyxml2::XMLElement* InfoElement = ObjSubElement->FirstChildElement();

				tinyxml2::XMLElement* ImgElement = ImgDocument.FirstChildElement();
				tinyxml2::XMLElement* ImgElement2 = ImgElement->FirstChildElement();

				while (InfoElement != nullptr)
				{
					const tinyxml2::XMLAttribute* Name_Attribute = InfoElement->FindAttribute("name");
					const tinyxml2::XMLAttribute* Value_Attribute = InfoElement->FindAttribute("value");

					string strName_Attribute = Name_Attribute->Value();
					string strValue_Attribute = Value_Attribute->Value();


					if (strName_Attribute == "oS")
					{
						ObjPath += strValue_Attribute;
						ObjPath += ".img";
						TextureFileName += strValue_Attribute;
						TextureFileName += ".img.";
					}
					else if (strName_Attribute == "l0" || strName_Attribute == "l1" || strName_Attribute == "l2")
					{
						TextureFileName += strValue_Attribute;
						TextureFileName += ".";

						while (ImgElement2 != nullptr)
						{
							string a = ImgElement2->FindAttribute("name")->Value();
							if (ImgElement2->FindAttribute("name")->Value() == strValue_Attribute)
							{
								ImgElement2 = ImgElement2->FirstChildElement();
								break;
							}

							ImgElement2 = ImgElement2->NextSiblingElement();
						}
					}
					else if (strName_Attribute == "x")
					{
						int _x{};
						Value_Attribute->QueryIntValue(&_x);
						ObjX = (float)_x;
					}
					else if (strName_Attribute == "y")
					{
						int _y{};
						Value_Attribute->QueryIntValue(&_y);
						ObjY = (float)_y;
					}
					else if (strName_Attribute == "z")
					{
						int _z{};
						Value_Attribute->QueryIntValue(&_z);
						ObjZ = (float)_z;
					}
					else if (strName_Attribute == "f")
					{
						Value_Attribute->QueryIntValue(&Flipped);
					}
					else if (strName_Attribute == "zM")
					{
						int zMinor{};
						Value_Attribute->QueryIntValue(&zMinor);
						ObjZ += zMinor * 0.01f;
					}

					InfoElement = InfoElement->NextSiblingElement();
				}

				TextureFileName += "0.png";

				int nOffsetX{};
				int nOffsetY{};

				if (ImgElement2)
				{
					strImageOffset = ImgElement2->FirstChildElement()->FindAttribute("value")->Value();

					string strX;
					string strY;

					auto CharIter = strImageOffset.begin();

					while (*CharIter != ',')
					{
						strX += *CharIter;
						++CharIter;
					}
					++CharIter;
					++CharIter;

					while (CharIter != strImageOffset.end())
					{
						strY += *CharIter;
						++CharIter;
					}

					nOffsetX = std::stoi(strX);
					nOffsetY = std::stoi(strY);
				}

				/* 액터 생성 */
				AObjBase* Obj = GetWorld()->SpawnActor<AObjBase>();
				URenderComponent* ObjRenderer = Obj->GetComponentByClass<URenderComponent>();
				string a = ObjPath + "\\" + TextureFileName;
				ObjRenderer->SetTextureByName(ObjPath + "\\" + TextureFileName);
				ObjRenderer->SetActorScaleByTextureSize();
				if (Flipped)
				{
					Obj->MultiplyScale(Flipped ? -1.0f : 1.0f, 1.0f, 1.0f);
					nOffsetX = (int)(nOffsetX + Obj->GetTransform().Scale.x / 2);
					nOffsetY = (int)(nOffsetY - Obj->GetTransform().Scale.y / 2);
					Obj->SetPosition({ ObjX + (float)nOffsetX, ((float)ObjY - (float)nOffsetY) * -1.0f, (float)ObjZ * -1.0f });
				}
				else
				{
					nOffsetX = (int)(nOffsetX - Obj->GetTransform().Scale.x / 2);
					nOffsetY = (int)(nOffsetY - Obj->GetTransform().Scale.y / 2);
					Obj->SetPosition({ ObjX - (float)nOffsetX, ((float)ObjY - (float)nOffsetY) * -1.0f, (float)ObjZ * -1.0f });
				}

				ObjSubElement = ObjSubElement->NextSiblingElement();
			}

		}

		MapElement = MapElement->NextSiblingElement();
	}
}
