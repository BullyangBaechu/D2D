#pragma once
#include "Component.h"

class CCollider2D :
    public Component
{
private:
    Vec3        m_Offset;           // ���� ������Ʈ�κ��� ������ ������� ��ġ
    Vec3        m_Scale;            // ���� ������Ʈ�κ��� �߰��� ����Ǵ� ����
    bool        m_IndependentScale; // ���� ������Ʈ�� ũ�⿡ ������ ������ ����
    int         m_OverlapCount;     // �浹ü�� �ٸ� �浹ü�� ��ø�Ǿ��ִ� Ƚ��
    Matrix      m_matColWorld;      // �浹ü�� ���� ����󿡼��� ��ȯ���(ũ��, ȸ��, �̵�)


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

