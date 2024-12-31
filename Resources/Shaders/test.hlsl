
/* 구조체 */
struct Vertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

/* 버퍼 */
cbuffer FTransformConstants : register(b0)
{
    float4x4 WVP;
};

Texture2D ImageTexture : register(t0);

SamplerState ImageSampler : register(s0);


/* 쉐이더 함수 */
VertexShaderOutPut DefaultVertexShader(Vertex _Vertex)
{
    VertexShaderOutPut OutPut;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
};

float4 DefaultPixelShader(VertexShaderOutPut _Vertex) : SV_Target0
{
    // float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
    float4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    return Color;
};