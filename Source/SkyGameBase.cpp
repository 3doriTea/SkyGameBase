// SkyGameBase.cpp : アプリケーションのエントリ ポイントを定義します。
#include "pch/pch.h"
#include "pch/framework.h"
#include "SkyGameBase.h"
#include "SampleSkyCombat.h"

#include "SampleGame.h"

int APIENTRY wWinMain(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPWSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	return wtgb::Game::Run<SampleGame>();
}
