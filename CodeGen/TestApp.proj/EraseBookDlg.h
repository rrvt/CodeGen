#pragma once


// EraseBookDlg dialog

class EraseBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(EraseBookDlg)

public:
	EraseBookDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EraseBookDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EraseBook };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString title;
};
