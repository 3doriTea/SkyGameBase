#pragma once
#include "Core/IGameSystem.h"
#include "Utility/Accessor.h"
#include "Input/KeyCode.h"
#include "Input/PadCode.h"
#include "Input/MouseCode.h"

#include "Input/InputData.h"

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

			bool IsKey(const KeyCode _keyCode);
			bool IsKeyDown(const KeyCode _keyCode);
			bool IsKeyUp(const KeyCode _keyCode);

			bool IsButton(const PadCode _padCode);
			bool IsButtonDown(const PadCode _padCode);
			bool IsButtonUp(const PadCode _padCode);

			bool IsMouse(const MouseCode _mouseCode);
			bool IsMouseDown(const MouseCode _mouseCode);
			bool IsMouseUp(const MouseCode _mouseCode);
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
		void Update() override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	private:
		InputResource* pResource_;  // 入力デバイス系のリソース
		InputData inputData_;  // 入力ステートのデータキャリア
	};
}


