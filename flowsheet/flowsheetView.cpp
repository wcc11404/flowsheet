
// flowsheetView.cpp : CflowsheetView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "flowsheet.h"
#endif

#include "flowsheetDoc.h"
#include "flowsheetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CflowsheetView

IMPLEMENT_DYNCREATE(CflowsheetView, CView)

BEGIN_MESSAGE_MAP(CflowsheetView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CflowsheetView ����/����

CflowsheetView::CflowsheetView()
{
	// TODO: �ڴ˴���ӹ������

}

CflowsheetView::~CflowsheetView()
{
}

BOOL CflowsheetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CflowsheetView ����

void CflowsheetView::OnDraw(CDC* /*pDC*/)
{
	CflowsheetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CflowsheetView ��ӡ

BOOL CflowsheetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CflowsheetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CflowsheetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CflowsheetView ���

#ifdef _DEBUG
void CflowsheetView::AssertValid() const
{
	CView::AssertValid();
}

void CflowsheetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CflowsheetDoc* CflowsheetView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CflowsheetDoc)));
	return (CflowsheetDoc*)m_pDocument;
}
#endif //_DEBUG


// CflowsheetView ��Ϣ�������
