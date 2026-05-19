//#include "ConstantBufferSender.h"
#include "ConstantBufferSender/PlayerConstantBuffer.h"
#include "ConstantBufferSender.h"

inline ConstantBufferSender::ConstantBufferSender() :
	pConstantBuffers_{},
	typeToIndex_{}
{
	this->template Register<PlayerConstantBuffer>();
}

inline ConstantBufferSender::~ConstantBufferSender()
{
}

inline Result ConstantBufferSender::Init(const ViewerInit& _viewer)
{
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

	D3D11_MAPPED_SUBRESOURCE data{};
	pContext->Map(pConstantBuffer->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	// 送信
	memcpy_s(
		data.pData,
		data.RowPitch,
		pConstantBuffer->GetPtr(),
		pConstantBuffer->GetSize());
	pContext->Unmap(pConstantBuffer->GetConstantBuffer().Get(), 0);
}

template<typename T>
inline void ConstantBufferSender::Register()
{
	std::unique_ptr<T> pConstantBuffer{ std::make_unique<T>() };

	typeToIndex_[std::type_index{ typeid(T) }] = pConstantBuffer.get()->GetConstantBufferType();
	pConstantBuffers_[ConstantBufferType_Player] = std::move(pConstantBuffer);
}

template<typename T>
inline std::unique_ptr<IConstantBuffer>& ConstantBufferSender::GetConstantBuffer()
{
	std::type_index typeIndex{ std::type_index{ typeid(T) } };

	wassert(typeToIndex_.count(typeIndex) > 0 && "指定の型は未登録");

	size_t constantBufferIndex{ typeToIndex_[typeIndex] };

	return pConstantBuffers_[constantBufferIndex];
}
