// BookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestApp.h"
#include "BookDlg.h"
#include "afxdialogex.h"


// BookDlg dialog

IMPLEMENT_DYNAMIC(BookDlg, CDialogEx)

BookDlg::BookDlg(CWnd* pParent /*=nullptr*/)
  : CDialogEx(IDD_DIALOG1, pParent)
  , title(_T(""))
  , authorFirstName(_T(""))
  , authorLastName(_T(""))
  , protagFirstName(_T(""))
  , protagLastName(_T(""))
{

}

BookDlg::~BookDlg()
{
}

void BookDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, title);
  DDX_Text(pDX, IDC_EDIT2, authorFirstName);
  DDX_Text(pDX, IDC_EDIT3, authorLastName);
  DDX_Text(pDX, IDC_EDIT4, protagFirstName);
  DDX_Text(pDX, IDC_EDIT5, protagLastName);
}


BEGIN_MESSAGE_MAP(BookDlg, CDialogEx)
END_MESSAGE_MAP()


// BookDlg message handlers
