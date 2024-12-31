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

cbuffer FTransformConstants : register(b0)
{
    float4x4 WVP;
};

VertexShaderOutPut DefaultVertexShader(Vertex _Vertex)
{
    VertexShaderOutPut OutPut;
    
    //_Vertex.POSITION.x += (1.0f - Pivot.x) - 0.5f;
    //_Vertex.POSITION.y += (1.0f - Pivot.y) - 0.5f;
	
    //OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
    //OutPut.UV.x = (_Vertex.UV.x * CuttingSize.x) + CuttingPos.x;
    //OutPut.UV.y = (_Vertex.UV.y * CuttingSize.y) + CuttingPos.y;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
};