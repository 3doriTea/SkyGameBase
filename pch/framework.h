#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>
// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// DirectX
#include <d3d11.h>
#include <DirectXMath.h>

// DXGI
#include <dxgi1_2.h>
#pragma comment(lib, "dxgi.lib")

// XInput
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dInput8.lib")

#pragma comment(lib, "dxguid.lib")
