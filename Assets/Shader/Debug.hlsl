// REF: https://learn.microsoft.com/ja-jp/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics

// コンスタントバッファ
cbuffer global
{
    float4x4 matrixWVP;  // ワールドビュープロジェクションの合成行列
    float4x4 matrixRotateWorld;  // ワールド回転行列
    float4 debugColor;  // デバッグカラー
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
    return debugColor;
}
