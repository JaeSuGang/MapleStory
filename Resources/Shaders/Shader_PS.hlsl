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
    
    float2 UVToApply;
    
    float PixelWidthCoordinate = (float)(_Vertex.UV.x * PlaneWidth % WidthTileLength) / WidthTileLength;
    float StartWidthUV = (float) (TextureWidth - WidthTileLength) / 2.0f / WidthTileLength;
    float EndWidthUV = 1.0f - StartWidthUV;
    
    float PixelHeightCoordinate = (float) (_Vertex.UV.y * PlaneHeight % HeightTileLength) / HeightTileLength;
    float StartHeightUV = (float) (TextureHeight- HeightTileLength) / 2.0f / HeightTileLength;
    float EndHeightUV = 1.0f - StartHeightUV;
    
    UVToApply.x = PixelWidthCoordinate * (EndWidthUV - StartWidthUV) + StartWidthUV;
    UVToApply.y = PixelHeightCoordinate * (EndHeightUV - StartHeightUV) + StartHeightUV;
    
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