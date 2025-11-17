#pragma once
#include "Core/IGameSystem.h"
#include "Utility/Accessor.h"

namespace wtgb
{
	/// <summary>
	/// カーソルを司るゲームシステム
	/// </summary>
	class Cursor : public IGameSystem
	{
	public:
		/// <summary>
		/// カーソル座標の更新処理だけのアクセッサ
		/// </summary>
		class CursorUpdater : public Accessor<Cursor>
		{
			friend class GameWindow;
		public:
			using Accessor<Cursor>::Accessor;
			~CursorUpdater() {}

			/// <summary>
			/// カーソルの位置を更新する
			/// </summary>
			/// <param name="_position"></param>
			void UpdatePosition(const Vector2Int& _position);
		};

	public:
		Cursor();
		~Cursor();

		/// <summary>
		/// 更新の呼び出しタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }
		
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
		/// 画面の中心にマウスカーソルを固定するか
		/// </summary>
		/// <param name="_isCenterLock">固定する true / false</param>
		void SetCenterLock(const bool _isCenterLock);
		/// <summary>
		/// 画面の中心にマウスカーソルが固定されているか
		/// </summary>
		/// <returns>固定されている true / false</returns>
		inline bool IsCenterLock() const { return isCenterLock_; }

		/// <summary>
		/// 1フレーム間でのカーソルの動きを取得する
		/// </summary>
		/// <returns>1フレーム間でのカーソルの移動量</returns>
		Vector2Int GetFrameMove() const { return frameMove_; }

		/// <summary>
		/// 座標更新処理アクセッサを取得する
		/// </summary>
		/// <returns>カーソルの座標更新処理のアクセッサ</returns>
		CursorUpdater& GetUpdater() { return updater_; }

		/// <summary>
		/// カーソルの表示を設定する
		/// </summary>
		/// <param name="_isShow">カーソルを表示する</param>
		void SetShow(const bool _isShow);
		/// <summary>
		/// カーソルを表示しているかを取得
		/// </summary>
		/// <returns>表示している true / false</returns>
		bool IsShow() const { return isShow_; }

	private:
		/// <summary>
		/// カーソルの座標を中央にする
		/// </summary>
		void SetPositionCenter();

	private:
		/// <summary>
		/// システムにアクセス
		/// </summary>
		/// <returns>システム</returns>
		ViewerCached& System() { return system_; }

	private:
		Vector2Int previousPosition_;  // 前回のフレームでのカーソル座標
		bool isCenterLock_;  // カーソルを画面中央に固定するか
		bool isIgnoreMoveFlag_;  // 1回だけ移動量を無視するフラグ
		bool isShow_;  // 表示されているか
		ViewerCached system_;  // システムアクセス用
		Vector2Int frameMoveDelta_;  // 1フレーム間の移動加算
		Vector2Int frameMove_;     // 1フレームでの移動量

		// TODO: 不要
		Vector2Int clientSize_;  // ウィンドウクライアントの大きさ

		CursorUpdater updater_;  // カーソルの座標更新処理アクセス用
	};
}

