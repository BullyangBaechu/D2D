#pragma once
#include "Component.h"


class CTransform :
    public Component
{
private:
    Vec3    m_RelativePos;          // 부모(or 월드) 로부터 상대적 위치
    Vec3    m_RelativeScale;        // 부모(or 월드) 로부터 상대적 크기
    Vec3    m_RelativeRot;          // 부모(or 월드) 로부터 상대적 회전

    Vec3    m_RelativeDir[(UINT)DIR::END];  // 부모를 고려하지않은 오브젝트 고유 로컬 방향벡터
    Vec3    m_WorldDir[(UINT)DIR::END];     // 월드상에서의 최종 방향벡터(부모의 상태까지 적용한)

    Matrix  m_matWorld;             // 모든 상태를 합친 월드행렬(부모의 상태까지 누적)

    bool    m_IndependentScale;     // 부모로부터 크기를 물려받지 않음, 자식은 독립적인 스케일(배율)을 가짐

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

