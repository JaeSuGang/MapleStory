#include "GamePch.h"
#include "DebugSubsystem/MapleStoryDebugSubsystem.h"
#include "IMGUI/imgui.h"
#include "Engine/Engine.h"
#include "Actor/Actor.h"
#include "World/World.h"
#include "Actors/BP_TestActor.h"

void UMapleStoryDebugSubsystem::CustomCode()
{
	ImGuiIO& io = ImGui::GetIO();
	vector<shared_ptr<AActor>>& Actors = GEngine->GetWorld()->GetActors();

	ImGui::ShowDemoWindow();

	ImGui::Begin("DebugSystem");
	ImGui::Text("Screen Size x: %f, y: %f", io.DisplaySize.x, io.DisplaySize.y);
	if (ImGui::Button("Spawn Test Actor"))
	{
		AActor* Actor = GEngine->GetWorld()->SpawnActor<BP_TestActor>();

		Actor->GetTransform().Scale = {0.3f, 0.3f, 0.3f};
		Actor->GetTransform().Position = {10000.0f, 10000.0f, 10000.0f};
	}

	ImGui::SeparatorText("Actors In World");
	for (shared_ptr<AActor>& Actor : Actors)
	{
		ImGui::Text("<%s> : %p", typeid(*Actor.get()).name(), Actor.get());
		ImGui::DragFloat("Scale.X", &Actor->GetTransform().Scale.x, 1);
		ImGui::DragFloat("Scale.Y", &Actor->GetTransform().Scale.y, 1);
		ImGui::DragFloat("Scale.Z", &Actor->GetTransform().Scale.z, 1);
		ImGui::DragFloat("Rotation.X", &Actor->GetTransform().Rotation.x, 1);
		ImGui::DragFloat("Rotation.Y", &Actor->GetTransform().Rotation.y, 1);
		ImGui::DragFloat("Rotation.Z", &Actor->GetTransform().Rotation.z, 1);
		ImGui::DragFloat("Position.X", &Actor->GetTransform().Position.x, 1);
		ImGui::DragFloat("Position.Y", &Actor->GetTransform().Position.y, 1);
		ImGui::DragFloat("Position.Z", &Actor->GetTransform().Position.z, 1);
	}
	ImGui::End();
}
