#pragma once

#include "CRenderComponent.h"
#include "AFlipbook.h"

#define PLAY_LOOP -1

class CFlipbookRender :
    public CRenderComponent
{
private:
    vector<Ptr<AFlipbook>>  m_vecFlipbook;

    Ptr<AFlipbook>          m_CurFlipbook;
    UINT                    m_SpriteIdx;    // ���� ������� Sprite

    int                     m_RepeatCount;  // -1 : ���ѹݺ�
    bool                    m_Finish;       // 1ȸ ����� ������ true

    float                   m_FPS;          // �ʴ� ���Ƚ��(����ӵ�)

    float                   m_Time;         // �����ð� üũ

public:
    void AddFlipbook(UINT _Idx, Ptr<AFlipbook> _Flipbook);
    Ptr<AFlipbook> GetFlipbook(UINT _Idx) { return m_vecFlipbook[_Idx]; }

    // _RepeatCount  PLAY_INF : ���ѹݺ� 
    void Play(UINT _Idx, float _FPS, int _RepeatCount);

private:
    void CreateMaterial();

public:
    virtual void FinalTick() override;
    virtual void Render() override;

public:
    CLONE(CFlipbookRender);
    CFlipbookRender();
    virtual ~CFlipbookRender();
};

