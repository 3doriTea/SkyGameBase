// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

// テクスチャ&サンプラーデータのグローバル変数定義
Texture2D g_texture : register(t0); // テクスチャ
SamplerState g_sampler : register(s0); // サンプラー

// コンスタントバッファ
cbuffer global
{
    float4x4 matrixProj; // プロジェクションの合成行列
    float4x4 matrixUV; // UV変換行列
    float4 color; // 塗りつぶす色
};

struct VS_OUT
{
    float4 pos : SV_POSITION; // 頂点の位置
    float4 uv : TEXCOORD; // 頂点に対応するUV座標
};

// 頂点シェーダ
VS_OUT VS(
    float4 pos : POSITION,
    float4 uv : TEXCOORD)
{
    // ピクセルシェーダに渡す情報
    VS_OUT outData;
    
    outData.pos = mul(pos, matrixProj);
    outData.uv = mul(uv, matrixUV);
    
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    return g_texture.Sample(g_sampler, inData.uv.xy);
}
