#pragma once
#include "GameSystemViewer.h"


namespace wtgb
{
	/// <summary>
	/// コンポーネント共通のインタフェース
	/// </summary>
	class IComponent
	{
	public:
		IComponent() {}
		virtual ~IComponent() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="system_">システム参照</param>
		virtual void Init(ViewerCached system_) = 0;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="system_">システム参照</param>
		virtual void Update(ViewerCached system_) = 0;
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void End() = 0;
	};
}
