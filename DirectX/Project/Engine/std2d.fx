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
    float4 vPosition : SV_Position; // NDC ��ǥ������ ����ִ�
    float2 vUV : TEXCOORD;
    float4 vColor : COLOR;
};


// �������̴��� ����
// ��ǥ�� ��ȯ
// ����(��) �����̽� -> ���� �����̽� -> ī�޶�(��) �����̽� -> ���� ��ǥ��(NDC)
// ��ǥ�踦 ��ȯ��ų�� �����ϴ� ��ǥ�� ��ȯ ���
VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    // ũ * ȸ(����) * �� * ȸ(��)
    // ũ���̰�  
    
    // ������Ʈ�� ũ��, ȸ��, �̵������� �ϳ��� ��Ŀ� �ִ´�(��ȯ ���)
    // �� ��ǥ�� ��ȯ����� ���ϸ�, �ش� ��ǥ��� �̵��Ѵ�.
    // ��ȯ����� 4x4 ����̰�, ����ǥ�� xyz 3�����̱� ������, ������ 4�������� ���߾�� �Ѵ�.
    // ������ǥ 1 (��ȯ����� ����޴� �����Ͱ� ��ġ ��ǥ�� ������)
    //         0 (��ȯ����� ����޴� �����Ͱ� ���⼺ ������)
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.vColor = _in.vColor;
    
    return output;
}

// �������� ������ ����, �����Ͷ������� ���ؼ� 
// ���� (Interpolation) �� ���� �ȼ� ���̴� �Է����� ���´�.
float4 PS_Std2D(VS_OUT _in) : SV_Target
{   
    float4 vColor = g_tex_0.Sample(g_sam_1, _in.vUV);
    
    if(vColor.a == 0.f)
        discard;
    
    return vColor;
}

#endif