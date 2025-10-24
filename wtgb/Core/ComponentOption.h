#pragma once
#include "GameObjectBuilder.h"

namespace wtgb
{
	class GameObjectBuilder;

	/// <summary>
	/// 追加したコンポーネントの設定をするか、設定せずにコンポーネントを追加するか、のオプション
	/// </summary>
	/// <typeparam name="ComponentT"></typeparam>
	template<typename ComponentT>
	class ComponentOption : public Accessor<ComponentT>
	{
	public:
		ComponentOption(GameObjectBuilder& _builder, ComponentT* _pComponent) :
			Accessor<ComponentT>::Accessor{ _pComponent },
			builder_{ _builder }
		{}
		~ComponentOption() {}

		/// <summary>
		/// 設定はせずにコンポーネントを追加
		/// </summary>
		/// <typeparam name="ComponentT"></typeparam>
		/// <typeparam name="...Args"></typeparam>
		/// <param name="...args"></param>
		/// <returns></returns>
		template<typename ComponentT>
		ComponentOption<ComponentT>& AddComponent()
		{
			ComponentT* pComponent{ builder_.pTarget_->template AddComponent<ComponentT>() };

			ComponentOption<ComponentT>* pNewOption
			{
				new ComponentOption<ComponentT>{ builder_, Accessor<ComponentT>::GetAccess() }
			};

			delete this;
			return *pNewOption;
		}

		/// <summary>
		/// コンポーネントの設定開始
		/// </summary>
		/// <returns>コンポーネントのセッター</returns>
		ComponentT::Setter& BeginSetter()
		{
			return *(new ComponentT::Setter{ builder_, Accessor<ComponentT>::GetAccess(), this });
		}

		GameObjectBuilder& Build()
		{
			delete this;
			return builder_;
		}

	private:
		GameObjectBuilder& builder_;
	};
}