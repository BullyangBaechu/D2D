#pragma once

#include "global.h"

class PathMgr
	: public singleton<PathMgr>
{
	SINGLE(PathMgr);
private:
	wstring m_SolutionPath;	// 솔루션 경로
	wstring m_ContentPath;		// 리소스들이 들어있는 Content 폴더 경로
	wstring m_BinPath;			// 실행파일이 있는 Bin 폴더 경로
	
public:
	void Init();

	const wstring& GetSolutionPath() { return m_SolutionPath; }
	const wstring& GetBinPath() { return m_BinPath; }
	const wstring& GetContentPath() { return m_ContentPath; }
};

