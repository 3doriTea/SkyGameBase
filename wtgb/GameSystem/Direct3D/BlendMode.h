#pragma once

namespace wtgb
{
	/// <summary>
	/// ブレンドの種類
	/// </summary>
	enum struct BlendMode
	{
		None,   // ブレンドモード特になし
		Alpha,  // 半透明描画する
		Max,    // 最大数
	};
	/// <summary>
	/// ブレンドモードの総数
	/// </summary>
	static constexpr size_t BLEND_MODE_MAX{ static_cast<size_t>(BlendMode::Max) };
}
