#include "pch.h"
#include "PathMgr.h"

PathMgr::PathMgr()
	: m_SolutionPath{}
	, m_ContentPath{}
	, m_BinPath{}
{
}

PathMgr::~PathMgr()
{
}

void PathMgr::Init()
{
	// ���� ���	
	// ���α׷��� ����� ���
	// VisualStudio �� ������ ��� ������Ʈ �Ӽ� '�۾� ���͸�' �� ������ �޴´�.
	// ���� �������� ��ο� �۾� ���͸��� ��ġ���Ѽ� ������ ������ ������ �� �ֵ��� �Ѵ�.
	wchar_t szPath[255] = {};
	wchar_t szContent[255] = {};
	wchar_t szSolution[255] = {};

	GetCurrentDirectory(255, szPath);
	m_BinPath = szPath;

	// Bin �������� ��θ� ContentPath �� �����Ѵ�.
	int Length = (int)wcslen(szPath);
	int i = Length;
	for ( ; i > 0; --i)
	{
		if ('\\' == szPath[i])
			break;
	}		
	wmemcpy_s(szContent, 255, szPath, i);

	// \\Content\\ �� �ٿ��ش�.
	wcscat_s(szContent, L"\\Content\\");
	m_ContentPath = szContent;


	// SolutionPath ����ϱ�
	--i;
	for (; i > 0; --i)
	{
		if ('\\' == szPath[i])
			break;
	}
	wmemcpy_s(szSolution, 255, szPath, i + 1);
	m_SolutionPath = szSolution;
}
