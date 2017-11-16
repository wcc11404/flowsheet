
// flowsheetView.cpp : CflowsheetView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "flowsheet.h"
#endif

#include "flowsheetDoc.h"
#include "flowsheetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "object.h"
#include <fstream>
// CflowsheetView

IMPLEMENT_DYNCREATE(CflowsheetView, CView)

BEGIN_MESSAGE_MAP(CflowsheetView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
ON_WM_KEYUP()
ON_COMMAND(ID_32771, &CflowsheetView::OnBuild)
ON_COMMAND(ID_32772, &CflowsheetView::OnClearBuild)
ON_COMMAND(ID_32773, &CflowsheetView::OnRuning)
ON_COMMAND(ID_FILE_SAVE, &CflowsheetView::OnFileSave)
ON_COMMAND(ID_FILE_OPEN, &CflowsheetView::OnFileOpen)
ON_COMMAND(ID_FILE_NEW, &CflowsheetView::OnFileNew)
ON_COMMAND(ID_32774, &CflowsheetView::OnClearRuning)
END_MESSAGE_MAP()

// CflowsheetView 构造/析构

CflowsheetView::CflowsheetView()
{
	// TODO: 在此处添加构造代码

}

CflowsheetView::~CflowsheetView()
{
}

BOOL CflowsheetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CflowsheetView 绘制

void CflowsheetView::OnDraw(CDC* pDC)
{
	CflowsheetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC MemDC; //首先定义一个显示设备对象 
	CBitmap MemBitmap;//定义一个位图对象 

					  //随后建立与屏幕显示兼容的内存显示设备 
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^ 
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小 
	LPRECT lpRect = new RECT();
	pDC->GetWindow()->GetWindowRect(lpRect);
	MemBitmap.CreateCompatibleBitmap(pDC, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);		//获取绘图区域大小

																											//将位图选入到内存显示设备中 
																											//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上 
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);

	//先用背景色将位图清除干净，这里我用的是白色作为背景 
	//你也可以用自己应该用的颜色 
	MemDC.FillSolidRect(0, 0, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, RGB(255, 255, 255));

	GetDocument()->manager.onDraw(&MemDC);

	pDC->BitBlt(0, 0, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, &MemDC, 0, 0, SRCCOPY);

	//绘图完成后的清理 
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}


// CflowsheetView 打印

BOOL CflowsheetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CflowsheetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CflowsheetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CflowsheetView 诊断

#ifdef _DEBUG
void CflowsheetView::AssertValid() const
{
	CView::AssertValid();
}

void CflowsheetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CflowsheetDoc* CflowsheetView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CflowsheetDoc)));
	return (CflowsheetDoc*)m_pDocument;
}
#endif //_DEBUG


// CflowsheetView 消息处理程序


BOOL CflowsheetView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return true;
}


void CflowsheetView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDocument()->manager.onPress(point.x, point.y);
	Invalidate();
	GetDocument()->x = point.x;
	GetDocument()->y = point.y;
	CView::OnLButtonDown(nFlags, point);
}


void CflowsheetView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(GetDocument()->manager.onRelease(point.x, point.y)) Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CflowsheetView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetDocument()->manager.onDBclick(point.x, point.y);
	Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}


void CflowsheetView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetDocument()->manager.onMove(point.x - GetDocument()->x, point.y - GetDocument()->y)) Invalidate();
	GetDocument()->x = point.x;
	GetDocument()->y = point.y;
	CView::OnMouseMove(nFlags, point);
}


void CflowsheetView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetDocument()->manager.onKey(nChar)) Invalidate();
	/*char temp[80];
	sprintf(temp, "%d", nChar);
	MessageBox(temp);*/
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CflowsheetView::OnBuild()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->manager.onBuild();
	Invalidate();
}


void CflowsheetView::OnClearBuild()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->manager.onClearBuild();
	Invalidate();
}


void CflowsheetView::OnRuning()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->manager.onRuning();
	Invalidate();
}


void CflowsheetView::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isOpen = FALSE;		//是否打开(否则为保存) 
	CString defaultDir = "C:\\Users\\cheng\\Desktop";	//默认打开的文件路径
	CString fileName = "test";			//默认打开的文件名
										//CString filter = "文件 (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";	//文件过虑的类型
	CString filter = "文件 (*.dbp)|*.dbp||";
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	//openFileDlg.GetOFN().lpstrInitialDir = "E:\\FileTest\\test";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();

		std::ofstream out(filePath);
		GetDocument()->manager.onSave(out);
		out.close();
	}
}


void CflowsheetView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	BOOL isOpen = TRUE;		//是否打开(否则为保存) 
	CString defaultDir = "C:\\Users\\cheng\\Desktop";	//默认打开的文件路径
	CString fileName = "test";			//默认打开的文件名
										//CString filter = "文件 (*.doc; *.ppt; *.xls)|*.doc;*.ppt;*.xls||";	//文件过虑的类型
	CString filter = "文件 (*.dbp)|*.dbp||";
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	//openFileDlg.GetOFN().lpstrInitialDir = "E:\\FileTest\\test";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result == IDOK) {
		filePath = openFileDlg.GetPathName();

		std::ifstream in(filePath);
		GetDocument()->manager.onOpen(in);
		in.close();

		Invalidate();
	}
}


void CflowsheetView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->manager.onClear();
	Invalidate();
}


void CflowsheetView::OnClearRuning()
{
	// TODO: 在此添加命令处理程序代码
	GetDocument()->manager.onClearRuning();
	Invalidate();
}
