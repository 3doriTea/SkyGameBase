#pragma once
#include "Core/IGameSystem.h"
#include "Utility/Accessor.h"
#include "Direct3D/BlendMode.h"
#include "Direct3D/ZBufferMode.h"

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
			 ComPtr<ID3D11Device>& DeviceComPtr();
			 ID3D11DeviceContext* Context();
			 ComPtr<ID3D11DeviceContext>& ContextComPtr();
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
		/// 深度バッファを使うかを設定する
		/// </summary>
		/// <param name="_useDepthBuffer">深度バッファを使う true / false</param>
		void SetUseDepthBuffer(const bool _useDepthBuffer);

		/// <summary>
		/// ブレンドモードを設定する
		/// </summary>
		/// <param name="_mode">ブレンドモード</param>
		void SetBlend(const BlendMode _mode);

		/// <summary>
		/// 深度バッファのモードを設定する
		/// </summary>
		/// <param name="_mode"></param>
		void SetZBuffer(const ZBufferMode _mode);

		/// <summary>
		/// リソースアクセッサを取得
		/// </summary>
		/// <returns>リソースへのアクセッサ</returns>
		ResourceAccessor& Resource() { return resourceAccessor_; }

		/// <summary>
		/// 描画直前のコールバック
		/// </summary>
		/// <param name="_callback">描画直前に呼び出したい処理</param>
		void AddRenderListener(const std::function<void()>& _callback);

	private:
		std::list<std::function<void()>> renderCallbacks_;  // 描画直前のコールバック処理

		Direct3DResource* pResource_;  // リソースのポインタ

		ViewerCached system_;  // システムアクセス用
		ResourceAccessor resourceAccessor_;  // リソースへのアクセッサ
	};
}
