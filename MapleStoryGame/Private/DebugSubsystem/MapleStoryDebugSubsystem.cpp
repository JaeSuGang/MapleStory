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
#include "Actors/Monsters/BP_Cleaner.h"
#include "Actors/BP_TestSkill.h"
#include "Actors/BP_TestSkill2.h"
#include "Actors/BP_TestCube.h"


UMapleStoryDebugSubsystem::UMapleStoryDebugSubsystem()
{
}

void UMapleStoryDebugSubsystem::CustomCode()
{
	ImGui::ShowDemoWindow();

	this->MainDebugTab();

	this->PlayerTab();
}

void UMapleStoryDebugSubsystem::CustomInit()
{
	this->SetupUnrealStyleImGui();
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
	for (auto pair : Attributes->Attributes.Tags)
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

void UMapleStoryDebugSubsystem::SetupUnrealStyleImGui()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(8, 8);
	style.FramePadding = ImVec2(5, 3);
	style.ItemSpacing = ImVec2(5, 5);
	style.GrabMinSize = 10.0f;
	style.FrameRounding = 2.0f; 

	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

	style.Colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

	style.Colors[ImGuiCol_Header] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);

	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 0.40f, 0.40f, 1.00f);
}

void UMapleStoryDebugSubsystem::MainDebugTab()
{
	ImGuiIO& io = ImGui::GetIO();
	vector<shared_ptr<AActor>>& Actors = GEngine->GetWorld()->GetActors();

	ImGui::Begin("DebugSystem");

	ImGui::Text("FPS : %.0f", this->FPS);
	ImGui::Text("Screen Size x: %.0f, y: %.0f", io.DisplaySize.x, io.DisplaySize.y);

	ImGui::SeparatorText("Camera");
	ImGui::Checkbox("Perspective View", &GEngine->RenderSubsystem->GetCamera().IsPerspectiveProjection);
	ImGui::Checkbox("Wireframe", &GEngine->RenderSubsystem->GetCamera().IsWireFrame);
	ImGui::InputInt("Debug Layer", &GEngine->RenderSubsystem->GetCamera().DebugLayerLevel, 1);
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

	if (ImGui::Button("Spawn Mob"))
	{
		FVector3 Pos = GEngine->RenderSubsystem->GetCamera().Transform.Position;
		Pos.z = 0.0f;

		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_Cleaner>();
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
