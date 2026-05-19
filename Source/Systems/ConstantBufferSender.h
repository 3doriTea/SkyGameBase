#pragma once
#include <wtgb.h>
#include "ConstantBufferSender/ConstantBufferType.h"
#include "ConstantBufferSender/IConstantBuffer.h"

/// <summary>
/// シェーダに送るグローバル以外のコンスタントバッファ(ラップ済み)を管理するクラス
/// </summary>
class ConstantBufferSender : public IGameSystem
{
public:
	ConstantBufferSender();
	~ConstantBufferSender();

	/// <summary>
	/// 更新タイミングを取得
	/// </summary>
	/// <returns>更新タイミング</returns>
	const CallType GetCallType() override { return CallType::DoNotUpdate; }
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="_viewer">システム参照</param>
	/// <returns>初期化処理の結果</returns>
	Result Init(const ViewerInit& _viewer) override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_system">システム参照</param>
	void Update(const ViewerUpdate& _system) override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void End() override;

	/// <summary>
	/// コンスタントバッファを送信する
	/// </summary>
	/// <typeparam name="T">コンスタントバッファの型</typeparam>
	/// <typeparam name="Func">void(T*)</typeparam>
	/// <param name="_callback">コールバック関数として更新値の更新と送信</param>
	/// <param name="_viewer">システム参照</param>
	template<typename T, typename Func>
	void SendConstant(Func&& _callback, const ViewerCached _viewer);

private:
	/// <summary>
	/// コンスタントバッファと型情報の登録
	/// </summary>
	/// <typeparam name="T">登録する型</typeparam>
	template<typename T>
	void Register();

	/// <summary>
	/// コンスタントバッファを取得する
	/// </summary>
	/// <typeparam name="T">コンスタントバッファ構造体の型</typeparam>
	/// <returns>コンスタントバッファの参照ポインタ</returns>
	template<typename T>
	std::unique_ptr<IConstantBuffer>& GetConstantBuffer();

private:
	// 各コンスタントバッファ
	std::array<std::unique_ptr<IConstantBuffer>, ConstantBufferType_Max> pConstantBuffers_;

	// 型インデクスをコンスタントバッファのインデクスに変換する連想配列
	std::map<std::type_index, uint32_t> typeToIndex_;
};

#include "ConstantBufferSender.inl"
