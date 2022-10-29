
#include "stdafx.h"
#include "EditExView.h"

using std::ifstream;
using std::ofstream;

const TCHAR* XTE_EXT = _T(".xte");

CEditExView::CEditExView()
{
	memset(m_path, 0, sizeof m_path);
	memset(m_name, 0, sizeof m_name);
	m_rawText.push_back(string());
	m_TabCount = 2;
	m_nSetTextSemaphor=0;
}

void CEditExView::CreateFile(TCHAR *path) 
{
	m_nSetTextSemaphor=0;

	if(path == NULL) {
		memset(m_path, 0, sizeof m_path);
		memset(m_name, 0, sizeof m_name);
	} else {
		SetNamePath(path);
	}

	EmptyRawText();
	m_rawText.push_back(string());
}

CEditExView::~CEditExView()
{
}

int CEditExView::InputRawSize()
{
	int len = 0;
	int size = (int)m_rawText.size();
	for(int i=0;i<size;i++) {
		string str = m_rawText[i];
		len += str.size();
	}
	return len;
}

string CEditExView::GetRawText()
{
	string rawText;
	int size = (int)m_rawText.size();
	for(int i=0; i<size; i++) {
		string str = m_rawText[i];
		rawText.append(str);
	}
	return rawText;
}

void CEditExView::EmptyRawText()
{
	m_rawText.clear();
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
	if (sPath == NULL)
		sPath = m_path;
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

TCHAR* CEditExView::GetNamePath() const
{	
	return (TCHAR*)m_path;
}

bool CEditExView::DoLoad(const TCHAR* sPath, UINT uiFlag)
{
	string line;
	ifstream in(sPath);

	m_rawText.clear();
	while( !in.eof() )
	{
		getline(in, line, '\n');
		line.append(1, '\r').append(1, '\n');
		m_rawText.push_back(line);
	}

	ATLASSERT(::IsWindow(m_hWnd));

	string input = GetRawText();
	::SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)input.c_str());

	return true;
}

bool CEditExView::DoSave(const TCHAR* sPath, UINT uiFlag)
{
	ofstream out(sPath);
	out << GetRawText();
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

BOOL CEditExView::IsInputPosition(int nPosition) const
{
	return TRUE;
}

LRESULT CEditExView::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nChar = (TCHAR)wParam;
	UINT nRepCnt = (UINT)lParam & 0xFFFF;
	UINT nFlags = (UINT)((lParam & 0xFFFF0000) >> 16);

	if((GetStyle()&ES_READONLY)==ES_READONLY) {
		return 0;
	}

	int nSelectionStart=0;
	int nSelectionEnd=0;
	GetSel(nSelectionStart, nSelectionEnd);

	BOOL bAcceptReturnKey=(GetStyle()&ES_MULTILINE) && (GetStyle()&ES_WANTRETURN);
	if(nChar==10)
	{
		nChar=VK_RETURN;
		bAcceptReturnKey=(GetStyle()&ES_MULTILINE);
	}

	// If character value is above 32, then it is ANSI or Extended. 
	// Below 32 are control and navigation characters. 
	if(nChar>=32 || nChar == VK_TAB || (nChar==VK_RETURN && bAcceptReturnKey))
	{
		if(nSelectionStart==nSelectionEnd)
		{
			if(GetStyle()&ES_NUMBER && nChar!=VK_RETURN && 
				(nChar<_T('0') || nChar>_T('9')))
			{
				return 0;
			}

			if(IsInputPosition(nSelectionStart))
			{
				int nActualInsertionPoint=nSelectionStart;
				if(m_bInsertMode)
					nActualInsertionPoint=InsertAt(nSelectionStart,(TCHAR)nChar);
				else
					nActualInsertionPoint=SetAt(nSelectionStart,(TCHAR)nChar);

				// InsertAt will return -1 if the character cannot be inserted here. 
				if(nActualInsertionPoint>=0)
					nSelectionStart=nActualInsertionPoint+1;
				else
					ValidationError();

				Update(nSelectionStart);
			}
			else
			{
				// Beep if trying to type over a literal. 
				ValidationError();
			}
		}
		else
		{
			// First delete the remaining selection. 
			// The function will return a valid count if 
			// some input characters were deleted. We use 
			// this value to determine if it makes sense to insert. 
			if(DeleteRange(nSelectionStart,nSelectionEnd))
			{
				if(GetStyle()&ES_NUMBER && nChar!=VK_RETURN && 
					(nChar<_T('0') || nChar>_T('9')))
				{
					return 0;
				}

				if(IsInputPosition(nSelectionStart))
				{
					int nActualInsertionPoint=nSelectionStart;
					if(m_bInsertMode)
						nActualInsertionPoint=InsertAt(nSelectionStart,(TCHAR)nChar);
					else
						nActualInsertionPoint=SetAt(nSelectionStart,(TCHAR)nChar);

					// InsertAt will return -1 if the character cannot be inserted here. 
					if(nActualInsertionPoint>=0)
						nSelectionStart=nActualInsertionPoint+1;
					else
						ValidationError();

					Update(nSelectionStart);
				}
				else  // Must be on a literal, so beep and move to a valid location. 
				{
					ValidationError();
				}
			}
		}
	}
	else
	{
		if(nChar==VK_BACK)
		{
			if(nSelectionStart==nSelectionEnd)
			{
				int nRow = 0;
				int nCol = 0;
				GetRowColFromPosition(nRow, nCol, nSelectionStart);
				if(nCol == 0)
					nSelectionStart -= 2;
				else
					nSelectionStart--;

				if(DeleteRange(nSelectionStart,nSelectionEnd))
					Update(nSelectionStart);
			}
			else if(DeleteRange(nSelectionStart,nSelectionEnd))
			{
				Update(nSelectionStart);
			}
		}
	}
	return 0;
}

