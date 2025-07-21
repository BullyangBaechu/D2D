#pragma once
#include "Component.h"


class CTransform :
    public Component
{
private:
    Vec3    m_RelativePos;          // �θ�(or ����) �κ��� ����� ��ġ
    Vec3    m_RelativeScale;        // �θ�(or ����) �κ��� ����� ũ��
    Vec3    m_RelativeRot;          // �θ�(or ����) �κ��� ����� ȸ��

    Vec3    m_RelativeDir[(UINT)DIR::END];  // �θ� ����������� ������Ʈ ���� ���� ���⺤��
    Vec3    m_WorldDir[(UINT)DIR::END];     // ����󿡼��� ���� ���⺤��(�θ��� ���±��� ������)

    Matrix  m_matWorld;             // ��� ���¸� ��ģ �������(�θ��� ���±��� ����)

    bool    m_IndependentScale;     // �θ�κ��� ũ�⸦ �������� ����, �ڽ��� �������� ������(����)�� ����

public:
    GET_SET(Vec3, RelativePos);
    GET_SET(Vec3, RelativeScale);
    GET_SET(Vec3, RelativeRot);
    GET_SET(bool, IndependentScale);
    Vec3 GetRoationDegree() {return (m_RelativeRot / XM_PI) * 180.f; }
    void SetRotationDegree(Vec3 _Degree) {  m_RelativeRot = (_Degree / 180.f) * XM_PI;}
    Vec3 GetRelativeDir(DIR _Dir) { return m_RelativeDir[(UINT)_Dir]; }

    Vec3 GetWorldDir(DIR _Dir) { return m_WorldDir[(UINT)_Dir]; }

    Vec3 GetWorldScale();

    const Matrix& GetWorldMat() { return m_matWorld; }
    void SetWorldMat(const Matrix& _matWorld) { m_matWorld = _matWorld; }

public:
    virtual void FinalTick() override;

public:
    void Binding();

    CLONE(CTransform);
public:
    CTransform();
    virtual ~CTransform();
};

