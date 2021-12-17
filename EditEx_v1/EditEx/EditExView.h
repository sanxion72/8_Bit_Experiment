// EditExView.h : interface of the CEditExView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlctrls.h>

#define FMT_TXT			0x0001
#define FMT_XTE			0x0002

class CEditExView : public CWindowImpl<CEditExView, CEdit>
{
	TCHAR m_path[_MAX_PATH];
	TCHAR m_name[_MAX_FNAME];

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
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

public:
	bool Load(const TCHAR* path, UINT uiFlag = 0);	
	bool Save(const TCHAR* path, UINT uiFlag = 0);	
	bool hasPath() { return m_path[0] == 0 ? false : true; }
	TCHAR* GetPath() { return m_path; }
private:		
	void SetNamePath(const TCHAR* path);		
	bool DoLoad(const TCHAR* sPath, UINT uiFlag = 0);
	bool DoSave(const TCHAR* sPath, UINT uiFlag = 0);
	int  GetType(const TCHAR* sPath) const;

public:
	static const TCHAR* RFind (const TCHAR* str, const TCHAR ch);
	static const TCHAR* RFind (const TCHAR* str, const TCHAR* ss);

};
