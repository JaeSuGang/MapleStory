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

void UMapBase::LoadXMLToMap(string strPath)
{
	tinyxml2::XMLDocument Document;
	tinyxml2::XMLError Error;
	Error = Document.LoadFile(strPath.data());

	if (Error)
		GEngine->DebugLog("XML 로드 실패", 2);
	
	tinyxml2::XMLElement* RootElement = Document.FirstChildElement();

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
				string TextureFileName{};
				ObjPath += "\\";

				int ObjX = 0;
				int ObjY = 0;
				int ObjZ = 0;
				int Flipped = 0;

				tinyxml2::XMLElement* InfoElement = ObjSubElement->FirstChildElement();
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
					}
					else if (strName_Attribute == "x")
					{
						Value_Attribute->QueryIntValue(&ObjX);
					}
					else if (strName_Attribute == "y")
					{
						Value_Attribute->QueryIntValue(&ObjY);
					}
					else if (strName_Attribute == "z")
					{
						Value_Attribute->QueryIntValue(&ObjZ);
					}
					else if (strName_Attribute == "f")
					{
						Value_Attribute->QueryIntValue(&Flipped);
					}

					InfoElement = InfoElement->NextSiblingElement();
				}

				TextureFileName += "0.png";

				/* 액터 생성 */
				AObjBase* Obj = GetWorld()->SpawnActor<AObjBase>();
				URenderComponent* ObjRenderer = Obj->GetComponentByClass<URenderComponent>();
				string a = ObjPath + "\\" + TextureFileName;
				ObjRenderer->SetTextureByName(ObjPath + "\\" + TextureFileName);
				ObjRenderer->SetActorScaleByTextureSize();
				Obj->SetPosition({ (float)ObjX , (float)ObjY * -1.0f, (float)ObjZ * -1.0f });
				Obj->MultiplyScale(Flipped ? -1.0f : 1.0f, 1.0f, 1.0f);

				ObjSubElement = ObjSubElement->NextSiblingElement();
			}

		}

		MapElement = MapElement->NextSiblingElement();
	}
}
