#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"

namespace wtgb
{
	class GameObject;

	class GameObjectBuilder
	{
	public:
		template<typename ComponentT>
		class Setter : public Accessor<ComponentT>
		{
		public:
			Setter(GameObjectBuilder& _builder, ComponentT* _pComponent) :
				Accessor::Accessor{ _pComponent },
				builder_{ _builder }
			{
			}
			virtual ~Setter() {}

			/// <summary>
			/// コンポーネントの設定開始
			/// </summary>
			/// <returns>コンポーネントのセッター</returns>
			ComponentT::Setter& BeginSetter()
			{
				pSetter_ = new ComponentT::Setter{};
				return *pSetter_;
			}
			/// <summary>
			/// コンポーネントの設定終了
			/// </summary>
			/// <returns>ビルダー</returns>
			GameObjectBuilder& EndSetter()
			{
				SAFE_DELETE(pSetter_);
				return builder_;
			}

		private:
			GameObjectBuilder& builder_;
			ComponentT::Setter* pSetter_;  // コンポーネントのセッターポインタ
		};

	private:
		GameObjectBuilder();
		~GameObjectBuilder();

	public:
		template<typename T, typename ...Args>
		Setter<T>& AddComponent(Args... args);

	private:
		GameObject* pTarget_;  // 構築するゲームオブジェクト
	};
}

inline wtgb::GameObjectBuilder::GameObjectBuilder()
{
}

inline wtgb::GameObjectBuilder::~GameObjectBuilder()
{
}

template<typename T, typename ...Args>
inline wtgb::GameObjectBuilder::Setter<T>& wtgb::GameObjectBuilder::AddComponent(Args... args)
{
	T* pComponent{ pTarget_->AddComponent<T>(args...) };
	GameObjectBuilder::Setter<T>* pSetter
	{
		new GameObjectBuilder::Setter<T>{ *this, pComponent }
	};
	return *pSetter;
}
