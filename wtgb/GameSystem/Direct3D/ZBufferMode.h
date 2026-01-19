#pragma once

namespace wtgb
{
	/// <summary>
	/// ブレンドの種類
	/// </summary>
	enum struct ZBufferMode
	{
		None,  // 特になし
		Back,  // 最背面に描画する
		Max,   // 最大数
	};

	/// <summary>
	/// ブレンドモードの総数
	/// </summary>
	static constexpr size_t ZBUFFER_MODE_MAX{ static_cast<size_t>(ZBufferMode::Max) };
}
