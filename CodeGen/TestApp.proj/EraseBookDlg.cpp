// EraseBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestApp.h"
#include "EraseBookDlg.h"
#include "afxdialogex.h"


// EraseBookDlg dialog

IMPLEMENT_DYNAMIC(EraseBookDlg, CDialogEx)

EraseBookDlg::EraseBookDlg(CWnd* pParent /*=nullptr*/)
  : CDialogEx(IDD_EraseBook, pParent)
  , title(_T(""))
{

}

EraseBookDlg::~EraseBookDlg()
{
}

void EraseBookDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, title);
}


BEGIN_MESSAGE_MAP(EraseBookDlg, CDialogEx)
END_MESSAGE_MAP()


// EraseBookDlg message handlers
