#pragma once

#include "global.h"

class PathMgr
	: public singleton<PathMgr>
{
	SINGLE(PathMgr);
private:
	wstring m_SolutionPath;	// �ַ�� ���
	wstring m_ContentPath;		// ���ҽ����� ����ִ� Content ���� ���
	wstring m_BinPath;			// ���������� �ִ� Bin ���� ���
	
public:
	void Init();

	const wstring& GetSolutionPath() { return m_SolutionPath; }
	const wstring& GetBinPath() { return m_BinPath; }
	const wstring& GetContentPath() { return m_ContentPath; }
};

