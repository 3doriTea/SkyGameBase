#include "pch\pch.h"
#include "ImGuiSystem.h"
#include "GameWindow.h"
#include "Direct3D.h"
#include "WTGBAssert.h"

// ImGui‚ÌWinProc—pƒCƒxƒ“ƒg
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
	(void)io;  // Å“K‰»‚ÅÁ‚³‚ê‚é‚Ì‚ð–hŽ~
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsLight();

	ImGuiStyle& style{ ImGui::GetStyle() };
	//style.ScaleAllSizes();
	//style.FontScaleDpi();

	bool succeed{ false };

	succeed = ImGui_ImplWin32_Init(gameWindow.GetMainWindowHandle());
	wassert(succeed && "ImGui Win32‰Šú‰»‚ÉŽ¸”s");

	succeed = ImGui_ImplDX11_Init(direct3DResource.Device(), direct3DResource.Context());
	wassert(succeed && "ImGui DX11‰Šú‰»‚ÉŽ¸”s");

	// winproc‚É‚à“o˜^‚·‚é
	gameWindow.AddWinProcListener(
		[](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
		{
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		});

	return Result::Code::Ok;
}

void wtgb::ImGuiSystem::Update(const ViewerUpdate& _system)
{
	if (firstFrame_ == false)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
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
