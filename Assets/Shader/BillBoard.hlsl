// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

// テクスチャ&サンプラーデータのグローバル変数定義
Texture2D g_texture : register(t0); // テクスチャ
SamplerState g_sampler : register(s0); // サンプラー

// コンスタントバッファ
cbuffer global
{
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

// 頂点シェーダ
VS_OUT VS(
    float4 pos : POSITION,
    float4 normal : NORMAL,
    float4 uv : TEXCOORD)
{
    // ピクセルシェーダに渡す情報
    VS_OUT outData;
    
    outData.pos = pos;
    mul(pos, matrixWVP);
    outData.uv = uv;
    mul(uv, matrixUV);
    
    float4 light = normalize(lightDirection);
    
    normal = mul(normal, matrixRotateWorld);
    normal.w = 0;
    
    outData.color = saturate(dot(normal, light));
    
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    return float4(0.0f, 0.0f, 1.0f, 1.0f);
    
    float4 diffuse;

    if (hasTexture)
    {
        diffuse = g_texture.Sample(g_sampler, inData.uv.xy);
    }
    else
    {
        diffuse = diffuseColor;
    }
    float4 color = diffuse * inData.color + diffuse * ambientValue;
    
    return color;
}
