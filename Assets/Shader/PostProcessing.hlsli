Texture2D g_screenTexture : register(t0);
SamplerState g_screenSampler : register(t0);

cbuffer PostConstant : register(b1)
{
    float4 g_time_strength;
};
