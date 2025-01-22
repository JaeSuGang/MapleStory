#include "GamePch.h"
#include "Levels/MapBase.h"
#include "TinyXML2/tinyxml2.h"
#include "Engine/Engine.h"
#include "World/World.h"
#include "Actors/ObjBase.h"
#include "Actors/FootholdBase.h"
#include "RenderCore/RenderComponent.h"
#include "RenderCore/RenderSubsystem.h"
#include "PhysicsCore/PhysicsComponent.h"
#include "Actors/NPCs/NPCBase.h"



UMapBase::UMapBase()
{

}

void UMapBase::BeginPlay()
{

}

void UMapBase::Tick(float fDeltaTime)
{

}

AActor* UMapBase::GetMainActor() const
{
	return MainActor.lock().get();
}

void UMapBase::LoadXMLToMap(string strMapPath, string strImgName)
{
	tinyxml2::XMLDocument MapDocument;
	tinyxml2::XMLDocument ObjImgDocument;
	tinyxml2::XMLDocument BackImgDocument;
	tinyxml2::XMLError Error;
	Error = MapDocument.LoadFile(strMapPath.data());
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

#pragma region Obj인경우
		if (!Error)
		{
			int SortingLayer = nNumberAttribute;

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


			bool bEscapeLoopInstantly = false;
			while (ObjSubElement != nullptr)
			{
				if (bEscapeLoopInstantly)
				{
					ObjSubElement = ObjSubElement->NextSiblingElement();
					continue;
				}


				string ObjPath{ TEXTURES_FOLDER_NAME };
				ObjPath += "\\Maps";
				string strImageOffset{};
				string TextureFileName{};
				ObjPath += "\\";

				float ObjX = 0.0f;
				float ObjY = 0.0f;
				int zValue = 0;
				int zIndex = 0;
				int Flipped = 0;
				AObjBase::EObjType ObjType = AObjBase::EObjType::Obj;

				ObjSubElement->FindAttribute("name")->QueryIntValue(&zIndex);

				tinyxml2::XMLElement* InfoElement = ObjSubElement->FirstChildElement();

				tinyxml2::XMLElement* ImgElement{};
				tinyxml2::XMLElement* ImgElement2{};

				while (InfoElement != nullptr)
				{
					const tinyxml2::XMLAttribute* Name_Attribute = InfoElement->FindAttribute("name");
					const tinyxml2::XMLAttribute* Value_Attribute = InfoElement->FindAttribute("value");

					string strName_Attribute = Name_Attribute->Value();
					string strValue_Attribute = Value_Attribute->Value();


					if (strName_Attribute == "oS")
					{
						Error = ObjImgDocument.LoadFile(("Resources\\XMLs\\Map.Obj." + strValue_Attribute + ".img.xml").data());
						if (Error)
						{
							bEscapeLoopInstantly = true;
							GEngine->DebugLog("XML 로드 실패", 0);
							break;
						}

						ImgElement = ObjImgDocument.FirstChildElement();
						ImgElement2 = ImgElement->FirstChildElement();

						ObjPath += strValue_Attribute;
						ObjPath += ".img";
						TextureFileName += strValue_Attribute;
						TextureFileName += ".img.";
					}
					else if (strName_Attribute == "l0" || strName_Attribute == "l1" || strName_Attribute == "l2")
					{
						if (strValue_Attribute == "foothold")
						{
							ObjType = AObjBase::EObjType::Foothold;
						}

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
						Value_Attribute->QueryIntValue(&zValue);
					}
					else if (strName_Attribute == "f")
					{
						Value_Attribute->QueryIntValue(&Flipped);
					}

					InfoElement = InfoElement->NextSiblingElement();
				}

				TextureFileName += "0.png";

				int nOffsetX{};
				int nOffsetY{};

				if (ImgElement2)
				{
					if (ImgElement2->FirstChildElement() == nullptr)
					{
						ObjSubElement = ObjSubElement->NextSiblingElement();
						continue;
					}

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
				Obj->SetObjType(ObjType);
				URenderComponent* ObjRenderer = Obj->GetComponentByClass<URenderComponent>();
				string a = ObjPath + "\\" + TextureFileName;
				ObjRenderer->SetTextureByName(ObjPath + "\\" + TextureFileName);
				ObjRenderer->SetActorScaleByTextureSize();
				FVector3 FinalPos{};
				if (Flipped)
				{
					Obj->MultiplyScale(Flipped ? -1.0f : 1.0f, 1.0f, 1.0f);
					nOffsetX = (int)(nOffsetX + std::round(Obj->GetTransform().Scale.x / 2));
					nOffsetY = (int)(nOffsetY - std::round(Obj->GetTransform().Scale.y / 2));
					FinalPos = { ObjX + (float)nOffsetX, ((float)ObjY - (float)nOffsetY) * -1.0f, 0.0f };
				}
				else
				{
					nOffsetX = (int)(nOffsetX - std::round(Obj->GetTransform().Scale.x / 2));
					nOffsetY = (int)(nOffsetY - std::round(Obj->GetTransform().Scale.y / 2));
					FinalPos = { ObjX - (float)nOffsetX, ((float)ObjY - (float)nOffsetY) * -1.0f, 0.0f };
				}

				ObjRenderer->SetSortingLayer(SortingLayer);
				ObjRenderer->SetZValue(zValue);
				ObjRenderer->SetZIndex(zIndex);

				Obj->SetPosition(FinalPos);

				ObjSubElement = ObjSubElement->NextSiblingElement();
			}

		}

#pragma endregion

		else
		{
			string strNodeName = MapElement_Attribute->Value();
#pragma region Foothold인 경우
			if (strNodeName == "foothold")
			{
				tinyxml2::XMLElement* FirstLoopElement = MapElement->FirstChildElement();

				while (FirstLoopElement != nullptr)
				{
					tinyxml2::XMLElement* SecondLoopElement = FirstLoopElement->FirstChildElement();
					while (SecondLoopElement != nullptr)
					{
						tinyxml2::XMLElement* ThirdLoopElement = SecondLoopElement->FirstChildElement();
						while (ThirdLoopElement != nullptr)
						{
							int x1{};
							int x2{};
							int y1{};
							int y2{};

							tinyxml2::XMLElement* FootholdInfoElement = ThirdLoopElement->FirstChildElement();
							while (FootholdInfoElement != nullptr)
							{
								const tinyxml2::XMLAttribute* NameAttribute = FootholdInfoElement->FindAttribute("name");
								const tinyxml2::XMLAttribute* ValueAttribute = FootholdInfoElement->FindAttribute("value");
								string strNameAttribute = NameAttribute->Value();
								int nValueAttribute = ValueAttribute->IntValue();

								if (strNameAttribute == "x1")
									x1 = nValueAttribute;

								else if (strNameAttribute == "x2")
									x2 = nValueAttribute;

								else if (strNameAttribute == "y1")
									y1 = nValueAttribute;

								else if (strNameAttribute == "y2")
									y2 = nValueAttribute;

								FootholdInfoElement = FootholdInfoElement->NextSiblingElement();
							}

							/* 액터 생성 */
							AFootholdBase* FootholdActor = GetWorld()->SpawnActor<AFootholdBase>();
							FootholdActor->InitializeValues((float)x1, (float)-y1, (float)x2, (float)-y2);

							ThirdLoopElement = ThirdLoopElement->NextSiblingElement();
						}
						SecondLoopElement = SecondLoopElement->NextSiblingElement();
					}
					FirstLoopElement = FirstLoopElement->NextSiblingElement();
				}
			}
#pragma endregion

#pragma region Back인 경우
			else if (strNodeName == "back")
			{
				tinyxml2::XMLElement* BackElement = MapElement->FirstChildElement();

				while (BackElement != nullptr)
				{
					tinyxml2::XMLElement* BackSubElement = BackElement->FirstChildElement();
					
					string strTexturePath = { TEXTURES_FOLDER_NAME };
					strTexturePath += "\\Maps\\";

					int nTileMode = TileMode::None;

					bool bIsAni = false;
					int nFlipped = 0;
					int nZIndex = BackElement->FindAttribute("name")->IntValue();
					float ObjX = 0.0f;
					float ObjY = 0.0f;
					float rx = 0.0f;
					float ry = 0.0f;
					float cx = 0.0f;
					float cy = 0.0f;
					int nOffsetX = 0;
					int nOffsetY = 0;
					FVector3 FinalPos{};

					while (BackSubElement != nullptr)
					{
						string strPropertyName = BackSubElement->FindAttribute("name")->Value();
						string strPropertyValue = BackSubElement->FindAttribute("value")->Value();

						if (strPropertyName == "bS")
						{
							Error = BackImgDocument.LoadFile(("Resources\\XMLs\\Map.Back." + strPropertyValue + ".img.xml").data());
							if (Error)
								GEngine->DebugLog("XML 로드 실패", 2);

							strTexturePath += strPropertyValue;
							strTexturePath += ".img\\";
							strTexturePath += strPropertyValue;
							strTexturePath += ".img.back.";
						}

						else if (strPropertyName == "no")
						{

							strTexturePath += strPropertyValue;
							strTexturePath += ".png";

							tinyxml2::XMLElement* ImgCategoryElement = BackImgDocument.FirstChildElement()->FirstChildElement();

							while (ImgCategoryElement != nullptr)
							{
								string strImgCategory = ImgCategoryElement->FindAttribute("name")->Value();

								if (strImgCategory == "back")
								{
									tinyxml2::XMLElement* BackImgElement = ImgCategoryElement->FirstChildElement();


									while (BackImgElement != nullptr)
									{
										int nBackImgIndex = BackImgElement->FindAttribute("name")->IntValue();
										if (nBackImgIndex == std::stoi(strPropertyValue))
										{
											break;
										}

										BackImgElement = BackImgElement->NextSiblingElement();
									}

									string strWzVector = BackImgElement->FirstChildElement()->FindAttribute("value")->Value();

									string strX;
									string strY;

									auto CharIter = strWzVector.begin();

									while (*CharIter != ',')
									{
										strX += *CharIter;
										++CharIter;
									}
									++CharIter;
									++CharIter;

									while (CharIter != strWzVector.end())
									{
										strY += *CharIter;
										++CharIter;
									}

									nOffsetX = std::stoi(strX);
									nOffsetY = std::stoi(strY);
								}

								ImgCategoryElement = ImgCategoryElement->NextSiblingElement();
							}
						}

						else if (strPropertyName == "f")
						{
							BackSubElement->FindAttribute("value")->QueryIntValue(&nFlipped);
						}

						else if (strPropertyName == "x")
						{
							int _x{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_x);
							ObjX = (float)_x;
						}

						else if (strPropertyName == "y")
						{
							int _y{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_y);
							ObjY = (float)_y;
						}

						else if (strPropertyName == "rx")
						{
							int _rx{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_rx);
							rx = (float)_rx;
						}

						else if (strPropertyName == "ry")
						{
							int _ry{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_ry);
							ry = (float)_ry;
						}

						else if (strPropertyName == "cx")
						{
							int _cx{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_cx);
							cx = (float)_cx;
						}

						else if (strPropertyName == "cy")
						{
							int _cy{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_cy);
							cy = (float)_cy;
						}

						else if (strPropertyName == "ani")
						{
							int _bool{};
							BackSubElement->FindAttribute("value")->QueryIntValue(&_bool);
							if (_bool != 0)
								bIsAni = true;
						}

						else if (strPropertyName == "type")
						{
							BackSubElement->FindAttribute("value")->QueryIntValue(&nTileMode);
						}

						BackSubElement = BackSubElement->NextSiblingElement();
					}

					if (bIsAni)
					{
						BackElement = BackElement->NextSiblingElement();
						continue;
					}


					if (nTileMode == TileMode::None)
					{
						AObjBase* BackObj = GetWorld()->SpawnActor<AObjBase>();
						URenderComponent* RenderComponent = BackObj->GetComponentByClass<URenderComponent>();

						RenderComponent->SetTextureByName(strTexturePath);
						RenderComponent->SetActorScaleByTextureSize();
						RenderComponent->SetSortingLayer(0);

						int nOffsetX2{};
						int nOffsetY2{};

						if (nFlipped)
						{
							BackObj->MultiplyScale(nFlipped ? -1.0f : 1.0f, 1.0f, 1.0f);
							nOffsetX2 = (int)(nOffsetX + (BackObj->GetTransform().Scale.x / 2));
							nOffsetY2 = (int)(nOffsetY - (BackObj->GetTransform().Scale.y / 2));
							FinalPos = { ObjX + (float)nOffsetX2, ((float)ObjY - (float)nOffsetY2) * -1.0f, 0.0f };
						}
						else
						{
							nOffsetX2 = (int)(nOffsetX - (BackObj->GetTransform().Scale.x / 2));
							nOffsetY2 = (int)(nOffsetY - (BackObj->GetTransform().Scale.y / 2));
							FinalPos = { ObjX - (float)nOffsetX2, ((float)ObjY - (float)nOffsetY2) * -1.0f, 0.0f };
						}

						BackObj->SetObjType(AObjBase::EObjType::Back);
						BackObj->OriginalX = FinalPos.x;
						BackObj->OriginalY = FinalPos.y;
						BackObj->rx = rx;
						BackObj->ry = ry;
					}

					else
					{

						int nRepeatWidth = 1;
						int nRepeatHeight = 1;

						if (nTileMode & TileMode::Horizontal || nTileMode & TileMode::ScrollHorizontal)
						{
							nRepeatWidth = (int)(GEngine->RenderSubsystem->GetCamera().Width * 8.0f);

							if (rx == 0.0f)
							{
								nRepeatWidth /= 4;
							}
						}

						if (nTileMode & TileMode::Vertical || nTileMode & TileMode::ScrollVertical)
						{
							nRepeatHeight = (int)GEngine->RenderSubsystem->GetCamera().Height * 4;

							if (ry == 0.0f)
							{
								nRepeatHeight /= 2;
							}
						}

						int nCameraLeft = (int)(-nRepeatWidth / 2.0f);
						int nCameraRight = (int)(nRepeatWidth / 2.0f);
						int nCameraTop = (int)(nRepeatHeight / 2.0f);
						int nCameraBottom = (int)(-nRepeatHeight / 2.0f);

						int nWidthTileCount = 1;
						int nHeightTileCount = 1;

						AObjBase* BackObj = GetWorld()->SpawnActor<AObjBase>();

						if (nTileMode == TileMode::ScrollHorizontal)
							BackObj->SetObjType(AObjBase::EObjType::BackScrollHorizontal);
						else
							BackObj->SetObjType(AObjBase::EObjType::Back);

						URenderComponent* RenderComponent = BackObj->GetComponentByClass<URenderComponent>();
						RenderComponent->SetPixelShaderByName(TILE_PIXEL_SHADER_NAME);
						RenderComponent->SetTextureByName(strTexturePath);
						RenderComponent->SetActorScaleByTextureSize();
						RenderComponent->SetSortingLayer(0);
						cx = cx ? cx : BackObj->Transform.Scale.x;
						cy = cy ? cy : BackObj->Transform.Scale.y;
						BackObj->cx = cx;
						BackObj->cy = cy;

						int nOffsetX2{};
						int nOffsetY2{};

						if (nFlipped)
						{
							BackObj->MultiplyScale(nFlipped ? -1.0f : 1.0f, 1.0f, 1.0f);
							nOffsetX2 = (int)(nOffsetX + (BackObj->GetTransform().Scale.x / 2));
							nOffsetY2 = (int)(nOffsetY - (BackObj->GetTransform().Scale.y / 2));
						}
						else
						{
							nOffsetX2 = (int)(nOffsetX - (BackObj->GetTransform().Scale.x / 2));
							nOffsetY2 = (int)(nOffsetY - (BackObj->GetTransform().Scale.y / 2));
						}

						if ((nTileMode & TileMode::Horizontal || nTileMode & TileMode::ScrollHorizontal))
						{
							nWidthTileCount = nRepeatWidth / (int)cx;
							BackObj->Transform.Scale.x = (float)nRepeatWidth;
						}
						if ((nTileMode & TileMode::Vertical || nTileMode & TileMode::ScrollVertical))
						{
							nHeightTileCount = nRepeatWidth / (int)cy;
							BackObj->Transform.Scale.y = (float)nRepeatHeight;
						}

						if (nWidthTileCount > 1)
							BackObj->Transform.Scale.x = cx * nWidthTileCount;

						if (nHeightTileCount > 1)
							BackObj->Transform.Scale.y = cy * nHeightTileCount;

						RenderComponent->SetWidthTileLength((int)cx); 
						RenderComponent->SetHeightTileLength((int)cy);
						RenderComponent->SetBlendMode(0);

						FinalPos = { ObjX , ObjY * -1.0f, 0.0f };
						BackObj->Transform.Position.x = FinalPos.x;
						BackObj->Transform.Position.y = FinalPos.y;
						BackObj->Transform.Position.z = 1.0f;
						BackObj->OriginalX = FinalPos.x;
						BackObj->OriginalY = FinalPos.y;
						BackObj->rx = rx;
						BackObj->ry = ry;
						BackObj->OffsetX = (float)nOffsetX2;
						BackObj->OffsetY = (float)nOffsetY2;
					}

					BackElement = BackElement->NextSiblingElement();
				}
			}
#pragma endregion

#pragma region info인 경우
			else if (strNodeName == "info")
			{
				tinyxml2::XMLElement* InfoElement = MapElement->FirstChildElement();

				while (InfoElement != nullptr)
				{
					string strPropertyName = InfoElement->FindAttribute("name")->Value();
					string strPropertyValue = InfoElement->FindAttribute("value")->Value();

					if (strPropertyName == "VRTop")
						this->VRTopInverted = -1.0f * (float)InfoElement->FindAttribute("value")->IntValue();

					else if (strPropertyName == "VRLeft")
						this->VRLeft = (float)InfoElement->FindAttribute("value")->IntValue();

					else if (strPropertyName == "VRBottom")
						this->VRBottomInverted = -1.0f * (float)InfoElement->FindAttribute("value")->IntValue();

					else if (strPropertyName == "VRRight")
						this->VRRight = (float)InfoElement->FindAttribute("value")->IntValue();

					InfoElement = InfoElement->NextSiblingElement();
				}
			}
#pragma endregion

#pragma region life인 경우
			else if (strNodeName == "life")
			{
				tinyxml2::XMLElement* LifeIndexElement = MapElement->FirstChildElement();

				while (LifeIndexElement != nullptr)
				{
					tinyxml2::XMLElement* LifeInfoElement = LifeIndexElement->FirstChildElement();

					string strLifeType{};
					string strLifeID{};

					float fLifePosX = 0.0f;
					float fLifePosY = 0.0f;
					int nOffsetX = 0;
					int nOffsetY = 0;
					int nFlipped = 0;
					float cy = 0.0f;
					FVector3 FinalPos{};

					while (LifeInfoElement != nullptr)
					{
						string strPropertyName = LifeInfoElement->FindAttribute("name")->Value();
						string strPropertyValue = LifeInfoElement->FindAttribute("value")->Value();

						if (strPropertyName == "type")
							strLifeType = strPropertyValue;

						if (strPropertyName == "id")
							strLifeID = strPropertyValue;

						if (strPropertyName == "x")
							fLifePosX = (float)LifeInfoElement->FindAttribute("value")->IntValue();

						if (strPropertyName == "y")
							fLifePosY = (float)LifeInfoElement->FindAttribute("value")->IntValue();

						if (strPropertyName == "f")
							nFlipped = LifeInfoElement->FindAttribute("value")->IntValue();

						LifeInfoElement = LifeInfoElement->NextSiblingElement();
					}

					/* 처리 시작 */
					if (strLifeType == "n")
					{
						string strImagePath = { RESOURCES_FOLDER_NAME };
						strImagePath += "\\Textures\\Npcs\\" + strLifeID + ".img";
						strImagePath += "\\" + strLifeID + ".img.stand.0.png";

						tinyxml2::XMLDocument NpcDocument;
						Error = NpcDocument.LoadFile(("Resources\\XMLs\\Npc." + strLifeID + ".img.xml").data());
						if (Error)
						{
							LifeIndexElement = LifeIndexElement->NextSiblingElement();
							continue;
						}

						tinyxml2::XMLElement* NpcStatusElement = NpcDocument.FirstChildElement()->FirstChildElement();
						while (NpcStatusElement != nullptr)
						{
							string strPropertyName = NpcStatusElement->FindAttribute("name")->Value();

							if (strPropertyName == "stand")
							{
								string strWzVector = NpcStatusElement->FirstChildElement()->FirstChildElement()->FindAttribute("value")->Value();

								string strX;
								string strY;

								auto CharIter = strWzVector.begin();

								while (*CharIter != ',')
								{
									strX += *CharIter;
									++CharIter;
								}
								++CharIter;
								++CharIter;

								while (CharIter != strWzVector.end())
								{
									strY += *CharIter;
									++CharIter;
								}

								nOffsetX = std::stoi(strX);
								nOffsetY = std::stoi(strY);
							}

							NpcStatusElement = NpcStatusElement->NextSiblingElement();
						}

						ANPCBase* NPC = GetWorld()->SpawnActor<ANPCBase>();

						URenderComponent* RenderComponent = NPC->GetComponentByClass<URenderComponent>();
						RenderComponent->SetTextureByName(strImagePath);
						RenderComponent->SetActorScaleByTextureSize();

						int nOffsetX2{};
						int nOffsetY2{};

						if (nFlipped)
						{
							NPC->MultiplyScale(nFlipped ? -1.0f : 1.0f, 1.0f, 1.0f);
							nOffsetX2 = (int)(nOffsetX + NPC->GetTransform().Scale.x / 2);
							nOffsetY2 = (int)(nOffsetY - NPC->GetTransform().Scale.y / 2);
							FinalPos = { fLifePosX + (float)nOffsetX2, ((float)fLifePosY - (float)nOffsetY2) * -1.0f, 0.0f };
						}
						else
						{
							nOffsetX2 = (int)(nOffsetX - NPC->GetTransform().Scale.x / 2);
							nOffsetY2 = (int)(nOffsetY - NPC->GetTransform().Scale.y / 2);
							FinalPos = { fLifePosX - (float)nOffsetX2, ((float)fLifePosY - (float)nOffsetY2) * -1.0f, 0.0f };
						}

						FTransform& NPCTransform = NPC->GetTransform();
						NPCTransform.Position = FinalPos;

						NPC->InitPhysics();
					}

					LifeIndexElement = LifeIndexElement->NextSiblingElement();
				}
			}
#pragma endregion



		}




		MapElement = MapElement->NextSiblingElement();
	}
}

