
// flowsheetView.h : CflowsheetView ��Ľӿ�
//

#pragma once


class CflowsheetView : public CView
{
protected: // �������л�����
	CflowsheetView();
	DECLARE_DYNCREATE(CflowsheetView)

// ����
public:
	CflowsheetDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CflowsheetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // flowsheetView.cpp �еĵ��԰汾
inline CflowsheetDoc* CflowsheetView::GetDocument() const
   { return reinterpret_cast<CflowsheetDoc*>(m_pDocument); }
#endif

