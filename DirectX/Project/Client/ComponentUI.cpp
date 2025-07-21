#include "pch.h"
#include "ComponentUI.h"

#include <Engine/GameObject.h>


ComponentUI::ComponentUI(COMPONENT_TYPE _Type)
	: EUI(COMPONENT_TYPE_STR[(UINT)_Type])
	, m_TargetObject(nullptr)
	, m_Type(_Type)
{
}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::SetTarget(GameObject* _Target)
{
	m_TargetObject = _Target;

	if (nullptr == m_TargetObject)
		SetActive(false);
	else if(m_TargetObject->GetComponent(m_Type).Get())
		SetActive(true);
	else
		SetActive(false);
}

void ComponentUI::OutputTitle()
{
	// 구분선
	ImGui::Separator();

	// 타이틀
	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.2f, 0.4f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.2f, 0.4f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.2f, 0.4f, 1.f));
	ImGui::Button(GetString(m_Type));
	ImGui::PopStyleColor(3);
	ImGui::PopID();

	ImGui::Spacing();
}
