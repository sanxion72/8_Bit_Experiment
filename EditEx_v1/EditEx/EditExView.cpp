
#include "stdafx.h"
#include "EditExView.h"

#include <iostream>
#include <string>

using std::string;
using std::ifstream;

const TCHAR* XTE_EXT = _T(".xte");

CEditExView::CEditExView()
{
	memset(m_path, 0, sizeof m_path);
	memset(m_name, 0, sizeof m_name);	
}

CEditExView::~CEditExView()
{
}

bool CEditExView::Load(const TCHAR* sPath, UINT uiFlag)
{
	if (DoLoad(sPath, uiFlag)) 
	{
		SetNamePath(sPath);
		ATLASSERT(lstrlen(m_path));
		SetModify(FALSE);
		return true;
	}
	return false;	
}

bool CEditExView::Save(const TCHAR* sPath, UINT uiFlag)
{
	if (DoSave(sPath, uiFlag)) 
	{
		SetNamePath(sPath);
		ATLASSERT(lstrlen(m_path));
		SetModify(FALSE);
		return true;
	}
	return false;	
}

void CEditExView::SetNamePath(const TCHAR* path)
{	
	lstrcpy(m_path, path);
	const TCHAR* name = RFind(m_path, _T('\\'));
	if (name) lstrcpy(m_name, ++name);
}

bool CEditExView::DoLoad(const TCHAR* sPath, UINT uiFlag)
{
	HANDLE hFile = ::CreateFile(sPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 0);
	if(INVALID_HANDLE_VALUE == hFile) return false;

	DWORD dwSizeLow = GetFileSize(hFile, 0);	
	char* pbBuff = (char*)malloc(dwSizeLow+1);
	DWORD pcb = 0;

	DWORD dwRet = ::ReadFile(hFile, pbBuff, dwSizeLow, (LPDWORD)&pcb, NULL);
	pbBuff[dwSizeLow] = '\0';

	::CloseHandle(hFile);

	ATLASSERT(::IsWindow(m_hWnd));
	
	::SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)pbBuff);
	delete pbBuff;

	return true;
}

bool CEditExView::DoSave(const TCHAR* sPath, UINT uiFlag)
{
	HANDLE hFile = ::CreateFile(sPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_FLAG_WRITE_THROUGH, 0);
	if(INVALID_HANDLE_VALUE == hFile) return false;

	ATLASSERT(::IsWindow(m_hWnd));

	DWORD dwSizeLow = ::GetWindowTextLength(m_hWnd);	
	char* pbBuff = (char*)malloc(dwSizeLow+1);
	::SendMessage(m_hWnd, WM_GETTEXT, (WPARAM)dwSizeLow, (LPARAM)pbBuff);
	pbBuff[dwSizeLow] = '\0';

	DWORD pcb = 0;
	DWORD dwRet = ::WriteFile(hFile, pbBuff, dwSizeLow, (LPDWORD)&pcb, NULL);

	::CloseHandle(hFile);
	delete pbBuff;

	return true;
}

int  CEditExView::GetType(const TCHAR* sPath) const
{
	int r = FMT_TXT;
	const TCHAR* ext = RFind(sPath, _T('.'));
	if ( ext && (lstrcmpi(ext, XTE_EXT) == 0) )
		r = FMT_XTE;
	return r;
}

const TCHAR* CEditExView::RFind (const TCHAR* str, const TCHAR ch)
{
	TCHAR* p = (TCHAR*)str;	
	while (*p++);
	while (--p != str)
		if(*p == ch) 
			return p;	
	return 0;
}

const TCHAR* CEditExView::RFind (const TCHAR* str, const TCHAR* ss)
{
	TCHAR* p = (TCHAR*)str;	
	while (*p++);
	while (--p != str) {
		const TCHAR* p1 = ss;
		while(*p1) { 
			if(*p1 == *p) {
				return p;
			}
			p1++;
		}
	}
	return 0;
}
