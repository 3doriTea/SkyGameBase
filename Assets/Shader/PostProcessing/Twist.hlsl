#include "../PostProcessing.hlsli"
#include "../Common2D.hlsli"

VS_OUT VS(
    float4 pos : POSITION,
    float4 uv  : TEXCOORD)
{
    VS_OUT outData;
    
    outData.pos = mul(pos, matrixProj);
    outData.uv = mul(uv, matrixUV);

    return outData;
}

float4 PS(VS_OUT inData) : SV_TARGET
{
    float2 uv = inData.uv.xy - float2(0.5f, 0.5f);
    float dist = length(uv);  // 中心からの距離
    
    // 渦の計算
    float angle = sin(g_time_strength[0] * g_time_strength[1] * (1.0f - dist));
    
    float cosAng = cos(angle);
    float sinAng = sin(angle);
    
    // よく出てくる回転行列
    float2 rotationUV;
    rotationUV.x = uv.x * cosAng - uv.y * sinAng;
    rotationUV.y = uv.x * sinAng - uv.y * cosAng;
    
    return g_screenTexture.Sample(g_screenSampler, rotationUV + float2(0.5f, 0.5f));

}
