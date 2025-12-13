#pragma once
#include <cstdint>

namespace wtgb
{
	/// <summary>
	/// モデルに貼り付けるテクスチャハンドル
	/// </summary>
	using TextureHandle = uint32_t;
	/// <summary>
	/// ゲームを描画するウィンドウのハンドル
	/// </summary>
	using GameWindowHandle = uint32_t;
	/// <summary>
	/// 読み込んだシェーダのハンドル
	/// </summary>
	using ShaderHandle = uint32_t;
	/// <summary>
	/// 読み込んだモデルのハンドル
	/// </summary>
	using ModelHandle = uint32_t;
	/// <summary>
	/// 読み込んだ音声ハンドル
	/// </summary>
	using AudioHandle = uint32_t;
}
