#pragma once
#include "IComponent.h"


namespace wtgb
{
	/// <summary>
	/// コンポーネントの基底クラス
	/// </summary>
	/// <typeparam name="ComponentPoolT">所属するコンポーネントプール型</typeparam>
	template<typename ComponentPoolT>
	class Component : public IComponent
	{
	public:
		/// <summary>
		/// 所属するコンポーネントプールの型
		/// </summary>
		using PoolT = ComponentPoolT;

	public:
		Component() {}
		virtual ~Component() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_system">システム参照</param>
		virtual void Init(ViewerCached _system) override {};
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システム参照</param>
		virtual void Update(ViewerCached _system) override {};
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void End() override{};
	};
}
