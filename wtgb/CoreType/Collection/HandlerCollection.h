#pragma once
#include "pch/pch.h"


namespace wtgb
{
	// 無効なハンドル値
	static const uint32_t INVALID_HANDLE{ 0 };

	/// <summary>
	/// ハンドルがキーの連想配列、コレクションクラス
	/// </summary>
	/// <typeparam name="ValueT"></typeparam>
	/// <typeparam name="HandleT"></typeparam>
	template<typename ValueT, std::unsigned_integral HandleT = uint32_t>
	class HandlerCollection
	{
	private:
		using InnerMap = std::map<HandleT, ValueT>;
	public:
		HandlerCollection();
		~HandlerCollection();

		/// <summary>
		/// ハンドラを追加 (登録する)
		/// </summary>
		/// <typeparam name="...Args">追加するときに渡すコンストラクタ引数の型</typeparam>
		/// <param name="...args">追加するときに渡すコンストラクタ引数</param>
		/// <returns>追加されたハンドラ</returns>
		template<typename ...Args>
		HandleT Emplace(Args&& ...args);
		/// <summary>
		/// ハンドラを無効化する
		/// </summary>
		/// <param name="_handle">無効化するハンドル</param>
		/// <returns></returns>
		bool Remove(const HandleT _handle);
		/// <summary>
		/// ハンドラを全て解放する
		/// </summary>
		void Release(const std::function<void(ValueT& _value)>& _callback = [](ValueT& _value){});
		/// <summary>
		/// 登録されているハンドラが空っぽか
		/// </summary>
		/// <returns>空っぽである true / false</returns>
		bool IsEmpty() const { return this->counter_ <= 0; }
		/// <summary>
		/// 重複する要素ハンドルを取得
		/// </summary>
		/// <param name="_callback">重複をチェックするコールバック関数</param>
		/// <returns>重複するハンドル / 見つからなければ無効ハンドル</returns>
		HandleT GetContainsDuplicate(const std::function<bool(ValueT& _value)>& _callback);

		/// <summary>
		/// 頭イテレータ取得
		/// </summary>
		/// <returns>頭イテレータ</returns>
		InnerMap::iterator begin() { return innerMap.begin(); }
		/// <summary>
		/// 尾イテレータ取得
		/// </summary>
		/// <returns>尾イテレータ</returns>
		InnerMap::iterator end() { return innerMap.end(); }

		std::remove_pointer_t<ValueT>& At(const HandleT _handle);
		const std::remove_pointer_t<ValueT>& At(const HandleT _handle) const;
	private:
		InnerMap innerMap{};
		HandleT counter_{};
	};
}

#include "HandlerCollection.inl"
