#include "pch.h"
#include "CameraUI.h"

CameraUI::CameraUI()
	: ComponentUI(COMPONENT_TYPE::CAMERA)
{
}

CameraUI::~CameraUI()
{
}

void CameraUI::Tick_UI()
{
}

void CameraUI::Render_UI()
{
	OutputTitle();

	CCamera* pCam = GetTarget()->Camera().Get();

	PROJ_TYPE Type = pCam->GetProjType();

	ImGui::Text("Projection");
	ImGui::SameLine(120);

	const char* items[] = { "Orthographic", "Perspective" };
	int item_current = Type;
	if (ImGui::Combo("##Projection", &item_current, items, 2))
	{
		pCam->SetProjType((PROJ_TYPE)item_current);
	}

	// 카메라 우선순위
	int Priority = pCam->GetPriority();
	ImGui::Text("Priority");
	ImGui::SameLine(120);
	if (ImGui::InputInt("##Priority", &Priority))
	{
		if (Priority < 0)
			Priority = 0;
		else
			pCam->SetPriority(Priority);
	}

	// Far
	float Far = pCam->GetFar();
	ImGui::Text("Far");
	ImGui::SameLine(120);
	if (ImGui::InputFloat("##Far", &Far, 0.f))
	{
		pCam->SetFar(Far);
	}


	// OrthoGraphic: Scale, Width
	ImGui::BeginDisabled(Type != PROJ_TYPE::ORTHOGRAPHIC);

	float Scale = pCam->GetScale();
	ImGui::Text("Scale");
	ImGui::SameLine(120);
	if (ImGui::InputFloat("##Scale", &Scale, 0.f))
	{
		pCam->SetScale(Scale);
	}

	float Width = pCam->GetWidth();
	ImGui::Text("Width");
	ImGui::SameLine(120);
	if (ImGui::InputFloat("##Width", &Width, 0.f))
	{
		pCam->SetWidth(Width);
	}

	ImGui::EndDisabled();


	// AspectRatio
	float AspectRatio = pCam->GetAspectRatio();
	ImGui::Text("AspectRatio");
	ImGui::SameLine(120);
	if (ImGui::InputFloat("##AspectRatio", &AspectRatio, 0.f))
	{
		pCam->SetAspectRatio(AspectRatio);
	}
	
	//FOV; // Perspective
	ImGui::BeginDisabled(Type != PROJ_TYPE::PERSPECTIVE);

	float FOV = pCam->GetFOV();
	FOV = (FOV / XM_PI) * 180.f;

	ImGui::Text("FOV");
	ImGui::SameLine(120);
	if (ImGui::InputFloat("##FOV", &FOV, 0.f))
	{
		FOV = (FOV / 180.f) * XM_PI;
		pCam->SetFOV(FOV);
	}

	ImGui::EndDisabled();

	// m_LayerCheck
}