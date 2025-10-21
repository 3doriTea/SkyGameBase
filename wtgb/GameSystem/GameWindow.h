#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	using GameWindowHandle = uint32_t;

	class GameWindow : public IGameSystem
	{
	public:
		struct CreateWindowConfig
		{
			std::string_view title;
			// REF: https://learn.microsoft.com/ja-jp/windows/win32/winmsg/window-class-styles
			UINT classStyle{ CS_VREDRAW | CS_HREDRAW };
			HICON icon;
			HICON iconSmile;
			HCURSOR cursor;
			// REF: https://learn.microsoft.com/ja-jp/windows/win32/winmsg/window-styles
			DWORD clientStyle{ WS_OVERLAPPEDWINDOW };  // クライアント領域のスタイル
			// REF: https://learn.microsoft.com/ja-jp/windows/win32/winmsg/extended-window-styles
			DWORD clientStyleEx{ WS_EX_OVERLAPPEDWINDOW };  // クライアント領域の拡張
			BOOL hasMenu{ FALSE };

			Vector2Int windowScreenSize;
			// ウィンドウの初期座標
			Vector2Int initPosition;
			// ウィンドウの親ウィンドウ
			HWND hWndParent{ nullptr };
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
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// ウィンドウを作成する
		/// </summary>
		/// <param name="_config">作成するウィンドウの設定</param>
		/// <returns>ウィンドウを特定するハンドル</returns>
		GameWindowHandle Create(const CreateWindowConfig& _config);

		HWND GetMainWindowHandle();

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

	private:
		// ウィンドウハンドルのコレクション
		HandlerCollection<HWND, GameWindowHandle> windowHandles_;
		MSG peekedMessage_;

	private:
		static Vector2Int mousePosition_;  // マウス座標 (WinProcで更新値仮置き) お好きにとって！
	};
}
