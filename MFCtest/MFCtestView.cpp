
// MFCtestView.cpp: CMFCtestView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCtest.h"
#endif

#include "MFCtestDoc.h"
#include "MFCtestView.h"
#include "math.h"
#include "CDiamondDlg.h"
#include "locale.h"
#include "P2.h"
#include "Line.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCtestView

IMPLEMENT_DYNCREATE(CMFCtestView, CView)

BEGIN_MESSAGE_MAP(CMFCtestView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CMFCtestView::OnLine)
	ON_COMMAND(ID_DIANMOND, &CMFCtestView::OnDianmond)
	ON_COMMAND(ID_OPTION, &CMFCtestView::OnOption)
	ON_COMMAND(ID_FILE_OPEN, &CMFCtestView::OnFileOpen)
	ON_COMMAND(ID_MIDBRESENHAM, &CMFCtestView::OnMidbresenham)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_WUAA, &CMFCtestView::OnWuaa)
	ON_COMMAND(ID_MFCCIRCLE, &CMFCtestView::OnMfccircle)
	ON_COMMAND(ID_MIDBRESENHAMCIRCLE, &CMFCtestView::OnMidbresenhamcircle)
END_MESSAGE_MAP()

// CMFCtestView 构造/析构

CMFCtestView::CMFCtestView() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCtestView::~CMFCtestView()
{
}

BOOL CMFCtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCtestView 绘图

void CMFCtestView::OnDraw(CDC* pDC/**/)
{
	CMFCtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//pDC->Ellipse(-100, -100, 200, 200);
	// TODO: 在此处为本机数据添加绘制代码
	Diamond(pDC);//调用绘图函数绘制图形
}

void CMFCtestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCtestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCtestView 诊断

#ifdef _DEBUG
void CMFCtestView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCtestDoc* CMFCtestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCtestDoc)));
	return (CMFCtestDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCtestView 消息处理程序


void CMFCtestView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	menuType = 1;
	CDC* pDC = GetDC();
	pDC->MoveTo(100, 100);
	pDC->LineTo(200, 200);
}


void CMFCtestView::OnDianmond()
{
	// TODO: 在此添加命令处理程序代码
	CDiamondDlg dlg;
	menuType = 3;
	if (dlg.DoModal() == IDOK)
	{
		N = dlg.N;
		R = dlg.R;
	}
	RedrawWindow();
}


void CMFCtestView::Diamond(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	//int N=30;//份数
	//int R=300;//半径 
	double thelta = 0;//初始角度b
	double delta = 2 * PI / N;//增量
	CPoint* p = new CPoint[N];
	CRect rect;
	CPen newpen, * oldpen;
	newpen.CreatePen(0, 1, myClr);
	oldpen = pDC->SelectObject(&newpen);
	GetClientRect(&rect);
	//zuobiaoyingshe
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	//计算所有分割点的坐标
	for (int i = 0; i < N; i++)
	{
		p[i].x = R * cos(thelta);
		p[i].y = R * sin(thelta);
		thelta += delta;
	}
	//绘制圆
	pDC->Ellipse(-R, R, R, -R);
	//绘图
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			pDC->MoveTo(p[i]);
			pDC->LineTo(p[j]);
		}
	}
	pDC->SelectObject(oldpen);
}


void CMFCtestView::OnOption()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		myClr = dlg.GetColor();
	}
	RedrawWindow();
}


void CMFCtestView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	CFileDialog fdlg(TRUE,_T("txt"),NULL,0,szFilter,this);
	CString strFilePath;
	if (fdlg.DoModal() == IDOK)
	{
		strFilePath = fdlg.GetPathName();
		//SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		CFile file;
		DWORD dwFileLen=100;
		char* pBuf;
		CString str;
		file.Open(strFilePath, CFile::modeRead);
		pBuf = new char[dwFileLen + 1];
		pBuf[dwFileLen] = 0;
		dwFileLen=file.Read(pBuf, dwFileLen);
		file.Close();
		CDC* pDC = GetDC();
		//str.Format(_T("%s"), pBuf);
		str = pBuf;
		setlocale(LC_CTYPE, "chs");
		pDC->TextOutW(100, 100, str);
		TRACE(pBuf);
		//MessageBox(str);
	}
}


void CMFCtestView::OnMidbresenham()
{
	// TODO: 在此添加命令处理程序代码
	menuType = 2;
}


void CMFCtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	startPoint.x = point.x;
	startPoint.y = point.y;
	CView::OnLButtonDown(nFlags, point);
}


void CMFCtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CLine line;
	CDC* pDC = GetDC();
	endPoint = point;
	if (menuType == 5)
	{
		pDC->Ellipse(startPoint.x, startPoint.y, point.x, point.y);
	}
	else if (menuType == 2) {
		line.MoveTo(pDC,startPoint.x,startPoint.y);
		line.LineTo(pDC, point.x, point.y);
	}
	else if (menuType == 6) {
		double r = sqrt((endPoint.x - startPoint.x) * (endPoint.x - startPoint.x) + (endPoint.y - startPoint.y) * (endPoint.y - endPoint.y)) / 2.0;//计算圆的半径
		MBCircle(r, pDC);//调用圆中点Bresenham算法	
	}
	CView::OnLButtonUp(nFlags, point);
}


void CMFCtestView::OnWuaa()
{
	// TODO: 在此添加命令处理程序代码
	menuType = 4;
}


void CMFCtestView::OnMfccircle()
{
	// TODO: 在此添加命令处理程序代码
	menuType = 5;
}


void CMFCtestView::OnMidbresenhamcircle()
{
	// TODO: 在此添加命令处理程序代码
	menuType = 6;
}


void CMFCtestView::MBEllipse(CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	double x, y, d1, d2, a, b;
	a = fabs(endPoint.x - startPoint.x) / 2;
	b = fabs(endPoint.y - startPoint.y) / 2;
	x = 0; y = b;
	d1 = b * b + a * a * (-b + 0.25);
	EllipsePoint(x, y, pDC);
	while (b * b * (x + 1) < a * a * (y - 0.5))//椭圆AC弧段
	{
		if (d1 < 0)
		{
			d1 += b * b * (2 * x + 3);
		}
		else
		{
			d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
			y--;
		}
		x++;
		EllipsePoint(x, y, pDC);
	}
	d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;//椭圆CB弧段
	while (y > 0)
	{
		if (d2 < 0)
		{
			d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++;
		}
		else
		{
			d2 += a * a * (-2 * y + 3);
		}
		y--;
		EllipsePoint(x, y, pDC);
	}
}


void CMFCtestView::EllipsePoint(double x, double y, CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CP2 pc = CP2((startPoint.x + endPoint.x) / 2.0, (startPoint.y +endPoint.y) / 2.0);        //椭圆中心坐标
	//COLORREF  clr = RGB(0, 0, 255);                         //定义椭圆的颜色
	pDC->SetPixelV(Round(x + pc.x), Round(y + pc.y), myClr);
	pDC->SetPixelV(Round(-x + pc.x), Round(y + pc.y), myClr);
	pDC->SetPixelV(Round(x + pc.x), Round(-y + pc.y), myClr);
	pDC->SetPixelV(Round(-x + pc.x), Round(-y + pc.y), myClr);
	pDC->MoveTo(Round(startPoint.x), Round(startPoint.y));
}


void CMFCtestView::MBCircle(double R, CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	double x, y, d;
	d = 1.25 - R; x = 0; y = R;
	for (x = 0; x <= y; x++)
	{
		CirclePoint(x, y, pDC);//调用八分法画圆子函数
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
	}
}


void CMFCtestView::CirclePoint(double x, double y, CDC* pDC)
{
	// TODO: 在此处添加实现代码.
	CP2 pc = CP2((startPoint.x + endPoint.x) / 2.0, (startPoint.y + endPoint.y) / 2.0);        //圆心坐标
	COLORREF  clr = RGB(0, 0, 255);                         //定义圆的边界颜色
	pDC->SetPixelV(Round(x + pc.x), Round(y + pc.y), clr);     //x,y
	pDC->SetPixelV(Round(y + pc.x), Round(x + pc.y), clr);     //y,x
	pDC->SetPixelV(Round(y + pc.x), Round(-x + pc.y), clr);    //y,-x
	pDC->SetPixelV(Round(x + pc.x), Round(-y + pc.y), clr);    //x,-y
	pDC->SetPixelV(Round(-x + pc.x), Round(-y + pc.y), clr);   //-x,-y
	pDC->SetPixelV(Round(-y + pc.x), Round(-x + pc.y), clr);   //-y,-x
	pDC->SetPixelV(Round(-y + pc.x), Round(x + pc.y), clr);    //-y,x
	pDC->SetPixelV(Round(-x + pc.x), Round(y + pc.y), clr);    //-x,y
	//pDC->MoveTo(Round(p0.x),Round(p0.y));
	//pDC->LineTo(Round(p1.x),Round(p1.y));	
}
