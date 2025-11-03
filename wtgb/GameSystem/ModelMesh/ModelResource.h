#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"
#include "Core/GameSystemViewer.h"

namespace wtgb
{
	/// <summary>
	/// モデルの抽象クラス
	/// </summary>
	class ModelResource : public IResource
	{
	public:
		ModelResource(const std::string& _fileName, const ViewerCached _system);
		virtual ~ModelResource() {}

		/// <summary>
		/// モデルのファイル名を取得する
		/// </summary>
		/// <returns></returns>
		std::string_view FileName() const { return FILE_NAME_; }

	protected:
		/// <summary>
		/// 初期化処理
		/// </summary>
		virtual void Init() override = 0;
		/// <summary>
		/// 解放処理
		/// </summary>
		virtual void Release() override = 0;

		/// <summary>
		/// システムへのアクセス
		/// </summary>
		/// <returns></returns>
		const ViewerCached& System() { return SYSTEM_; }

	private:
		const std::string FILE_NAME_;
		const ViewerCached SYSTEM_;
	};
}
