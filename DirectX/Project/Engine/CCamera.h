#pragma once
#include "Component.h"

enum PROJ_TYPE
{
    ORTHOGRAPHIC,   // ��������
    PERSPECTIVE,    // ��������
};


class CCamera :
    public Component
{
private:
    float                   m_Far;          // �ִ� �þ�
    float                   m_FOV;          // �þ� ����(Field Of View)
    float                   m_Width;        // ���� ���ι���
    float                   m_AspectRatio;  // ��Ⱦ��
    float                   m_Scale;        // ���� ����
    PROJ_TYPE               m_ProjType;     // ���� ���

    int                     m_Priority;     // ī�޶� �켱����, 0 : MainCamera, 1 ~ SubCamera
    UINT                    m_LayerCheck;   // ī�޶� �� ���̾� ��Ʈ�� üũ(32���� ��Ʈ)


    // RenderDomain ���� �з��� GameObject
    vector<GameObject*>     m_Opaque;
    vector<GameObject*>     m_Masked;
    vector<GameObject*>     m_Transparent;


    // View ���
    // ����� �ִ� ��ǥ�� View ����� ���ؼ�, View Space �� �Ѿ�� �� �ְ� ���ִ� ��ȯ���
    Matrix                  m_matView;      // �����

    // Projection ���
    Matrix                  m_matProj;      // �������

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

