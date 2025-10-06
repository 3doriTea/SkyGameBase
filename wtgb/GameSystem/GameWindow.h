#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class GameWindow : public IGameSystem
	{
	public:
		struct Config
		{
			std::string_view title;
		};
	public:
		GameWindow();
		~GameWindow();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Cycle; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// ウィンドウを作成する
		/// </summary>
		void Create(const Config& _config);

	private:
		/// <summary>
		/// ウィンドウイベントのコールバック処理
		/// </summary>
		/// <param name="hWnd">ウィンドウハンドル</param>
		/// <param name="message">メッセージ</param>
		/// <param name="wParam">追加データ 状態Idフラグなど</param>
		/// <param name="lParam">詳細データ 2つの値やポインタなど</param>
		/// <returns>結果コード</returns>
		static LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}
