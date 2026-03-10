#pragma once
#include "pch/pch.h"
#include "Utility/IResource.h"

namespace wtgb
{
	/// <summary>
	/// 入力リソース
	/// </summary>
	class InputResource : public IResource<>
	{
	public:
		/// <summary>
		/// 設定
		/// </summary>
		struct Config
		{
			// TODO: ハンドル管理するシステムから取得する
			HWND hWnd;  // ウィンドウハンドル
			// REF: https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ee417921(v=vs.85)
			DWORD cooperativeLevelFlag;  // 干渉度合いフラグ
		};

	public:
		InputResource(const Config& _config);
		~InputResource();

		/// <summary>
		/// キーボードのデバイスポインタを取得
		/// </summary>
		/// <returns>キーボードのデバイスポインタ</returns>
		LPDIRECTINPUTDEVICE8 GetKeyDevice() const { return pKeyDevice_; }
		/// <summary>
		/// マウスのデバイスポインタを取得
		/// </summary>
		/// <returns>マウスのデバイスポインタ</returns>
		LPDIRECTINPUTDEVICE8 GetMouseDevice() const { return pMouseDevice_; }

	private:
		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
		/// <summary>
		/// 解放処理
		/// </summary>
		void Release() override;

	private:
		LPDIRECTINPUT8 pDirectInput_;
		LPDIRECTINPUTDEVICE8 pKeyDevice_;
		LPDIRECTINPUTDEVICE8 pMouseDevice_;

		Config config_;  // 設定
	};
}