LRESULT CEditExView::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nChar = (TCHAR)wParam;

	BOOL bIsShiftKeyDown=::GetAsyncKeyState(VK_SHIFT)<0;
	BOOL bIsCtrlKeyDown=::GetAsyncKeyState(VK_CONTROL)<0;

	if(nChar == VK_INSERT) {
	if (!bIsShiftKeyDown && !bIsCtrlKeyDown)
		{
			// The standard CEdit control does not support over-typing. 
			// This flag is used to manage over-typing internally. 
			SetInsertMode(!GetInsertMode());
		}
	}
	return 0;
}


int CEditExView::DeleteRange(int& nSelectionStart, int& nSelectionEnd)
{
	int nDeleteCount = nSelectionEnd - nSelectionStart;
	int nRow = 0;
	int nCol = 0;

	vector<string> temp_;
	string line;
	GetRowColFromPosition(nRow, nCol, nSelectionStart);
	for(int i=0;i<nRow;i++)
		temp_.push_back(m_rawText[i]);
	line =  m_rawText[nRow];
	string h = line.substr(0, nCol);
	GetRowColFromPosition(nRow, nCol, nSelectionEnd);
	line =  m_rawText[nRow];
	string t = line.substr(nCol, line.size());
	temp_.push_back(h.append(t));
	for(int i=nRow+1;i<m_rawText.size();i++)
		temp_.push_back(m_rawText[i]);

	m_rawText.swap(temp_);

	if(nDeleteCount)
	{
		Update(-1);
	}

	// return the deleted count so that an error can be generated 
	// if none were deleted. 
	return nDeleteCount;
}

int CEditExView::InsertAt(int nSelectionStart, TCHAR chNewChar)
{
	int nInsertionPoint=nSelectionStart;
	int nRow = 0;
	int nCol = 0;
	GetRowColFromPosition(nRow, nCol, nInsertionPoint);

	if(chNewChar==VK_RETURN)
	{
		string line1 = m_rawText[nRow].substr(0, nCol);
		line1.append(1, '\r').append(1, '\n');
		string line2 = m_rawText[nRow].substr(nCol, m_rawText[nRow].size());
		m_rawText[nRow] = line2;
		m_rawText.insert(m_rawText.begin() + nRow, line1);
		nInsertionPoint++;
	}
	else if (chNewChar == VK_TAB)
	{
		for(int i=0;i<m_TabCount;i++) {
			nInsertionPoint = nCol++;
			m_rawText[nRow].insert(nInsertionPoint, 1, _T(' '));
		}
	}
	else
		m_rawText[nRow].insert(nCol, &chNewChar);

	return nInsertionPoint;
}


int CEditExView::SetAt(int nSelectionStart, TCHAR chNewChar)
{
	int nInsertionPoint=nSelectionStart;
	int nRow = 0;
	int nCol = 0;
	GetRowColFromPosition(nRow, nCol, nInsertionPoint);

	if(chNewChar == VK_RETURN)
	{
		string line1 = m_rawText[nRow].substr(0, nCol-1);
		line1.append(1, '\r').append(1, '\n');
		string line2 = m_rawText[nRow].substr(nCol, m_rawText[nRow].size());
		m_rawText[nRow] = line2;
		m_rawText.insert(m_rawText.begin() + nRow, line1);
	}
	else if (chNewChar == VK_TAB)
	{
		TCHAR nChar = _T(' ');
		for(int i=0;i<m_TabCount;i++) {
			if(nCol<m_rawText[nRow].size()) {
				nInsertionPoint = nCol++;
				m_rawText[nRow][nInsertionPoint] = nChar;
			}
		}
	}
	else
		m_rawText[nRow][nCol] = chNewChar;

	return nInsertionPoint;
}

void CEditExView::SetInsertMode(BOOL bInsertMode)
{
	m_bInsertMode = bInsertMode;
}

BOOL CEditExView::GetInsertMode() const
{
	return m_bInsertMode;
}

void CEditExView::ValidationError()
{
	::MessageBeep(MB_ICONEXCLAMATION);
}

void CEditExView::Update(int nSelectionStart/*=0*/)
{
	// Update the edit control if it exists. 
	if(::IsWindow(m_hWnd))
	{
		m_nSetTextSemaphor++;
		string input = GetRawText();
		::SendMessage(m_hWnd, WM_SETTEXT, 0, (LPARAM)input.c_str());
		m_nSetTextSemaphor--;
		SetModify(TRUE);
		SetSel(nSelectionStart, nSelectionStart);
	}
}
