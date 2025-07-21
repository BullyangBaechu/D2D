#include "pch.h"
#include "Collider2DUI.h"

#include <Engine/GameObject.h>
#include <Engine/CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI(COMPONENT_TYPE::COLLIDER2D)
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::Tick_UI()
{
}

void Collider2DUI::Render_UI()
{
	OutputTitle();

	CCollider2D* pCollider = GetTarget()->Collider2D().Get();

	Vec2 vOffset = pCollider->GetOffset();
	Vec2 vScale = pCollider->GetScale();
	bool bIndependent = pCollider->GetIndependentScale();

	ImGui::Text("Offset");
	ImGui::SameLine(100);
	if (ImGui::DragFloat2("##Offset", vOffset))
	{
		pCollider->SetOffset(vOffset);
	}

	ImGui::Text("Scale");
	ImGui::SameLine(100);
	if(ImGui::DragFloat2("##Scale", vScale))
	{
		pCollider->SetScale(vScale);
	}

	ImGui::Text("Independent Scale");
	ImGui::SameLine(140);
	if (ImGui::Checkbox("##Independent", &bIndependent))
	{
		pCollider->SetIndependentScale(bIndependent);
	}
}