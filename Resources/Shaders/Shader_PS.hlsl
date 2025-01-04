/* 구조체 */
struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

Texture2D ImageTexture : register(t0);

SamplerState ImageSampler : register(s0);

float4 PSDefault(VertexShaderOutPut _Vertex) : SV_Target0
{
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    
    /* 투명픽셀 제거 */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* 감마 보정 */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);
    
    return float4(ColorSRGB, Color.a);
};

float4 PSWireframe(VertexShaderOutPut _Vertex) : SV_Target0
{
    float4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
    return Color;
};