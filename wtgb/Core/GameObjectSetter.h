#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"

namespace wtgb
{
	class GameObjectBuilder;
	template<typename T>
	class ComponentOption;

	template<typename ComponentT>
	class GameObjectSetter : public Accessor<ComponentT>
	{
	public:
		GameObjectSetter(
			GameObjectBuilder& _builder,
			ComponentT* _pComponent,
			ComponentOption<ComponentT>* _pOption) :
			Accessor<ComponentT>::Accessor{ _pComponent },
			builder_{ _builder },
			pOption_{ _pOption }
		{
		}
		virtual ~GameObjectSetter() {}

		/// <summary>
		/// コンポーネントの設定終了
		/// </summary>
		/// <returns>ビルダー</returns>
		ComponentOption<ComponentT>& EndSetter()
		{
			SAFE_DELETE(this);
			return *pOption_;
		}

	private:
		GameObjectBuilder& builder_;
		ComponentOption<ComponentT>* pOption_;
	};
}