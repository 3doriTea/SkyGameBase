#pragma once
#include "pch/pch.h"
#include "Core/GameSystemViewer.h"


namespace wtgb
{
	/// <summary>
	/// シェーダのコンスタント
	/// </summary>
	template<typename StructT>
	class ShaderConstant
	{
		static_assert(alignof(StructT) == 16
			&& "コンスタントバッファの構造体はアラインメントが16byteである必要があります。");
	public:
		ShaderConstant();
		~ShaderConstant();

		/// <summary>
		/// 使用する基底のレジスタ番号をセットする
		/// </summary>
		/// <param name="_registerNumber">レジスタ番号</param>
		void SetBaseRegistryNumber(const UINT _registerNumber) { beginSlot_ = _registerNumber; }
		/// <summary>
		/// 使用するレジスタ数をセットする
		/// </summary>
		/// <param name="_count"></param>
		void SetUseRegistryCount(const UINT _count) { slotCount_ = _count; }

		/// <summary>
		/// コンスタントバッファの初期化処理
		/// </summary>
		/// <param name="_system">システム参照</param>
		void Init(ViewerCached _system);
		/// <summary>
		/// コンスタントバッファのGPU送信処理
		/// </summary>
		/// <param name="_system">システム参照</param>
		void Send(ViewerCached _system);

	private:
		ComPtr<ID3D11Buffer> pConstantBuffer_;
		UINT beginSlot_;  // コンスタントバッファをセットする基底レジスタ番号
		UINT slotCount_;  // 基底レジスタから使用するレジスタの数
	};
}

#include "ShaderConstant.inl"
