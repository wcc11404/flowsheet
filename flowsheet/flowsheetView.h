
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
};

#ifndef _DEBUG  // flowsheetView.cpp �еĵ��԰汾
inline CflowsheetDoc* CflowsheetView::GetDocument() const
   { return reinterpret_cast<CflowsheetDoc*>(m_pDocument); }
#endif
