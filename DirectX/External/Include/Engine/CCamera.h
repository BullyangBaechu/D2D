#pragma once
#include "Component.h"

enum PROJ_TYPE
{
    ORTHOGRAPHIC,   // 직교투영
    PERSPECTIVE,    // 원근투영
};


class CCamera :
    public Component
{
private:
    float                   m_Far;          // 최대 시야
    float                   m_FOV;          // 시야 각도(Field Of View)
    float                   m_Width;        // 투영 가로범위
    float                   m_AspectRatio;  // 종횡비
    float                   m_Scale;        // 투영 배율
    PROJ_TYPE               m_ProjType;     // 투영 방식

    int                     m_Priority;     // 카메라 우선순위, 0 : MainCamera, 1 ~ SubCamera
    UINT                    m_LayerCheck;   // 카메라가 볼 레이어 비트값 체크(32개의 비트)


    // RenderDomain 으로 분류한 GameObject
    vector<GameObject*>     m_Opaque;
    vector<GameObject*>     m_Masked;
    vector<GameObject*>     m_Transparent;


    // View 행렬
    // 월드상에 있는 좌표가 View 행렬을 곱해서, View Space 로 넘어올 수 있게 해주는 변환행렬
    Matrix                  m_matView;      // 뷰행렬

    // Projection 행렬
    Matrix                  m_matProj;      // 투영행렬

public:
	GET_SET(float, Far);
	GET_SET(float, FOV);
	GET_SET(float, Width);
	GET_SET(float, AspectRatio);
	GET_SET(float, Scale);
	GET_SET(PROJ_TYPE, ProjType);

    int GetPriority() { return m_Priority; }
    void SetPriority(int _Priority);

    void LayerCheck(UINT _LayerIdx);
    void LayerCheckAll() { m_LayerCheck = 0xffffffff; }
    void LayerCheckClear() { m_LayerCheck = 0; }

public:
    virtual void FinalTick() override;
    void Render();


private:
    void SortObject();


public:
    CLONE(CCamera);
    CCamera();
    CCamera(const CCamera& _Origin);
    virtual ~CCamera();

    friend class RenderMgr;
};

