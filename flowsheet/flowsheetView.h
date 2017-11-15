
// flowsheetView.h : CflowsheetView 类的接口
//

#pragma once


class CflowsheetView : public CView
{
protected: // 仅从序列化创建
	CflowsheetView();
	DECLARE_DYNCREATE(CflowsheetView)

// 特性
public:
	CflowsheetDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CflowsheetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBuild();
	afx_msg void OnClearBuild();
	afx_msg void OnRuning();
};

#ifndef _DEBUG  // flowsheetView.cpp 中的调试版本
inline CflowsheetDoc* CflowsheetView::GetDocument() const
   { return reinterpret_cast<CflowsheetDoc*>(m_pDocument); }
#endif

