#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"
#include "Core/GameSystemViewer.h"
#include "GameSystem/ModelMesh/IMeshSimple.h"

namespace wtgb
{
	/// <summary>
	/// モデルの抽象クラス
	/// </summary>
	class ModelResource : public IMeshSimple
	{
	public:
		ModelResource(const std::string& _fileName);
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
		virtual void Init(ViewerCached _system) override = 0;
		/// <summary>
		/// 解放処理
		/// </summary>
		virtual void Release(ViewerCached _system) override = 0;

	private:
		const std::string FILE_NAME_;
	};
}
