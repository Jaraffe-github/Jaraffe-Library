cbuffer constant : register(b0)
{
	float4x4 worldViewProj;
};

struct VertexIn
{
	float3 posL : POSITION;
	float3 normalL : NORMAL;
	float4 color : COLOR;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
	float3 normalW : NORMAL;
	float4 color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	vout.posH = mul(float4(vin.posL, 1.0f), worldViewProj);
	vout.normalW = mul(vin.normalL, (float3x3)worldViewProj);
	vout.color = vin.color;
	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	return pin.color;
}
