#pragma once
#include "LibHeader/FileSystem.h"
#include "Core/IGameSystem.h"
#include "ResourceSystem/Texture.h"

namespace wtgb
{
	class ResourceSystem : public IGameSystem
	{
	public:
		ResourceSystem();
		~ResourceSystem();

		/// <summary>
		/// 更新タイミングを取得する
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::DoNotUpdate; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">他システムのアクセッサ</param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">他システムのアクセッサ</param>
		void Update(const ViewerUpdate& _system) override {}
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// テクスチャを読み込む
		/// </summary>
		/// <param name="_fileName">テクスチャの画像ファイル名</param>
		/// <returns>テクスチャのハンドル</returns>
		TextureHandle LoadTexture(const fs::path& _fileName);
		/// <summary>
		/// テクスチャを読み込む
		/// </summary>
		/// <param name="_fileName">テクスチャの画像ファイル名</param>
		/// <returns>テクスチャのハンドル</returns>
		TextureHandle LoadTexture(const std::string& _fileName);

		/// <summary>
		/// テクスチャを設定
		/// </summary>
		/// <param name="_config">テクスチャの詳細設定</param>
		/// <returns>テクスチャのハンドル</returns>
		TextureHandle LoadTexture(const Texture::Config& _config);

		/// <summary>
		/// ファイル名からテクスチャを取得
		/// </summary>
		/// <param name="_fileName">ファイル名</param>
		/// <returns>テクスチャのポインタ / なければ nullptr</returns>
		Texture* GetTexture(const std::string& _fileName);

		/// <summary>
		/// ハンドルからテクスチャを取得
		/// </summary>
		/// <param name="_hTexture">テクスチャのハンドル</param>
		/// <returns>テクスチャのポインタ / なければ nullptr</returns>
		Texture* GetTexture(const TextureHandle _hTexture);

	private:
		HandlerCollection<Texture, TextureHandle> textures_;
		ViewerCached system_;
	};
}
