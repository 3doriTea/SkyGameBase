#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class GameWindow : public IGameSystem
	{
	public:
		/// <summary>
		/// 画面のリフレッシュレート
		/// </summary>
		struct RefreshRate
		{
			/// <summary>
			/// FPSでリフレッシュレートを指定
			/// </summary>
			/// <param name="fps">Frame par sec</param>
			RefreshRate(const uint32_t fps) :
				denominator{ 1U },
				numerator{ fps }
			{}
			uint32_t denominator;  // 分子
			uint32_t numerator;  // 分母
		};
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
			// 画面の更新頻度 (秒)
			RefreshRate refreshRateSec;
			// ウィンドウであるか
			BOOL windowed{ TRUE };
		};

	private:
		/// <summary>
		/// 作成したウィンドウの情報
		/// </summary>
		struct CreatedWindowData
		{
			/// <summary>
			/// 作成時のウィンドウ設定
			/// </summary>
			CreateWindowConfig config;
			/// <summary>
			/// ウィンドウのハンドル
			/// </summary>
			HWND hWnd;
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

		/// <summary>
		/// メインウィンドウのウィンドウハンドルを取得
		/// </summary>
		/// <returns>ウィンドウハンドル</returns>
		HWND GetMainWindowHandle();

		/// <summary>
		/// メインウィンドウのウィンドウサイズを取得
		/// </summary>
		/// <returns>2次元の整数ベクトル</returns>
		Vector2Int GetMainWindowSize();
		/// <summary>
		/// 画面の更新間隔 (秒) を取得
		/// </summary>
		/// <returns>画面の更新間隔 (秒)</returns>
		RefreshRate GetMainWindowRefreshRate();
		/// <summary>
		/// メインウィンドウがウィンドウであるかを取得
		/// </summary>
		/// <returns>ウィンドウである true / false</returns>
		BOOL GetMainWindowIsWindowed();

		/// <summary>
		/// メインウィンドウがアクティブ(選択中のウィンドウ)かどうか
		/// </summary>
		/// <returns>アクティブである true / false</returns>
		BOOL IsActiveMainWindow();

		/// <summary>
		/// WinProcのイベントを受け取る
		/// </summary>
		/// <param name="_callback"></param>
		void AddWinProcListener(const std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>& _callback);

	private:
		const CreateWindowConfig& GetMainWindowData();

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
		HandlerCollection<CreatedWindowData, GameWindowHandle> windowHandles_;
		MSG peekedMessage_;
		static std::list<std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>> winProcCallbacks_;

	private:
		static Vector2Int mousePosition_;  // マウス座標 (WinProcで更新値仮置き) お好きにとって！
	};
}
