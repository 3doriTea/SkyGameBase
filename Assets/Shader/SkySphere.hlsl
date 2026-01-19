// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

// テクスチャ&サンプラーデータのグローバル変数定義
Texture2D g_texture : register(t0); // テクスチャ
SamplerState g_sampler : register(s0); // サンプラー

// コンスタントバッファ
cbuffer global
{
    float4x4 matrixProjection; // Projection行列
    float4x4 matrixView; // View行列
    float4x4 matrixWVP; // ワールドビュープロジェクションの合成行列
    float4x4 matrixUV; // UV変換行列
    float4x4 matrixRotateWorld; // ワールド回転行列
    float4 lightDirection; // ライトの向き
    float4 lightColor; // ライトの色
    float4 diffuseColor; // 元の色
    float ambientValue; // 環境光の量
    bool hasTexture; // テクスチャを持っている true / false
};

struct VS_OUT
{
    float4 pos : SV_POSITION; // 頂点の位置
    float4 uv : TEXCOORD; // 頂点に対応するUV座標
    float4 color : COLOR; // 色 / 明るさ
};

VS_OUT VS(float4 pos : POSITION, float4 normal : NORMAL, float4 uv : TEXCOORD)
{
    VS_OUT outData;
    
    // ビュー行列の平行移動部分を消してカメラと同じ位置にする
    float4x4 viewNoTranslation = matrixView;
    viewNoTranslation._41 = 0;
    viewNoTranslation._42 = 0;
    viewNoTranslation._43 = 0;
    
    // ビュー座標を求めてプロジェクション座標に変換する
    float4 viewPos = mul(float4(pos.xyz, 1.0), viewNoTranslation);
    outData.pos = mul(viewPos, matrixProjection);

    // プロジェクション座標上の z / w = 1.0 -> 最背面描画にする
    outData.pos.z = outData.pos.w;
    
    outData.uv = mul(uv, matrixUV);
    outData.color = float4(1, 1, 1, 1); // ライト計算を飛ばして白くする
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    float4 diffuse;
    
    diffuse = g_texture.Sample(g_sampler, inData.uv.xy);
    float4 color = diffuse;
    
    return color;
}
