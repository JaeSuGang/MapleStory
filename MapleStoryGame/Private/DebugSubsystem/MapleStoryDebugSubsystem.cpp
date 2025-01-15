#include "GamePch.h"
#include "DebugSubsystem/MapleStoryDebugSubsystem.h"
#include "IMGUI/imgui.h"
#include "Engine/Engine.h"
#include "Actor/Actor.h"
#include "World/World.h"
#include "GameInstance/GameplaySubsystem.h"
#include "Engine/TimeSubsystem.h"
#include "RenderCore/Material.h"
#include "RenderCore/RenderSubsystem.h"
#include "RenderCore/RenderComponent.h"
#include "Attributes/AttributeComponent.h"
#include "GameplayTags/GameplayTagsManager.h"
#include "Levels/TestLevel.h"
#include "Actors/BP_OrangeMushroom.h"
#include "Actors/BP_TestSkill.h"
#include "Actors/BP_TestSkill2.h"
#include "Actors/BP_TestFloor.h"
#include "Actors/BP_TestCube.h"


void UMapleStoryDebugSubsystem::CustomCode()
{
	ImGuiIO& io = ImGui::GetIO();
	vector<shared_ptr<AActor>>& Actors = GEngine->GetWorld()->GetActors();

	float fFPS = GEngine->TimeSubsystem->GetFPS();

	ImGui::ShowDemoWindow();

	this->PlayerTab();

	ImGui::Begin("DebugSystem");
	ImGui::Text("FPS : %.2f", fFPS);
	ImGui::Text("Screen Size x: %f, y: %f", io.DisplaySize.x, io.DisplaySize.y);

	ImGui::SeparatorText("Camera");
	ImGui::Checkbox("Perspective View", &GEngine->RenderSubsystem->GetCamera().IsPerspectiveProjection);
	ImGui::Checkbox("Wireframe", &GEngine->RenderSubsystem->GetCamera().IsWireFrame);
	ImGui::DragFloat("FOV", &GEngine->RenderSubsystem->GetCamera().FOV, 1);
	ImGui::DragFloat("Rotation.X", &GEngine->RenderSubsystem->GetCamera().Transform.Rotation.x, 1);
	ImGui::DragFloat("Rotation.Y", &GEngine->RenderSubsystem->GetCamera().Transform.Rotation.y, 1);
	ImGui::DragFloat("Rotation.Z", &GEngine->RenderSubsystem->GetCamera().Transform.Rotation.z, 1);
	ImGui::DragFloat("Position.X", &GEngine->RenderSubsystem->GetCamera().Transform.Position.x, 10);
	ImGui::DragFloat("Position.Y", &GEngine->RenderSubsystem->GetCamera().Transform.Position.y, 10);
	ImGui::DragFloat("Position.Z", &GEngine->RenderSubsystem->GetCamera().Transform.Position.z, 10);

	if (ImGui::Button("Open New Level"))
	{
		GEngine->GetGameInstance()->GameplaySubsystem->OpenLevel<UTestLevel>();
	}

	ImGui::SeparatorText("Actor");
	if (ImGui::Button("Spawn Floor"))
	{
		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_TestFloor>();
		URenderComponent* RenderComponent = Actor->GetComponentByClass<URenderComponent>();
		string strMeshName = "Plane";
		string strTextureName = "Resources\\Textures\\9000404.img.stand11.0.png";
		RenderComponent->SetMeshIDByName(strMeshName);
		RenderComponent->SetTextureByName(strTextureName);
		RenderComponent->SetPixelShaderByName(DEFAULT_PIXEL_SHADER_NAME);
		RenderComponent->SetBlendMode(0);
		RenderComponent->SetActorScaleByTextureSize();
	}

	if (ImGui::Button("Spawn Mob"))
	{
		FVector3 Pos = GEngine->RenderSubsystem->GetCamera().Transform.Position;
		Pos.z = 0.0f;

		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_OrangeMushroom>();
		Actor->SetPosition(Pos);
	}

	if (ImGui::Button("Spawn Transculent Effect"))
	{
		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_TestSkill>();
	}

	if (ImGui::Button("Spawn Transculent Effect2"))
	{
		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_TestSkill2>();
	}

	if (ImGui::Button("Spawn Cube"))
	{
		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_TestCube>();

	}

	int nActorCount = (int)Actors.size();

	ImGui::Text("Actor Count : %d", nActorCount);

	if (ImGui::Button("Destroy All"))
	{
		for (shared_ptr<AActor>& Actor : Actors)
		{
			Actor->Destroy();
		}
	}
	ImGui::End();
}

void UMapleStoryDebugSubsystem::PlayerTab()
{
	UMapBase* Level = static_cast<UMapBase*>(GEngine->GetWorld()->GetLevel());

	AActor* Player = Level->GetMainActor();

	if (!Player)
		return;

	UAttributeComponent* Attributes = Player->GetComponentByClass<UAttributeComponent>();

	ImGui::Begin("Player");

	int ImguiID = 0;
	for (auto pair : Attributes->Attributes)
	{
		int TagID = pair.first;

		FGameplayTag Tag = GEngine->GetGameInstance()->GameplayTagsManager->FindRegisteredTagByID(TagID);

		ImguiID++;

		ImGui::PushID(ImguiID);
		ImGui::TextUnformatted(Tag.TagName.c_str());
		ImGui::PopID();
	}

	ImGui::End();
}
