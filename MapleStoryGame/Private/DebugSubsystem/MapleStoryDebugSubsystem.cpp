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

	ImGui::Begin("DebugSystem");
	ImGui::Text("FPS : %.2f", fFPS);
	ImGui::Text("Screen Size x: %f, y: %f", io.DisplaySize.x, io.DisplaySize.y);

	ImGui::SeparatorText("Camera");
	ImGui::Checkbox("Perspective View", &GEngine->RenderSubsystem->GetCamera().IsPerspectiveProjection);
	ImGui::Checkbox("Wireframe", &GEngine->RenderSubsystem->GetCamera().IsWireFrame);
	ImGui::DragFloat("FOV", &GEngine->RenderSubsystem->GetCamera().FOV, 1);
	ImGui::DragFloat("Position.X", &GEngine->RenderSubsystem->GetCamera().Transform.Position.x, 1);
	ImGui::DragFloat("Position.Y", &GEngine->RenderSubsystem->GetCamera().Transform.Position.y, 1);
	ImGui::DragFloat("Position.Z", &GEngine->RenderSubsystem->GetCamera().Transform.Position.z, 1);

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
		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_OrangeMushroom>();

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
	int n = 0;
	for (shared_ptr<AActor>& Actor : Actors)
	{
		ImGui::PushID(n++);
		ImGui::Text("<%s> : %p", typeid(*Actor.get()).name(), Actor.get());
		if (ImGui::Button("Destroy"))
		{
			Actor->Destroy();
		}
		ImGui::DragFloat("Scale.X", &Actor->GetTransform().Scale.x, 1);
		ImGui::DragFloat("Scale.Y", &Actor->GetTransform().Scale.y, 1);
		ImGui::DragFloat("Scale.Z", &Actor->GetTransform().Scale.z, 1);
		ImGui::DragFloat("Rotation.X", &Actor->GetTransform().Rotation.x, 1);
		ImGui::DragFloat("Rotation.Y", &Actor->GetTransform().Rotation.y, 1);
		ImGui::DragFloat("Rotation.Z", &Actor->GetTransform().Rotation.z, 1);
		ImGui::DragFloat("Position.X", &Actor->GetTransform().Position.x, 1);
		ImGui::DragFloat("Position.Y", &Actor->GetTransform().Position.y, 1);
		ImGui::DragFloat("Position.Z", &Actor->GetTransform().Position.z, 1);
		ImGui::PopID();
	}
	ImGui::End();
}
