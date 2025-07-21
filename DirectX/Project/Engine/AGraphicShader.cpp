#include "pch.h"
#include "AGraphicShader.h"

#include "PathMgr.h"
#include "Device.h"

AGraphicShader::AGraphicShader()
	: Asset(ASSET_TYPE::GRAPHICSHADER)
	, m_Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_RSType(RS_TYPE::CULL_BACK)
	, m_DSType(DS_TYPE::LESS)
	, m_BSType(BS_TYPE::DEFAULT)
{
}

AGraphicShader::~AGraphicShader()
{
}


void AGraphicShader::CreateVertexShader(const wstring& _HLSFilePath, const string& _FuncName)
{
	// 쉐이더 파일 컴파일
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	ContentPath += _HLSFilePath;

	UINT Flag = D3DCOMPILE_DEBUG;
	if (FAILED(D3DCompileFromFile(ContentPath.c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _FuncName.c_str(), "vs_5_0", Flag, 0
		, m_VSBlob.GetAddressOf()
		, m_ErrBlob.GetAddressOf())))
	{
		const char* pMsg = (const char*)m_ErrBlob->GetBufferPointer();
		MessageBoxA(nullptr, pMsg, "쉐이더 컴파일 실패", MB_OK);
		return;
	}

	if (FAILED(DEVICE->CreateVertexShader(m_VSBlob->GetBufferPointer()
		, m_VSBlob->GetBufferSize()
		, nullptr, m_VS.GetAddressOf())))
	{
		MessageBox(nullptr, L"버텍스 쉐이더 생성 실패", L"쉐이더 생성 실패", MB_OK);
		return;
	}

	CreateLayout();
}

void AGraphicShader::CreatePixelShader(const wstring& _HLSFilePath, const string& _FuncName)
{
	// 경로
	wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	ContentPath += _HLSFilePath;

	UINT Flag = D3DCOMPILE_DEBUG;

	// 픽셀쉐이더 객체 생성	
	if (FAILED(D3DCompileFromFile(ContentPath.c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _FuncName.c_str(), "ps_5_0", Flag, 0
		, m_PSBlob.GetAddressOf()
		, m_ErrBlob.GetAddressOf())))
	{
		const char* pMsg = (const char*)m_ErrBlob->GetBufferPointer();
		MessageBoxA(nullptr, pMsg, "쉐이더 컴파일 실패", MB_OK);
		return;
	}

	if (FAILED(DEVICE->CreatePixelShader(m_PSBlob->GetBufferPointer()
		, m_PSBlob->GetBufferSize()
		, nullptr, m_PS.GetAddressOf())))
	{
		MessageBox(nullptr, L"픽셀 쉐이더 생성 실패", L"쉐이더 생성 실패", MB_OK);
		return;
	}
}

void AGraphicShader::CreateLayout()
{
	// InputLayout 생성
	// 정점 구조 정보 생성
	D3D11_INPUT_ELEMENT_DESC arrElement[3] = {};

	// POSITION
	arrElement[0].SemanticName = "POSITION";
	arrElement[0].SemanticIndex = 0;
	arrElement[0].AlignedByteOffset = 0;
	arrElement[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	arrElement[0].InputSlot = 0;
	arrElement[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrElement[0].InstanceDataStepRate = 0;

	arrElement[1].SemanticName = "TEXCOORD";
	arrElement[1].SemanticIndex = 0;
	arrElement[1].AlignedByteOffset = 12;
	arrElement[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	arrElement[1].InputSlot = 0;
	arrElement[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrElement[1].InstanceDataStepRate = 0;

	arrElement[2].SemanticName = "COLOR";
	arrElement[2].SemanticIndex = 0;
	arrElement[2].AlignedByteOffset = 20;
	arrElement[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	arrElement[2].InputSlot = 0;
	arrElement[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	arrElement[2].InstanceDataStepRate = 0;

	if (FAILED(DEVICE->CreateInputLayout(arrElement, 3
		, m_VSBlob->GetBufferPointer()
		, m_VSBlob->GetBufferSize()
		, m_Layout.GetAddressOf())))
	{
		MessageBox(nullptr, L"레이아웃 생성 실패", L"레이아웃 생성 실패", MB_OK);
		return;
	}
}


void AGraphicShader::Binding()
{
	CONTEXT->IASetPrimitiveTopology(m_Topology);
	CONTEXT->IASetInputLayout(m_Layout.Get());	
	CONTEXT->VSSetShader(m_VS.Get(), 0, 0);
	CONTEXT->PSSetShader(m_PS.Get(), 0, 0);

	// RasterizerState
	CONTEXT->RSSetState(Device::GetInst()->GetRSState(m_RSType).Get());

	// DepthStencilState
	CONTEXT->OMSetDepthStencilState(Device::GetInst()->GetDSState(m_DSType).Get(), 0);

	// BlendState
	CONTEXT->OMSetBlendState(Device::GetInst()->GetBSState(m_BSType).Get(), nullptr, 0xffffffff);
}