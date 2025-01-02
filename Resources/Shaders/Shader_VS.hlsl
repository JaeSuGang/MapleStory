
/* ����ü */
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

/* ���� */
cbuffer FTransformConstants : register(b0)
{
    float4x4 WVP;
};


/* ���̴� �Լ� */
VertexShaderOutPut VSMain(Vertex _Vertex)
{
    VertexShaderOutPut OutPut;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.UV = _Vertex.UV;
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
};