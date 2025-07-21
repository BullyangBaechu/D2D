#ifndef _SPRITE
#define _SPRITE

#include "value.fx"


#define ALTAS_TEX   g_tex_0
#define LeftTop     g_vec2_0
#define Slice       g_vec2_1
#define Offset      g_vec2_2  
#define Background  g_vec2_3


struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};


VS_OUT VS_Sprite(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Sprite(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
  
    float2 vBackgroundLeftTop = (LeftTop + Slice / 2.f) - (Background / 2.f);
    float2 SpriteUV = vBackgroundLeftTop + _in.vUV * Background;
    
    // Offset º¸Á¤
    SpriteUV -= Offset;
    
    if (  LeftTop.x < SpriteUV.x && SpriteUV.x < LeftTop.x + Slice.x
        && LeftTop.y < SpriteUV.y && SpriteUV.y < LeftTop.y + Slice.y)
    {
        vOutColor = ALTAS_TEX.Sample(g_sam_1, SpriteUV);
    }
    
    else 
    {
        discard;
    }
   
    if (vOutColor.a == 0.f)
        discard;
    
    return vOutColor;
}




#endif