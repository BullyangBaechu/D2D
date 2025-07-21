#include "pch.h"
#include "Device.h"

Device::Device()
	: m_OutputWnd(nullptr)	
	, m_ViewPort{}
{}

Device::~Device()
{}

int Device::Init(HWND _hWnd, Vec2 _Resolution)
{
	m_OutputWnd = _hWnd;
	m_RenderResolution = _Resolution;

	// ID3D11Device, ID3D11DeviceContext 생성
	UINT Flag = 0;
	D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;
#ifdef _DEBUG
	Flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	if(FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
								, nullptr , Flag , nullptr , 0
								, D3D11_SDK_VERSION
								, m_Device.GetAddressOf(), &FeatureLevel
								, m_Context.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SwapChain 및 렌더타겟 생성
	if (FAILED(CreateSwapChain()))
	{
		MessageBox(nullptr, L"SwapChain 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 렌더타겟, 깊이타겟
	if (FAILED(CreateTargetTexture()))
	{		
		return E_FAIL;
	}

	// View 생성 및 출력(OM)으로 연결
	if (FAILED(CreateView()))
	{
		MessageBox(nullptr, L"View 생성 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// ViewPort 설정
	// RenderTarget 의 이미지를 출력시킬 윈도우 영역 지정
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width	= m_RenderResolution.x;
	m_ViewPort.Height	= m_RenderResolution.y;
	m_ViewPort.MinDepth = 0.f;
	m_ViewPort.MaxDepth = 1.f;
	m_Context->RSSetViewports(1, &m_ViewPort);

	// RasterizerState 생성
	CreateRasterizerState();

	// DepthStencilState 생성
	CreateDepthStencilState();

	// BlendState 생성
	CreateBlendState();

	// 상수버퍼 생성
	CreateConstBuffer();

	// Sampler 생성
	CreateSampler();
	
	return S_OK;
}

void Device::ClearTarget(Vec4 _ClearColor)
{
	m_Context->ClearRenderTargetView(m_RTV.Get(), _ClearColor);
	m_Context->ClearDepthStencilView(m_DSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Device::Present()
{
	m_SwapChain->Present(0, 0);
}

int Device::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC Desc = {};

	// 렌더타겟 텍스쳐 정보
	Desc.BufferCount = 1;								// 버퍼(타겟 텍스쳐) 개수
	Desc.BufferDesc.Width = (UINT)m_RenderResolution.x; // 해상도
	Desc.BufferDesc.Height = (UINT)m_RenderResolution.y;// 해상도
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 텍스쳐 사용 용도(렌더타겟)
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// 렌더타겟 픽셀 포맷

	// 타겟 갱신 속도(모니터 주사율에 맞춰서 초당 60회)
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		
	Desc.Windowed = true;			 // 창모드
	Desc.OutputWindow = m_OutputWnd; // 출력 윈도우

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Flags = 0;
	
	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 장면 유지 X

	// GUID, UUID 로 SwapChain 생성시킬 수 있는 객체를 만들어서 SwapChain 을 생성한다.

	ComPtr<IDXGIDevice> DXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	ComPtr<IDXGIFactory> pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)DXGIDevice.GetAddressOf());
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
	pAdapter->GetParent(__uuidof(pFactory), (void**)pFactory.GetAddressOf());

	if (FAILED(pFactory->CreateSwapChain(m_Device.Get()
										, &Desc
										, m_SwapChain.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int Device::CreateTargetTexture()
{
	// 1. RenderTarget Texture
	// 스왚체인이 보유하고 있는 RenderTarget 주소값을 받아온다.
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_RenderTarget.GetAddressOf());

	// 2. DepthStencil Texture
	// - 깊이 + 스텐실 기록하는 버퍼
	D3D11_TEXTURE2D_DESC Desc = {};

	// 해상도는 RenderTarget 과 반드시 일치해야한다.
	Desc.Width	= m_RenderResolution.x;
	Desc.Height = m_RenderResolution.y;
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.ArraySize = 1;
	Desc.MipLevels = 1; // 저해상도 이미지 생성 레벨(개수) 1은 원본만

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.MiscFlags = 0;

	// 사용 용도(View)
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// CPU 접근 X
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.CPUAccessFlags = 0;

	if (FAILED(m_Device->CreateTexture2D(&Desc, nullptr, m_DepthStencilTarget.GetAddressOf())))
	{
		MessageBox(nullptr, L"DepthStencil 텍스쳐 생성 실패", L"Target 텍스쳐 생성 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

int Device::CreateView()
{
	// View 의 종류
	// RenderTargetView, DepthStencilView, ShaderResourceView, UnorderedAccessView
	// 리소스의 용도를 증명하는 역할

	// RenderTargetView 생성
	if (FAILED(m_Device->CreateRenderTargetView(m_RenderTarget.Get(), nullptr, m_RTV.GetAddressOf())))
	{
		return E_FAIL;
	}
	
	// DepthStencilView 생성
	if (FAILED(m_Device->CreateDepthStencilView(m_DepthStencilTarget.Get(), nullptr, m_DSV.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int Device::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC Desc = {};

	// CULL_BACK : 기본옵션
	m_RSState[(UINT)RS_TYPE::CULL_BACK] = nullptr;

	// CULL_FONT : 뒷면 렌더링
	Desc.CullMode = D3D11_CULL_FRONT;
	Desc.FillMode = D3D11_FILL_SOLID;	
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_FRONT].GetAddressOf());

	// CULL_FONT : 앞면 뒷면 모두 렌더링
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::CULL_NONE].GetAddressOf());

	// WIRE_FRAME : 정점사이를 잇는 뼈대만 렌더링
	Desc.CullMode = D3D11_CULL_NONE;
	Desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&Desc, m_RSState[(UINT)RS_TYPE::WIRE_FRAME].GetAddressOf());


	return S_OK;
}

int Device::CreateBlendState()
{
	D3D11_BLEND_DESC Desc = {};

	// Default 
	m_BSState[(UINT)BS_TYPE::DEFAULT] = nullptr;


	// AlphaBlend
	Desc.AlphaToCoverageEnable = false;
	Desc.IndependentBlendEnable = false;

	Desc.RenderTarget[0].BlendEnable = true;
	Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // 가산혼합
	Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // SrcRGB * SrcAlpha
	Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // DstRGB * (1.f - SrcAlpha)

	Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO; // SrcAlpha * 0.f
	Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; // DstAlpha * 0.f;

	DEVICE->CreateBlendState(&Desc, m_BSState[(UINT)BS_TYPE::ALPHABLEND].GetAddressOf());


	return S_OK;
}

int Device::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC Desc = {};

	// LESS
	m_DSState[(UINT)DS_TYPE::LESS] = nullptr;

	// Greater
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_GREATER;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.StencilEnable = false;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::GREATER].GetAddressOf());

	// No Test
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	Desc.StencilEnable = false;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST].GetAddressOf());

	// NO_WRITE
	Desc.DepthEnable = true;
	Desc.DepthFunc = D3D11_COMPARISON_LESS;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	Desc.StencilEnable = false;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_WRITE].GetAddressOf());
	
	// No Test, No Write
	Desc.DepthEnable = false;
	Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DEVICE->CreateDepthStencilState(&Desc, m_DSState[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());


	return S_OK;
}

int Device::CreateConstBuffer()
{
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = new ConstBuffer(CB_TYPE::TRANSFORM);
	m_arrCB[(UINT)CB_TYPE::TRANSFORM]->Create(sizeof(tTransform));

	m_arrCB[(UINT)CB_TYPE::MATERIAL] = new ConstBuffer(CB_TYPE::MATERIAL);
	m_arrCB[(UINT)CB_TYPE::MATERIAL]->Create(sizeof(tMtrlConst));

	return S_OK;
}

void Device::CreateSampler()
{
	D3D11_SAMPLER_DESC Desc = {};

	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.Filter = D3D11_FILTER_ANISOTROPIC; // 이방성 필터링, 
	Desc.MinLOD = 0;
	Desc.MaxLOD = 0;
	DEVICE->CreateSamplerState(&Desc, m_Sampler[0].GetAddressOf());
	CONTEXT->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());

	Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // Mip 필터링 
	Desc.MinLOD = 0;
	Desc.MaxLOD = 0;
	DEVICE->CreateSamplerState(&Desc, m_Sampler[1].GetAddressOf());
	CONTEXT->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());


	Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	Desc.Filter = D3D11_FILTER_ANISOTROPIC; // 이방성 필터링 
	Desc.MinLOD = 0;
	Desc.MaxLOD = 0;
	DEVICE->CreateSamplerState(&Desc, m_Sampler[2].GetAddressOf());
	CONTEXT->PSSetSamplers(2, 1, m_Sampler[2].GetAddressOf());
}
