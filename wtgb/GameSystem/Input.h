#pragma once
#include "Core/IGameSystem.h"
#include "Utility/Accessor.h"
#include "Input/KeyCode.h"
#include "Input/PadCode.h"
#include "Input/MouseCode.h"

#include "Input/InputData.h"

#include "Utility/InputChecker.h"

namespace wtgb
{
	class InputResource;

	/// <summary>
	/// 入力系管理クラス
	/// </summary>
	class Input : public IGameSystem
	{
	public:
		/// <summary>
		/// 入力ステート取得のためだけのアクセッサー
		/// </summary>
		class InputGetter : public Accessor<Input>
		{
		public:
			using Accessor::Accessor;
			~InputGetter() {}

			bool IsKey(const KeyCode _keyCode) const;
			bool IsKeyDown(const KeyCode _keyCode) const;
			bool IsKeyUp(const KeyCode _keyCode) const;

			bool IsButton(const PadCode _padCode) const;
			bool IsButtonDown(const PadCode _padCode) const;
			bool IsButtonUp(const PadCode _padCode) const;

			bool IsMouse(const MouseCode _mouseCode) const;
			bool IsMouseDown(const MouseCode _mouseCode) const;
			bool IsMouseUp(const MouseCode _mouseCode) const;

			/// <summary>
			/// 現在のマウス座標
			/// </summary>
			/// <returns>マウス座標 Vector2Int</returns>
			Vector2Int GetMousePosition() const;
			/// <summary>
			/// マウスの移動量
			/// </summary>
			/// <returns>マウスの移動量</returns>
			Vector2Int GetMouseMove() const;
		};

		/// <summary>
		/// マウスの状態更新のためだけのアクセッサー
		/// </summary>
		class MouseUpdater : public Accessor<Input>
		{
			friend class GameWindow;
		private:
			using Accessor::Accessor;

		public:
			~MouseUpdater() {}

		private:
			void SetMousePosition(const Vector2Int _position);
		};

	public:
		Input();
		~Input();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <returns>結果</returns>
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
		/// 入力取得用クラスの参照
		/// </summary>
		/// <returns>入力ゲッターの参照</returns>
		const InputGetter& Getter() const { return inputGetter_; }

		/// <summary>
		/// <para>マウス座標更新用アクセッサを取得</para>
		/// <para>指定したクラス以外は取得する理由はないです</para>
		/// </summary>
		/// <returns>マウス座標更新用アクセッサの参照</returns>
		MouseUpdater& GetMouseUpdater() { return mouseUpdater_; }

	private:
		MouseUpdater mouseUpdater_;  // マウス設定専用
		InputGetter inputGetter_;  // 入力取得用
		InputResource* pResource_;  // 入力デバイス系のリソース
		InputData inputData_;  // 入力ステートのデータキャリア

		InputChecker::Checker<BYTE> isDown_;  // 押された瞬間か
		InputChecker::Checker<BYTE> isUp_;    // 離された瞬間か
	};
}


