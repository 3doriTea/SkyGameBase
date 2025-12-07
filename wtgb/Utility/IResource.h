#pragma once
#ifdef _DEBUG
#include "CallStackViewer.h"
#include "WTGBAssert.h"
#include "GameSystem/Debug.h"
#endif

namespace wtgb
{
	/// <summary>
	/// リソースのインタフェース
	/// </summary>
	template<typename... Args>
	class IResource
	{
	public:
		inline IResource()
		{
#ifdef _DEBUG
			isReleased_ = true;
#endif
		}
		inline virtual ~IResource()
		{
#ifdef _DEBUG
			if (!isReleased_)
			{
				LOGFLN("::warn::" "リソースを解放せずにデストラクタが呼ばれている" "\n" "{}", GetStackTrace(2));
				wassert(isReleased_ && "リソースを解放せずにデストラクタが呼ばれている");
			}
#endif
		}

		/// <summary>
		/// 初期化処理 (外部から呼び出し用)
		/// </summary>
		inline virtual void CallInit(Args... args) final
		{
#ifdef _DEBUG
			isReleased_ = false;
#endif
			Init(args...);
		}
		/// <summary>
		/// 解放処理 (外部から呼び出し用)
		/// </summary>
		inline virtual void CallRelease(Args... args) final
		{
			Release(args...);
#ifdef _DEBUG
			isReleased_ = true;
#endif
		}

protected:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Init(Args... args) = 0;
	/// <summary>
	/// 解放処理
	/// </summary>
	virtual void Release(Args... args) = 0;

	private:
#ifdef _DEBUG
		bool isReleased_;
#endif
	};
}
