
// md2View.cpp: Cmd2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "md2.h"
#endif

#include "md2Doc.h"
#include "md2View.h"
#include "CLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmd2View

IMPLEMENT_DYNCREATE(Cmd2View, CView)

BEGIN_MESSAGE_MAP(Cmd2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_COL, &Cmd2View::OnMenuCol)
	ON_COMMAND(ID_SIZE_1, &Cmd2View::OnSize1)
	ON_COMMAND(ID_SIZE_16, &Cmd2View::OnSize16)
	ON_COMMAND(ID_SIZE_32, &Cmd2View::OnSize32)
END_MESSAGE_MAP()

// Cmd2View 생성/소멸

Cmd2View::Cmd2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Cmd2View::~Cmd2View()
{
}

BOOL Cmd2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Cmd2View 그리기

void Cmd2View::OnDraw(CDC* pDC)
{
	Cmd2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int n = pDoc->m_oa.GetSize();
	for (int i = 0; i < n; i++) {
		CLine* p;
		p=(CLine*)pDoc->m_oa[i];
		p->Draw(pDC);
	}
}


// Cmd2View 인쇄

BOOL Cmd2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void Cmd2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void Cmd2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// Cmd2View 진단

#ifdef _DEBUG
void Cmd2View::AssertValid() const
{
	CView::AssertValid();
}

void Cmd2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmd2Doc* Cmd2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmd2Doc)));
	return (Cmd2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cmd2View 메시지 처리기


void Cmd2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nFlags==MK_LBUTTON){
		CLine* p = new CLine(pnt, point, Size,Col);
		GetDocument()->m_oa.Add(p);
		Invalidate(FALSE);
	}
	pnt = point;
	CView::OnMouseMove(nFlags, point);
}


void Cmd2View::OnMenuCol()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK) {
		Col = dlg.GetColor();
	}
}


void Cmd2View::OnSize1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Size = 1;
}


void Cmd2View::OnSize16()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Size = 16;
}


void Cmd2View::OnSize32()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Size = 32;
}


void Cmd2View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Col = RGB(0, 255, 0);
	Size = 2;
}
