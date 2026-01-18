// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

// コンスタントバッファ
cbuffer global
{
    float4x4 matrixVP; // ビュープロジェクションの合成行列
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
    float4 pos : SV_POSITION;  // 頂点の位置
};

// 頂点シェーダ
VS_OUT VS(float4 pos : POSITION)
{
    // ピクセルシェーダに渡す情報
    VS_OUT outData;
    
    outData.pos = mul(pos, matrixWVP);
    
    return outData;
}

// ピクセルシェーダ
float4 PS(VS_OUT inData) : SV_TARGET
{
    return diffuseColor;
}
