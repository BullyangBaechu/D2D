#ifndef _STD2D
#define _STD2D

#include "value.fx"

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    float4 vColor : COLOR;
};

struct VS_OUT
{
    float4 vPosition : SV_Position; // NDC 좌표정보가 들어있다
    float2 vUV : TEXCOORD;
    float4 vColor : COLOR;
};


// 정점쉐이더의 역할
// 좌표계 변환
// 로컬(모델) 스페이스 -> 월드 스페이스 -> 카메라(뷰) 스페이스 -> 투영 좌표계(NDC)
// 좌표계를 변환시킬때 적용하는 좌표계 변환 행렬
VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    // 크 * 회(자전) * 이 * 회(공)
    // 크자이공  
    
    // 오브젝트의 크기, 회전, 이동정보를 하나의 행렬에 넣는다(변환 행렬)
    // 모델 좌표에 변환행렬을 곱하면, 해당 좌표계로 이동한다.
    // 변환행렬은 4x4 행렬이고, 모델좌표는 xyz 3차원이기 때문에, 차수를 4차원으로 맞추어야 한다.
    // 동차좌표 1 (변환행렬을 적용받는 데이터가 위치 좌표성 데이터)
    //         0 (변환행렬을 적용받는 데이터가 방향성 데이터)
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.vColor = _in.vColor;
    
    return output;
}

// 정점에서 리턴한 값이, 레스터라이저를 통해서 
// 보간 (Interpolation) 된 값이 픽셀 쉐이더 입력으로 들어온다.
float4 PS_Std2D(VS_OUT _in) : SV_Target
{   
    float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    
    if(vColor.a == 0.f)
        discard;
    
    return vColor;
}

#endif