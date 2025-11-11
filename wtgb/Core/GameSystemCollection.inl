#include "GameSystem/ComponentManager.h"

template<wtgb::GameSystemT T, typename ...Args>
inline const wtgb::GameSystemCollection::GameSystemAdder&
wtgb::GameSystemCollection::GameSystemAdder::Register(Args&& ...args) const
{
	assert(GetAccess() && "ゲームシステムコレクションがnullptr参照されてしまう");

	// コレクション要素への参照
	TypeKeys& gameSystemTypeKey{ GetAccess()->gameSystemTypeKey_ };
	GameSystems& gameSystems{ GetAccess()->gameSystems_ };
	Indexes& callFrameIndexes{ GetAccess()->callFrameIndexes_ };
	Indexes& callCycleIndexes{ GetAccess()->callCycleIndexes_ };

	IGameSystem* pGameSystem{ new T{ args... } };

	const Index index{ gameSystems.size() };

	gameSystems.push_back(pGameSystem);
	gameSystemTypeKey.emplace(typeid(T), index);

	// 呼び出すタイミング別で要素番号を保存しておく
	switch (pGameSystem->GetCallType())
	{
	case IGameSystem::CallType::Frame:  // フレーム毎の呼び出しコレクションに追加
		callFrameIndexes.push_back(index);
		break;
	case IGameSystem::CallType::Cycle:  // サイクル毎の呼び出しコレクションに追加
		callCycleIndexes.push_back(index);
		break;
	case IGameSystem::CallType::DoNotUpdate:  // 更新不要
	default:
		break;
	}

	// IComponentPool なら処理する
	if constexpr (std::is_base_of_v<IComponentPool, T>)
	{
		
	}

	return *this;
}

template<wtgb::GameSystemT T>
inline T& wtgb::GameSystemCollection::GameSystemViewer::Get() const
{
	TypeKeys& gameSystemTypeKey{ GetAccess()->gameSystemTypeKey_ };
	GameSystems& gameSystems{ GetAccess()->gameSystems_ };

	Index index{};
	try
	{
		index = gameSystemTypeKey.at(typeid(T));
	}
	catch (const std::out_of_range& exception)
	{
		(void)exception;  // 意図的に使っていないよ！
		// 型が登録されていない
		assert(false && "指定されたゲームシステム型が登録されていない");
	}

	IGameSystem* pGameSystem{};
	try
	{
		pGameSystem = gameSystems.at(index);
	}
	catch (const std::out_of_range& exception)
	{
		(void)exception;  // 意図的に使っていないよ！
		// 型からindexは取得済み、実体へのポインタが未登録
		assert(false && "指定されたゲームシステムが登録されていない");
	}

	T* p{ dynamic_cast<T*>(pGameSystem) };
	assert(p != nullptr && "指定された型がゲームシステムではない @wtgb::GameSystemCollection::Get");

	return *p;
}
