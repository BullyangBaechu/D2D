#pragma once
#include "Component.h"

class CCollider2D :
    public Component
{
private:
    Vec3        m_Offset;           // 소유 오브젝트로부터 떨어진 상대적인 위치
    Vec3        m_Scale;            // 소유 오브젝트로부터 추가로 적용되는 배율
    bool        m_IndependentScale; // 소유 오브젝트의 크기에 영향을 받을지 말지
    int         m_OverlapCount;     // 충돌체가 다른 충돌체와 충첩되어있는 횟수
    Matrix      m_matColWorld;      // 충돌체의 최종 월드상에서의 변환행렬(크기, 회전, 이동)


public:
    Vec2 GetOffset() { return Vec2(m_Offset.x, m_Offset.y); }
    void SetOffset(Vec2 _Offset) { m_Offset = Vec3(_Offset.x, _Offset.y, 0.f); }

    Vec2 GetScale() { return Vec2(m_Scale.x, m_Scale.y); }
    void SetScale(Vec2 _Scale) { m_Scale = Vec3(_Scale.x, _Scale.y, 1.f); }

    GET_SET(bool, IndependentScale);
    const Matrix& GetWorldMat() { return m_matColWorld; }

public:
    virtual void FinalTick() override;

private:
    void BeginOverlap(CCollider2D* _Other);
    void Overlap(CCollider2D* _Other);
    void EndOverlap(CCollider2D* _Other);


public:
    CLONE(CCollider2D);
    CCollider2D();
    CCollider2D(const CCollider2D& _Origin);
    virtual ~CCollider2D();

    friend class CollisionMgr;
};

