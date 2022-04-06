#pragma once


// CDiamondDlg 对话框

class CDiamondDlg : public CDialog
{
	DECLARE_DYNAMIC(CDiamondDlg)

public:
	CDiamondDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDiamondDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDiamondDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 分割份数
	int N;
	// 圆的半径
	int R;
};
