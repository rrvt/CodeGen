// PersonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestApp.h"
#include "PersonDlg.h"
#include "afxdialogex.h"


// PersonDlg dialog

IMPLEMENT_DYNAMIC(PersonDlg, CDialogEx)

PersonDlg::PersonDlg(CWnd* pParent /*=nullptr*/)
  : CDialogEx(IDD_Person, pParent)
  , firstName(_T(""))
  , lastName(_T(""))
  , isAuthor(FALSE)
{

}

PersonDlg::~PersonDlg()
{
}

void PersonDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, firstName);
  DDX_Text(pDX, IDC_EDIT2, lastName);
  DDX_Check(pDX, IDC_CHECK1, isAuthor);
}


BEGIN_MESSAGE_MAP(PersonDlg, CDialogEx)
END_MESSAGE_MAP()


// PersonDlg message handlers
