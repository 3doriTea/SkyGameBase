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

#include <cmath>

// DirectX
#include <d3d11.h>
#include <DirectXMath.h>

// XInput
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dInput8.lib")

#pragma comment(lib, "dxguid.lib")

// シェーダコンパイラ
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")


#define USE_FBX_SDK

#ifdef USE_FBX_SDK

// FbxSDK
#include <fbxsdk.h>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

#else

// ufbx
#include "Library/ufbx/ufbx.h"

#endif
