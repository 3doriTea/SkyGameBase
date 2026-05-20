//#include "ConstantBufferSender.h"
#include "ConstantBufferSender/PlayerConstantBuffer.h"
#include "ConstantBufferSender/StageConstantBuffer.h"
#include "ConstantBufferSender.h"

inline ConstantBufferSender::ConstantBufferSender() :
	pConstantBuffers_{},
	typeToIndex_{}
{
}

inline ConstantBufferSender::~ConstantBufferSender()
{
}

inline Result ConstantBufferSender::Init(const ViewerInit& _viewer)
{
	// 各コンスタントバッファの登録をしていく
	this->template Register<PlayerConstantBuffer>(_viewer.GetCache());
	this->template Register<StageConstantBuffer>(_viewer.GetCache());

	return Result::Code::Ok;
}

inline void ConstantBufferSender::Update(const ViewerUpdate& _system)
{
}

inline void ConstantBufferSender::End()
{
}

template<typename T, typename Func>
inline void ConstantBufferSender::SendConstant(Func&& _callback, const ViewerCached _viewer)
{
	// ラップ済みコンスタントバッファ取得
	IConstantBuffer* pConstantBuffer{ GetConstantBuffer<T>().get() };

	// コールバックで更新してもらう
	_callback(static_cast<T*>(pConstantBuffer));


	ID3D11DeviceContext* pContext{ _viewer.Get<Direct3D>().Resource().Context() };

	HRESULT hResult{};

	D3D11_MAPPED_SUBRESOURCE data{};
	hResult = pContext->Map(pConstantBuffer->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (SUCCEEDED(hResult))
	{

		size_t size{ pConstantBuffer->GetSize() };

		// 送信
		memcpy_s(
			data.pData,
			data.RowPitch,
			pConstantBuffer->GetPtr(),
			pConstantBuffer->GetSize());
		pContext->Unmap(pConstantBuffer->GetConstantBuffer().Get(), 0);
	}
	else
	{
		wassert(SUCCEEDED(hResult) && "コンスタントバッファ送信に失敗");
		return;  // 失敗したため無視
	}
}

template<typename T>
inline void ConstantBufferSender::Register(const ViewerCached _viewer)
{
	// コンスタントバッファをインスタンス
	std::unique_ptr<T> pConstantBuffer{ std::make_unique<T>() };

	// コンスタントバッファの種類
	ConstantBufferType constantBufferType{ pConstantBuffer.get()->GetConstantBufferType() };

	// 型情報とコンスタントバッファの種類を紐づけ
	typeToIndex_[std::type_index{ typeid(T) }] = constantBufferType;
	pConstantBuffers_[constantBufferType] = std::move(pConstantBuffer);

	pConstantBuffers_[constantBufferType].get()->Initialize(_viewer);
}

template<typename T>
inline std::unique_ptr<IConstantBuffer>& ConstantBufferSender::GetConstantBuffer()
{
	std::type_index typeIndex{ std::type_index{ typeid(T) } };

	wassert(typeToIndex_.count(typeIndex) > 0 && "指定の型は未登録");

	size_t constantBufferIndex{ typeToIndex_[typeIndex] };

	return pConstantBuffers_[constantBufferIndex];
}
