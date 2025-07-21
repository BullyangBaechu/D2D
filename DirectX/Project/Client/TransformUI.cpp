#include "pch.h"
#include "TransformUI.h"

#include <Engine/GameObject.h>
#include <Engine/CTransform.h>

TransformUI::TransformUI()
	: ComponentUI(COMPONENT_TYPE::TRANSFORM)
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::Tick_UI()
{
}

void TransformUI::Render_UI()
{
	OutputTitle();

	CTransform* pTransform = GetTarget()->Transform().Get();

	// Transform 컴포넌트 정보를 화면에 띄움
	Vec3 vPos = pTransform->GetRelativePos();
	Vec3 vScale = pTransform->GetRelativeScale();
	Vec3 vRot = pTransform->GetRoationDegree();

	ImGui::Text("Position");
	ImGui::SameLine(100);
	if (ImGui::DragFloat3("##Position", vPos, 1.f))
	{
		pTransform->SetRelativePos(vPos);
	}

	ImGui::Text("Scale");
	ImGui::SameLine(100);
	if (ImGui::DragFloat3("##Scale", vScale, 1.f))
	{
		pTransform->SetRelativeScale(vScale);
	}

	ImGui::Text("Rotation");
	ImGui::SameLine(100);
	if (ImGui::DragFloat3("##Rotation", vRot, 1.f))
	{
		pTransform->SetRotationDegree(vRot);
	}

	bool bIndependentScale = pTransform->GetIndependentScale();
	ImGui::Text("Independent Scale");
	ImGui::SameLine(140);
	if (ImGui::Checkbox("##CheckBox", &bIndependentScale))
	{
		pTransform->SetIndependentScale(bIndependentScale);
	}
}
