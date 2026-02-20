// コンスタントバッファ: グローバル
cbuffer global : register(b0)
{
	float4x4 matrixProjection;   // Projection行列
	float4x4 matrixView;         // View行列
	float4x4 matrixWVP;          // ワールドビュープロジェクションの合成行列
	float4x4 matrixUV;           // UV変換行列
	float4x4 matrixRotateWorld;  // ワールド回転行列
	float4 lightDirection;       // ライトの向き
	float4 lightColor;           // ライトの色
	float4 diffuseColor;         // 元の色
	float ambientValue;          // 環境光の量
	int hasTexture;              // テクスチャを持っている true / false
};
