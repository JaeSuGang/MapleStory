/* ����ü */
struct VertexShaderOutput
{
    float4 SVPOSITION : SV_POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

Texture2D ImageTexture : register(t0);

SamplerState ImageSampler : register(s0);

float4 PSDefault(VertexShaderOutput _Vertex) : SV_Target0
{
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    
    /* �����ȼ� ���� */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* ���� ���� */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);
    
    return float4(ColorSRGB, Color.a);
};

float4 PSBoxOutlinedGreen(VertexShaderOutput _Vertex) : SV_Target
{
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);

    /* �׵θ� ��ȯ */
    float dx = fwidth(_Vertex.UV.x);
    float dy = fwidth(_Vertex.UV.y);

    bool border = ((_Vertex.UV.x < 0.0f + dx) || (_Vertex.UV.x > 1.0f - dx) || (_Vertex.UV.y < 0.0f + dy) || (_Vertex.UV.y > 1.0f - dy));
    if (border)
        return float4(0.0f, 1.0f, 0.0f, 1.0f);

    /* �����ȼ� ���� */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* ���� ���� */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);

    return float4(ColorSRGB, Color.a);
}

float4 PSWireframe(VertexShaderOutput _Vertex) : SV_Target0
{
    float4 Color = {0.0f, 0.0f, 0.0f, 1.0f};
    return Color;
};

float4 PSGreen(VertexShaderOutput _Vertex) : SV_Target0
{
    float4 Color = { 0.0f, 1.0f, 0.0f, 1.0f };
    return Color;
};