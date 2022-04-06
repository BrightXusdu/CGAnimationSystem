
// MFCtestView.h: CMFCtestView 类的接口
//

#pragma once


class CMFCtestView : public CView
{
protected: // 仅从序列化创建
	CMFCtestView() noexcept;
	DECLARE_DYNCREATE(CMFCtestView)

// 特性
public:
	CMFCtestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CMFCtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	//int N;
	//int R;
	afx_msg void OnDianmond();
	// 存储传输过来的圆的半径
	int R;
	// 存储传输过来的分割份数
	int N;
	void Diamond(CDC* pDC);
	// 颜色
	COLORREF myClr;
	afx_msg void OnOption();
	afx_msg void OnFileOpen();
	afx_msg void OnMidbresenham();
	// menu MFC api drawline  1,Mid bresenham 2
	int menuType;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 直线起点。
//	CP2 startPoint;
	CPoint startPoint;
	afx_msg void OnWuaa();
	afx_msg void OnMfccircle();
	afx_msg void OnMidbresenhamcircle();
	void MBEllipse(CDC* pDC);
	void EllipsePoint(double x, double y, CDC* pDC);
	CPoint endPoint;
	void MBCircle(double R, CDC* pDC);
	void CirclePoint(double x, double y, CDC* pDC);
};

#ifndef _DEBUG  // MFCtestView.cpp 中的调试版本
inline CMFCtestDoc* CMFCtestView::GetDocument() const
   { return reinterpret_cast<CMFCtestDoc*>(m_pDocument); }
#endif

