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

// XAudio2
#include <xaudio2.h>

// XInput
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment(lib, "dInput8.lib")

#pragma comment(lib, "dxguid.lib")

// ImGui
#define IMGUI_DEFINE_MATH_OPERATORS
#include "Library/ImGui/imgui.h"
#include "Library/ImGui/imgui_impl_win32.h"
#include "Library/ImGui/imgui_impl_dx11.h"

// mtbin
#include "Library/mtbin/BinaryReader.h"
#include "Library/mtbin/BinaryWriter.h"
#include "Library/mtbin/MemoryStream.h"
#include "Library/mtbin/Util.h"

// シェーダコンパイラ
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

// DirectXTex
#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

// json
#include "LibHeader/NlohmannJson.h"

#define USE_FBX_SDK

#ifdef USE_FBX_SDK

// FbxSDK

#pragma warning(disable:26812)  // enum class関連
#pragma warning(disable:26495)  // メンバ初期化
#pragma warning(disable:26451)  // 演算オーバーフロー
#include <fbxsdk.h>
#pragma warning(default:26812)
#pragma warning(default:26451)
#pragma warning(default:26495)

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

#else

// ufbx
//#include "Library/ufbx/ufbx.h"

#endif
