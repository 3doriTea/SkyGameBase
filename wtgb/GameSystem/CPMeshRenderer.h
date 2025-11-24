#pragma once
#include "ComponentPool.h"
#include "GameComponent/MeshRenderer.h"

namespace wtgb
{
	class IMeshSimple;
	class MeshRenderer;
	class Transform;

	/// <summary>
	/// コンポーネントプール : メッシュ描画
	/// </summary>
	class CPMeshRenderer : public ComponentPool<MeshRenderer>
	{
	public:
		CPMeshRenderer();
		~CPMeshRenderer();

		/// <summary>
		/// シンプルメッシュを単体で描画する
		/// </summary>
		/// <param name="_pMeshSimple">シンプルメッシュの派生</param>
		/// <param name="_pTransform">座標系</param>
		/// <param name="_hShader">シェーダ</param>
		void Render(IMeshSimple* _pMeshSimple, Transform* _pTransform, const ShaderHandle _hShader);

	private:
		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;

		//void 
	};
}
