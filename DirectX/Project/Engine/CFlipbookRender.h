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
    UINT                    m_SpriteIdx;    // 현재 재생중인 Sprite

    int                     m_RepeatCount;  // -1 : 무한반복
    bool                    m_Finish;       // 1회 재생이 끝나면 true

    float                   m_FPS;          // 초당 재생횟수(재생속도)

    float                   m_Time;         // 누적시간 체크

public:
    void AddFlipbook(UINT _Idx, Ptr<AFlipbook> _Flipbook);
    Ptr<AFlipbook> GetFlipbook(UINT _Idx) { return m_vecFlipbook[_Idx]; }

    // _RepeatCount  PLAY_INF : 무한반복 
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

