#include "pch.h"
#include "CMeshRender.h"

#include "GameObject.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::FinalTick()
{
}

void CMeshRender::Render()
{
	Transform()->Binding();

	GetMaterial()->Binding();	

	GetMesh()->Render();
}