#pragma once
#include "Core/IGameSystem.h"
#include "Utility/Accessor.h"
#include "Input/KeyCode.h"
#include "Input/ButtonCode.h"
#include "Input/MouseCode.h"


namespace wtgb
{
	class InputResource;

	/// <summary>
	/// 入力系管理クラス
	/// </summary>
	class Input : public IGameSystem
	{
	public:
		class InputData : public Accessor<Input>
		{
		public:
			using Accessor::Accessor;
			~InputData() {};

			bool IsKey(const KeyCode _keyCode);
			bool IsKeyDown(const KeyCode _keyCode);
			bool IsKeyUp(const KeyCode _keyCode);

			bool IsButton(const ButtonCode _buttonCode);
			bool IsButtonDown(const ButtonCode _buttonCode);
			bool IsButtonUp(const ButtonCode _buttonCode);

			bool IsMouse(const MouseCode _mouseCode);
			bool IsMouseDown(const MouseCode _mouseCode);
			bool IsMouseUp(const MouseCode _mouseCode);
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
		Result Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	private:
		InputResource* pResource_;
	};
}


