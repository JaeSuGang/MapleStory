#include "GamePch.h"
#include "DebugSubsystem/MapleStoryDebugSubsystem.h"
#include "IMGUI/imgui.h"
#include "Engine/Engine.h"
#include "Actor/Actor.h"
#include "World/World.h"

void UMapleStoryDebugSubsystem::CustomCode()
{
	ImGuiIO& io = ImGui::GetIO();
	vector<shared_ptr<AActor>>& Actors = GEngine->GetWorld()->GetActors();

	ImGui::Begin("DebugSystem");
	ImGui::Text("Screen Size x: %f, y: %f", io.DisplaySize.x, io.DisplaySize.y);
	if (ImGui::Button("Spawn Test Actor"))
	{
		GEngine->GetWorld()->SpawnActor<AActor>();
	}
	ImGui::Text("Actors In World :");
	for (shared_ptr<AActor>& Actor : Actors)
	{
		ImGui::Text("<%s> : %p", typeid(*Actor.get()).name(), Actor.get());
	}
	ImGui::End();
}
