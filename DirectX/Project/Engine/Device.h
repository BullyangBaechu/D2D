#pragma once


#include "ConstBuffer.h"

// Dx9
// Dx11 객체 매니저
// GPU 제어
class Device
	: public singleton<Device>
{
	SINGLE(Device)
private:
	HWND							m_OutputWnd;
	Vec2							m_RenderResolution;

	ComPtr<ID3D11Device>			m_Device;   // GPU 메모리 할당, 객체 생성
	ComPtr<ID3D11DeviceContext>		m_Context;	// GPU 동작, 명령, 렌더링
	ComPtr<IDXGISwapChain>			m_SwapChain;

	ComPtr<ID3D11Texture2D>			m_RenderTarget;
	ComPtr<ID3D11Texture2D>			m_DepthStencilTarget;

	ComPtr<ID3D11RenderTargetView>	m_RTV;
	ComPtr<ID3D11DepthStencilView>	m_DSV;

	D3D11_VIEWPORT					m_ViewPort;

	ComPtr<ID3D11SamplerState>		m_Sampler[3];


	ComPtr<ID3D11RasterizerState>	m_RSState[(UINT)RS_TYPE::END];
	ComPtr<ID3D11BlendState>		m_BSState[(UINT)BS_TYPE::END];
	ComPtr<ID3D11DepthStencilState>	m_DSState[(UINT)DS_TYPE::END];


	Ptr<ConstBuffer>				m_arrCB[(UINT)CB_TYPE::CB_END];

public:
	Vec2 GetRenderResolution() { return m_RenderResolution; }
	void TargetBinding() { m_Context->OMSetRenderTargets(1, m_RTV.GetAddressOf(), m_DSV.Get()); }

public:
	int Init(HWND _hWnd, Vec2 _Resolution);
	void ClearTarget(Vec4 _ClearColor);
	void Present();

	const Ptr<ConstBuffer>& GetConstBuffer(CB_TYPE _Type) { return m_arrCB[(UINT)_Type]; }
	const ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_RSState[(UINT)_Type]; }
	const ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_DSState[(UINT)_Type]; }
	const ComPtr<ID3D11BlendState> GetBSState(BS_TYPE _Type) { return m_BSState[(UINT)_Type]; }

private:
	int CreateSwapChain();
	int CreateTargetTexture();
	int CreateView();

	int CreateRasterizerState();
	int CreateBlendState();
	int CreateDepthStencilState();

	int CreateConstBuffer();
	void CreateSampler();

public:
	ComPtr<ID3D11Device> Get11Device() { return m_Device; }
	ComPtr<ID3D11DeviceContext> Get11DeviceContext() { return m_Context; }
};

