// EditExView.h : interface of the CEditExView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlctrls.h>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

#define FMT_TXT			0x0001
#define FMT_XTE			0x0002

class CEditExView : 
	public CWindowImpl<CEditExView, CEdit>
{
	TCHAR m_path[_MAX_PATH];
	TCHAR m_name[_MAX_FNAME];

	vector<string> m_rawText;

	int m_TabCount;
	int m_nRow;
	int m_nCol;

protected:
	// flag that specifies if control is insert or overwrite edit mode
	BOOL m_bInsertMode;
	int m_nSetTextSemaphor;

public:
	CEditExView();
	~CEditExView();

	DECLARE_WND_SUPERCLASS(NULL, CEdit::GetWndClassName())

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CEditExView)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_CHAR, OnChar)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

public:
	bool Load(const TCHAR* path, UINT uiFlag = 0);	
	bool Save(const TCHAR* path = NULL, UINT uiFlag = 0);

	int InputRawSize();
	string GetRawText();
	void EmptyRawText();
	void GetCurrentRowCol (int& nRow, int &nCol, bool bUpdate);
	void UpdateCurrentRowCol();
	void GetRowColFromPosition(int& nRow, int &nCol, int nPosition);
	void SetInsertMode(BOOL bInsertMode);
	BOOL GetInsertMode() const;
	void CreateFile(TCHAR* path = NULL);
	TCHAR* GetNamePath() const;

protected:
	virtual BOOL IsInputPosition(int nPosition) const;
	// called every time when user is deleting symbol or range of symbols
	virtual int DeleteRange(int& nSelectionStart, int& nSelectionEnd);
	// called every time user typed new symbol (insert mode is on)
	virtual int InsertAt(int nSelectionStart, TCHAR chNewChar);
	// called every time user typed new symbol (overwrite mode is on)
	virtual int SetAt(int nSelectionStart, TCHAR chNewChar);
	virtual void ValidationError();
	void Update(int nSelectionStart = 0);
	
private:
	void SetNamePath(const TCHAR* path);
	bool DoLoad(const TCHAR* sPath, UINT uiFlag = 0);
	bool DoSave(const TCHAR* sPath, UINT uiFlag = 0);

	int  GetType(const TCHAR* sPath) const;

public:
	static const TCHAR* RFind (const TCHAR* str, const TCHAR ch);
	static const TCHAR* RFind (const TCHAR* str, const TCHAR* ss);
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

};

////////////////////////////////////////////
// inline

inline void CEditExView::
GetRowColFromPosition(int& nRow, int &nCol, int nPosition)
{
	int len = 0;
	int size = m_rawText.size();
	nCol = nPosition;
	for(nRow=0;nRow<size;nRow++) {
		len = m_rawText[nRow].size();
		if(nCol > len)
			nCol -= len;
		else {
			if(nCol == len && size - nRow > 1) {
				nCol = 0; nRow++;
			}
			break;
		}
	}
}

inline void CEditExView::
UpdateCurrentRowCol()
{
	int nStartPos, nEndPos;
	GetSel(nStartPos, nEndPos);
	m_nRow = LineFromChar(nEndPos);
	m_nCol = 0;
	int nChar = nEndPos - LineIndex();
	if(nChar > 0)
	{
		LPTSTR lpstrLine = (LPTSTR)_alloca(max(2, (nChar + 1) * sizeof(TCHAR)));	// min = WORD for length
		nChar = GetLine(m_nRow, lpstrLine, nChar);
		for(int i = 0; i < nChar; i++)
		{
			if(lpstrLine[i] == _T('\t'))
				m_nCol = ((m_nCol / m_TabCount) + 1) * m_TabCount;
			else
				m_nCol++;
		}
	}

	m_nRow++; m_nCol++;
}

inline void CEditExView::
GetCurrentRowCol (int& nRow, int &nCol, bool bUpdate)
{
	if (bUpdate)
		UpdateCurrentRowCol();
	nRow =  m_nRow;
	nCol =  m_nCol;		
}
