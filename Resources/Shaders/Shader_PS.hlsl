/* 구조체 */
struct VertexShaderOutput
{
    float4 SVPOSITION : SV_POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

Texture2D ImageTexture : register(t0);

SamplerState ImageSampler : register(s0);

/* 버퍼 */
cbuffer FPSConstantsBufferStruct : register(b1)
{
    float AlphaValue;
    float NotUsed1;
    float NotUsed2;
    float NotUsed3;
    int PlaneWidth;
    int PlaneHeight;
    int WidthTileLength;
    int HeightTileLength;
};

float4 PSDefault(VertexShaderOutput _Vertex) : SV_Target0
{
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    
    /* 투명픽셀 제거 */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* 감마 보정 */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);
    
    return float4(ColorSRGB, Color.a * AlphaValue);

};

float4 PSDark(VertexShaderOutput _Vertex) : SV_Target0
{
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    
    /* 투명픽셀 제거 */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* 감마 보정 */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);
    
    /* 어둡게 */
    ColorSRGB = Color.rgb * 0.4f;
    
    return float4(ColorSRGB, Color.a * AlphaValue);

};

float4 PSTransparent(VertexShaderOutput _Vertex) : SV_Target0
{
    /* 투명픽셀 제거 */
    if (_Vertex.COLOR.a == 0.0f)
        clip(-1);
    
    return float4(0.0f, 0.0f, 0.0f, 0.0f);
};

float4 PSTile(VertexShaderOutput _Vertex) : SV_Target0
{
    uint TextureWidth, TextureHeight;
    ImageTexture.GetDimensions(TextureWidth, TextureHeight);
    
    float UVX = (_Vertex.UV.x * PlaneWidth) % WidthTileLength / WidthTileLength;
    float UVY = (_Vertex.UV.y * PlaneHeight) % HeightTileLength / HeightTileLength;

    float UVWidthStart = (TextureWidth - WidthTileLength) / 2.0f / TextureWidth;
    float UVWidthEnd = 1.0f - UVWidthStart;
    float UVHeightStart = (TextureHeight - HeightTileLength) / 2.0f / TextureHeight;
    float UVHeightEnd = 1.0f - UVHeightStart;
    
    float2 UVToApply = _Vertex.UV;
    UVToApply.x = lerp(UVWidthStart, UVWidthEnd, UVX);
    UVToApply.y = lerp(UVHeightStart, UVHeightEnd, UVY);
    
    int2 texelCoord = int2(floor(UVToApply.x * TextureWidth), floor(UVToApply.y * TextureHeight));

    
    float4 Color = ImageTexture.Sample(ImageSampler, UVToApply);

    /* 투명픽셀 제거 */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* 감마 보정 */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);

    return float4(ColorSRGB, Color.a * AlphaValue);
}

float4 PSBoxOutlinedGreen(VertexShaderOutput _Vertex) : SV_Target
{
    float4 Color = ImageTexture.Sample(ImageSampler,  _Vertex.UV.xy);

    /* 테두리 변환 */
    float dx = fwidth(_Vertex.UV.x);
    float dy = fwidth(_Vertex.UV.y);

    bool border = ((_Vertex.UV.x < 0.0f + dx) || (_Vertex.UV.x > 1.0f - dx) || (_Vertex.UV.y < 0.0f + dy) || (_Vertex.UV.y > 1.0f - dy));
    if (border)
        return float4(0.0f, 1.0f, 0.0f, 1.0f);

    /* 투명픽셀 제거 */
    if (Color.a == 0.0f)
        clip(-1);
    
    /* 감마 보정 */
    float3 ColorSRGB = pow(Color.rgb, 1.0f / 2.2f);

    return float4(ColorSRGB, Color.a * AlphaValue);
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