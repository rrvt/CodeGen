#pragma once


// BookDlg dialog

class BookDlg : public CDialogEx
{
  DECLARE_DYNAMIC(BookDlg)

public:
  BookDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~BookDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Book };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  CString title;
  CString authorFirstName;
  CString authorLastName;
  CString protagFirstName;
  CString protagLastName;
};
