#pragma once
#include "Asset.h"

#include "AGraphicShader.h"
#include "ATexture.h"

// 어떻게 렌더링 할 것인지(GraphicShader)
// 
class AMaterial :
    public Asset
{
private:
    Ptr<AGraphicShader>     m_Shader;
    tMtrlConst              m_Const;
    Ptr<ATexture>           m_arrTex[TEX_END];
    RENDER_DOMAIN           m_Domain;


public:
    GET_SET(Ptr<AGraphicShader>, Shader);
    void SetTexture(TEX_PARAM _TexParam, Ptr<ATexture> _Tex) { m_arrTex[_TexParam] = _Tex; }

    template<typename T>
    void SetScalar(SCALAR_PARAM _ScalarParam, const T& _Data);

    GET_SET(RENDER_DOMAIN, Domain);

public:
    void Binding();
    virtual int Save(const wstring& _FilePath) override { return S_OK; };
    virtual int Load(const wstring& _FilePath) override { return S_OK; };

public:
    CLONE(AMaterial)
    AMaterial();
    virtual ~AMaterial();
};

template<typename T>
void AMaterial::SetScalar(SCALAR_PARAM _ScalarParam, const T& _Data)
{
    switch (_ScalarParam )
    {
    case INT_0:
    case INT_1:
    case INT_2:
    case INT_3:
    {
        if constexpr (std::is_same_v<T, int>)
        {
            m_Const.iArr[_ScalarParam] = _Data;
        }        
    }
        break;
    case FLOAT_0:
    case FLOAT_1:
    case FLOAT_2:
    case FLOAT_3:
    {
        if constexpr (std::is_same_v<T, float>)
        {
            m_Const.fArr[_ScalarParam - FLOAT_0] = _Data;
        }        
    }
        break;
    case VEC2_0:
    case VEC2_1:
    case VEC2_2:
    case VEC2_3:
    {
        if constexpr (std::is_same_v<T, Vec2>)
        {
            m_Const.v2Arr[_ScalarParam - VEC2_0] = _Data;
        }
    }        
        break;
    case VEC4_0:
    case VEC4_1:
    case VEC4_2:
    case VEC4_3:
    {
        if constexpr (std::is_same_v<T, Vec4>)
        {
            m_Const.v4Arr[_ScalarParam - VEC4_0] = _Data;
        }
    }
        break;
    case MAT_0:
    case MAT_1:
    {
        if constexpr (std::is_same_v<T, Matrix>)
        {
            m_Const.matArr[_ScalarParam - MAT_0] = _Data;
        }
    }       
        break;
    }
}
