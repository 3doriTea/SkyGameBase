#include "WTGBAssert.h"

template<typename T, typename ...Args>
inline const wtgb::GameSystemCollection::GameSystemAdder&
wtgb::GameSystemCollection::GameSystemAdder::Register(Args&& ...args) const
{
	assert(GetAccess() && "ゲームシステムコレクションがnullptr参照されてしまう");

	// コレクション要素への参照
	TypeKeys& gameSystemTypeKey{ GetAccess()->gameSystemTypeKey_ };
	GameSystems& gameSystems{ GetAccess()->gameSystems_ };
	Indexes& callFrameIndexes{ GetAccess()->callFrameIndexes_ };
	Indexes& callCycleIndexes{ GetAccess()->callCycleIndexes_ };
	Indexes& componentPoolIndexes{ GetAccess()->componentPoolIndexes_ };
	
	if (gameSystemTypeKey.count(typeid(T)))
	{
		wassert(false && "同じシステムが重複して登録されました。");
		return *this;  // 既に登録されているため無視
	}

	// 登録するゲームシステムに割り当てる要素番号
	const Index INDEX{ gameSystems.size() };

	gameSystems.push_back(std::make_unique<T>(args...));
	gameSystemTypeKey.emplace(typeid(T), INDEX);

	// 呼び出すタイミング別で要素番号を保存しておく
	switch (gameSystems[INDEX].get()->GetCallType())
	{
	case IGameSystem::CallType::Frame:  // フレーム毎の呼び出しコレクションに追加
		callFrameIndexes.push_back(INDEX);
		break;
	case IGameSystem::CallType::Cycle:  // サイクル毎の呼び出しコレクションに追加
		callCycleIndexes.push_back(INDEX);
		break;
	case IGameSystem::CallType::DoNotUpdate:  // 更新不要
	default:
		break;
	}

	// IComponentPool なら処理する
	if constexpr (std::is_base_of_v<IComponentPool, T>)
	{
		componentPoolIndexes.push_back(INDEX);
	}

	return *this;
}

template<typename T>
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
		assert(false && "指定されたゲームシステム型が登録されていない ※そもそも登録する予定がない可能性あり！CPのつけ忘れてではない？");
	}

	IGameSystem* pGameSystem{};
	try
	{
		pGameSystem = gameSystems.at(index).get();
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
