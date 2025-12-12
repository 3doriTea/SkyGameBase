#include "pch\pch.h"
#include "ImGuiSystem.h"
#include "GameWindow.h"
#include "Direct3D.h"

wtgb::ImGuiSystem::ImGuiSystem() :
	firstFrame_{ true }
{
}

wtgb::ImGuiSystem::~ImGuiSystem()
{
}

wtgb::Result wtgb::ImGuiSystem::Init(const ViewerInit& _system)
{
	GameWindow& gameWindow{ _system.Get<GameWindow>() };
	Direct3D::ResourceAccessor& direct3DResource{ _system.Get<Direct3D>().Resource() };

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };
	(void)io;  // ç≈ìKâªÇ≈è¡Ç≥ÇÍÇÈÇÃÇñhé~
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsLight();

	ImGuiStyle& style{ ImGui::GetStyle() };
	//style.ScaleAllSizes();
	//style.FontScaleDpi();

	ImGui_ImplWin32_Init(gameWindow.GetMainWindowHandle());
	ImGui_ImplDX11_Init(direct3DResource.Device(), direct3DResource.Context());

	return Result::Code::Ok;
}

void wtgb::ImGuiSystem::Update(const ViewerUpdate& _system)
{
	if (firstFrame_ == false)
	{
		ImGui::Render();
	}
	else
	{
		firstFrame_ = false;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void wtgb::ImGuiSystem::End()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
