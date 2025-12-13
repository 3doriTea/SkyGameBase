#include "pch\pch.h"
#include "ImGuiSystem.h"
#include "GameWindow.h"
#include "Direct3D.h"
#include "WTGBAssert.h"

// ImGui‚ÌWinProc—pƒCƒxƒ“ƒg
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

wtgb::ImGuiSystem::ImGuiSystem()
{
}

wtgb::ImGuiSystem::~ImGuiSystem()
{
}

wtgb::Result wtgb::ImGuiSystem::Init(const ViewerInit& _system)
{
	GameWindow& gameWindow{ _system.Get<GameWindow>() };
	Direct3D& direct3D{ _system.Get<Direct3D>() };
	//Direct3D::ResourceAccessor& direct3DResource{ direct3D.Resource() };

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsLight();

	ImGuiStyle& style{ ImGui::GetStyle() };
	//style.ScaleAllSizes();
	//style.FontScaleDpi();

	bool succeed{ false };

	succeed = ImGui_ImplWin32_Init(gameWindow.GetMainWindowHandle());
	wassert(succeed && "ImGui Win32‰Šú‰»‚ÉŽ¸”s");

	ID3D11Device* pDevice{ direct3D.Resource().DeviceComPtr().Get() };
	ID3D11DeviceContext* pContext{ direct3D.Resource().ContextComPtr().Get() };

	pDevice->CreateBuffer(nullptr, nullptr, nullptr);

	succeed = ImGui_ImplDX11_Init(pDevice, pContext);
	wassert(succeed && "ImGui DX11‰Šú‰»‚ÉŽ¸”s");

	// winproc‚É‚à“o˜^‚·‚é
	gameWindow.AddWinProcListener(
		[](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
		{
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		});

	direct3D.AddRenderListener(
		[this]()
		{
			Render();
		});

	return Result::Code::Ok;
}

void wtgb::ImGuiSystem::Update(const ViewerUpdate& _system)
{
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

void wtgb::ImGuiSystem::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
