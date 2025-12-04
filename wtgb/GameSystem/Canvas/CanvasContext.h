#pragma once
#include "Utility/Accessor.h"
#include "CoreType/Handler.h"

namespace wtgb
{
	class Canvas;

	/// <summary>
	/// UI描画へのアクセス
	/// </summary>
	class CanvasContext : public Accessor<Canvas>
	{
	public:
		using Accessor<Canvas>::Accessor;
		~CanvasContext() {}

		/// <summary>
		/// 画像の描画をする
		/// </summary>
		/// <param name="_position">描画基準座標</param>
		/// <param name="_hTexture">テクスチャのハンドル</param>
		void DrawImage(const Vector2& _position, const TextureHandle _hTexture);
		void DrawImage(const Vector2& _position, const Vector2& _scale, const TextureHandle _hTexture);
	};
}
