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
	// 현재 경로	
	// 프로그램이 실행된 경로
	// VisualStudio 로 실행할 경우 프로젝트 속성 '작업 디렉터리' 에 영향을 받는다.
	// 실제 실행파일 경로와 작업 디렉터리를 일치시켜서 동일한 동작을 수행할 수 있도록 한다.
	wchar_t szPath[255] = {};
	wchar_t szContent[255] = {};
	wchar_t szSolution[255] = {};

	GetCurrentDirectory(255, szPath);
	m_BinPath = szPath;

	// Bin 상위폴더 경로를 ContentPath 에 복사한다.
	int Length = (int)wcslen(szPath);
	int i = Length;
	for ( ; i > 0; --i)
	{
		if ('\\' == szPath[i])
			break;
	}		
	wmemcpy_s(szContent, 255, szPath, i);

	// \\Content\\ 를 붙여준다.
	wcscat_s(szContent, L"\\Content\\");
	m_ContentPath = szContent;


	// SolutionPath 계산하기
	--i;
	for (; i > 0; --i)
	{
		if ('\\' == szPath[i])
			break;
	}
	wmemcpy_s(szSolution, 255, szPath, i + 1);
	m_SolutionPath = szSolution;
}
