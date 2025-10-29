#pragma once

namespace wtgb
{
	/// <summary>
	/// リソースのインタフェース
	/// </summary>
	class IResource
	{
	public:
		IResource();
		virtual ~IResource();

		/// <summary>
		/// 初期化処理 (外部から呼び出し用)
		/// </summary>
		virtual void CallInit() final;
		/// <summary>
		/// 解放処理 (外部から呼び出し用)
		/// </summary>
		virtual void CallRelease() final;

protected:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 解放処理
	/// </summary>
	virtual void Release() = 0;

	private:
#ifdef _DEBUG
		bool isReleased_;
#endif
	};
}
