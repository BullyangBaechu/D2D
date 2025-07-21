#include "pch.h"
#include "Inspector.h"

#include <Engine/LevelMgr.h>

#include "TransformUI.h"
#include "CameraUI.h"
#include "Collider2DUI.h"

Inspector::Inspector()
	: EUI("Inspector")
	, m_arrComUI{}
{
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]->SetAsChildSize(ImVec2(0.f, 130.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM]);

	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]->SetAsChildSize(ImVec2(0.f, 200.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA]);

	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]->SetAsChildSize(ImVec2(0.f, 100.f));
	AddChildUI(m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D]);


}

Inspector::~Inspector()
{
}

void Inspector::Tick_UI()
{
	if (nullptr == m_TargetObject)
	{
		SetTargetObject(LevelMgr::GetInst()->FindObjectByName(L"Player"));
	}
}

void Inspector::Render_UI()
{
	if (nullptr == m_TargetObject)
		return;

	string ObjectName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
	ImGui::Text("Name");
	ImGui::SameLine(100);
	ImGui::InputText("##InputText", (char*)ObjectName.c_str(), ObjectName.length() + 1, ImGuiInputTextFlags_ReadOnly);
}

void Inspector::SetTargetObject(GameObject* _Object)
{
	m_TargetObject = _Object;

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr != m_arrComUI[i])
			m_arrComUI[i]->SetTarget(_Object);
	}
}