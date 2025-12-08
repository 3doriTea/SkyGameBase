#pragma once
#include "ComponentPool.h"
#include "GameComponent/MeshRenderer.h"

namespace wtgb
{
	class IMeshSimple;
	class IMeshSimple2D;
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
		void Render(IMeshSimple* _pMeshSimple, Transform* _pTransform, const ShaderHandle _hShader, const Color& _diffuseColor = Color::GREEN);

		void Render2D(
			IMeshSimple2D* _pMeshSimple,
			const Matrix4x4& _matrixProjection,
			const Matrix4x4& _matrixUV,
			const ShaderHandle _hShader,
			const TextureHandle _hTexture = INVALID_HANDLE,
			const Color& _diffuseColor = Color::GREEN);
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
