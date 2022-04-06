// CDiamondDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCtest.h"
#include "CDiamondDlg.h"
#include "afxdialogex.h"


// CDiamondDlg 对话框

IMPLEMENT_DYNAMIC(CDiamondDlg, CDialog)

CDiamondDlg::CDiamondDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CDiamondDlg, pParent)
	, N(0)
	, R(0)
{

}

CDiamondDlg::~CDiamondDlg()
{
}

void CDiamondDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_N, N);
	DDV_MinMaxInt(pDX, N, 3, 50);
	DDX_Text(pDX, IDC_EDIT_R, R);
	DDV_MinMaxInt(pDX, R, 5, 500);
}


BEGIN_MESSAGE_MAP(CDiamondDlg, CDialog)
END_MESSAGE_MAP()


// CDiamondDlg 消息处理程序
