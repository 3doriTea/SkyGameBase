#pragma once
#include <wtgb.h>


/// <summary>
/// はねねこボール
/// </summary>
class NekoGame : public IGame
{
public:
	NekoGame() {}
	~NekoGame() {}

	/// <summary>
	/// ゲームのタイトルを取得する
	/// </summary>
	/// <returns>ゲームのタイトル</returns>
	inline const char8_t* GetTitle() const override { return u8"はねねこ ボール"; }
	/// <summary>
	/// ゲームのバージョンを取得する
	/// </summary>
	/// <returns>ゲームのバージョン</returns>
	inline const char8_t* GetVersion() const override { return u8"1.1.2"; }

	/// <summary>
	/// 開始時のゲームシステム登録
	/// </summary>
	/// <param name="_pGameSystemAdder">ゲームシステムコレクションへの追加参照</param>
	void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) override;
};
