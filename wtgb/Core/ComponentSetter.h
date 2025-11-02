#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"


namespace wtgb
{
	class GameObjectBuilder;
	template<typename T>
	class ComponentOption;

	template<typename ComponentT>
	class ComponentSetter : public Accessor<ComponentT>
	{
	public:
		ComponentSetter(
			GameObjectBuilder& _builder,
			ComponentT* _pComponent,
			ComponentOption<ComponentT>* _pOption) :
			Accessor<ComponentT>::Accessor{ _pComponent },
			builder_{ _builder },
			pOption_{ _pOption }
		{
		}
		virtual ~ComponentSetter() {}

		/*/// <summary>
		/// コンポーネントの設定終了
		/// </summary>
		/// <returns>ビルダー</returns>
		ComponentOption<ComponentT>& EndSetter()
		{
			ComponentOption<ComponentT>& option{ *pOption_ };
			delete this;
			return option;
		}*/

		/// <summary>
		/// コンポーネントの設定終了
		/// </summary>
		/// <returns>ビルダー</returns>
		GameObjectBuilder& EndSetter();

	private:
		GameObjectBuilder& builder_;
		ComponentOption<ComponentT>* pOption_;
	};
}

#include "ComponentSetter.inl"
