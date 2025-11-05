#pragma once
#include "Core/IGameSystem.h"
#include "Utility/Accessor.h"

#pragma comment(lib, "d3d11.lib")

namespace wtgb
{
	class Direct3DResource;

	/// <summary>
	/// DirectX11-3D系の管理クラス
	/// </summary>
	class Direct3D : public IGameSystem
	{
	public:
		class ResourceAccessor : public Accessor<Direct3D>
		{
			friend Direct3D;
		private:
			using Accessor<Direct3D>::Accessor;
			~ResourceAccessor() {}
		
		public:
			 ID3D11Device* Device();
			 ID3D11DeviceContext* Context();
		};

	public:
		Direct3D();
		~Direct3D();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// 描画する
		/// </summary>
		void Render();

		/// <summary>
		/// シェーダをセットする
		/// </summary>
		/// <param name="_hShader">シェーダハンドル</param>
		void SetShader(const ShaderHandle _hShader);

		/// <summary>
		/// リソースアクセッサを取得
		/// </summary>
		/// <returns>リソースへのアクセッサ</returns>
		ResourceAccessor& Resource() { return resourceAccessor_; }

	private:
		Direct3DResource* pResource_;  // リソースのポインタ

		ViewerCached system_;  // システムアクセス用
		ResourceAccessor resourceAccessor_;  // リソースへのアクセッサ
	};
}
