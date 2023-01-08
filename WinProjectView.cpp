
// WinProjectView.cpp: CWinProjectView 클래스의 구현
//
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WinProject.h"
#endif

#include "WinProjectDoc.h"
#include "WinProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinProjectView

IMPLEMENT_DYNCREATE(CWinProjectView, CView)

BEGIN_MESSAGE_MAP(CWinProjectView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(Easy, &CWinProjectView::OnEasy)
	ON_COMMAND(Normal, &CWinProjectView::OnNormal)
	ON_COMMAND(Hard, &CWinProjectView::OnHard)
	ON_COMMAND(Hell, &CWinProjectView::OnHell)
END_MESSAGE_MAP()

// CWinProjectView 생성/소멸
int Second = 600;
#define W_TIME Second//나타나는 시간
int Max_Stage = 1;
int Fail_Num = 0;
int Max_number = 7;//나타나는 최대 수
int xpo[15];//x좌표
int ypo[15];//y좌표
int start = 0;//1이되면 시작
int number = 0;//나타나는 숫자
int stage=1;//스테이지 번호
int WaitTime = W_TIME;//wait 시간
CWinProjectView::CWinProjectView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWinProjectView::~CWinProjectView()
{
}

BOOL CWinProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWinProjectView 그리기
void CWinProjectView::Wait(DWORD dwMillisecond)
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
void CWinProjectView::OnDraw(CDC* pDC)
{
	

	CWinProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CPen pen1,pen2;
	CFont font1,font2,font3;
	pen1.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	pen2.CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	font1.CreateFont(162,                                    //           
		0,                                          //          
		0,                                          //  nEscapement 
		0,                                          //  nOrientation   
		FW_NORMAL,                                  //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("  "));
	font2.CreateFont(32,                                    //           
		0,                                          //          
		0,                                          //  nEscapement 
		0,                                          //  nOrientation   
		FW_NORMAL,                                  //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("  "));
	font3.CreateFont(20,                                    //           
		0,                                          //          
		0,                                          //  nEscapement 
		0,                                          //  nOrientation   
		FW_NORMAL,                                  //   nWeight   
		FALSE,                                      //   bItalic   
		FALSE,                                      //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("  "));


			pDC->SelectObject(&font2);

	
	CString Stagenum,Maxstage;
	Stagenum.Format ( _T("%d"), stage);
	pDC->SelectObject(&pen1);
	Maxstage.Format(_T("%d"), Max_Stage);
	pDC->TextOutW(580, 5, _T("stage"));
	pDC->TextOutW(650, 5, (Stagenum));
	pDC->SelectObject(&font3);

	pDC->TextOutW(5, 5, _T("High Stage: "));
	

	pDC->TextOutW(90, 5, (Maxstage));
pDC->SelectObject(&font2);

	CBrush brush1, *oldbrush;
	brush1.CreateSolidBrush(RGB(255, 255, 255));

	pDC->SelectObject(&font3);

	pDC->Rectangle(1170, 10, 1270, 40);
	pDC->TextOutW(1190, 15, _T("RETRY"));
	pDC->Rectangle(1050, 10, 1150, 40);
	pDC->TextOutW(1070, 15, _T("START"));
	srand((unsigned int)time(NULL));
	CString strEx;
	if (start == 1) {
		pDC->SelectObject(&font1);
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->TextOutW(580, 250, _T("3"));
		Wait(500);
		pDC->TextOutW(580, 250, _T("2"));
		Wait(500);
		pDC->TextOutW(580, 250, _T("1"));
		Wait(500);
		pDC->SelectObject(&pen2);
		pDC->Rectangle(0, 90, 1300, 650);
		pDC->SelectObject(&font2);
	}
	if (start == 0) {
		pDC->SelectObject(&pen2);
		pDC->Rectangle(0, 90, 1300, 650);
		pDC->SelectObject(&pen1);
		pDC->SelectObject(&font2);

		pDC->TextOutW(500, 300, _T("START 버튼을 누르시오"));
		pDC->SelectObject(&font3);

	}
	for (int i = 0; i < Max_number+3; i++) {
			if (start == 1){
				
					Wait(WaitTime);
					xpo[i] = rand() % 1200;
					ypo[i] = (rand() % 510) + 90;//랜덤 좌표

					strEx.Format(_T("%d"), i + 1);
					pDC->SelectObject(&pen1);
					oldbrush = pDC->SelectObject(&brush1);
					if (i < Max_number) {
						pDC->Ellipse(xpo[i], ypo[i], xpo[i] + 50, ypo[i] + 50);//원 그리기
						pDC->TextOutW(xpo[i] + 15, ypo[i] + 10, (strEx));//원 안에 숫자 적기
					}
					if (i > 2) {
						pDC->SelectObject(&pen2);
						pDC->Ellipse(xpo[i - 3], ypo[i - 3], xpo[i - 3] + 50, ypo[i - 3] + 50);//원 그리기
					}
					if (Fail_Num > number + 2) {
						AfxMessageBox(L"실패",
							MB_OK | MB_ICONWARNING | MB_DEFBUTTON2);
						start = 0;
						stage = 1;
						number = 0;
						WaitTime = W_TIME;
						Max_number = 7;
						Fail_Num = 0;
						Invalidate();
					}
					Fail_Num++;
					if (start == 0) {
						pDC->SelectObject(&pen2);
						pDC->Rectangle(0, 90, 1300, 650);
						pDC->SelectObject(&pen1);
						pDC->SelectObject(&font2);

						pDC->TextOutW(500, 300, _T("START 버튼을 누르시오"));
						pDC->SelectObject(&font3);
					}
				
		}
			
			
	}
	start = 0;
		
	//pDC->SelectObject(oldbrush);

	pen1.DeleteObject();
	pen2.DeleteObject();
	brush1.DeleteObject();
	font1.DeleteObject();
	font2.DeleteObject();

	font3.DeleteObject();

}

void CWinProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWinProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWinProjectView 진단

#ifdef _DEBUG
void CWinProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CWinProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinProjectDoc* CWinProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinProjectDoc)));
	return (CWinProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinProjectView 메시지 처리기


void CWinProjectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this); //DC생성
	CPen my_pen(PS_SOLID, 5, RGB(255, 255, 255)); // 굵기가 5인 팬을 생성한다.
	dc.SelectObject(&my_pen); //  생성한 팬을 DC에 연결한다.

	
	
		if ((point.x - xpo[number]) < 50 && (point.x - xpo[number]) > 0 &&
			(point.y - ypo[number]) > 0 && (point.y - ypo[number]) < 50) //원을 클릭했을 때
		{
			dc.Ellipse(xpo[number], ypo[number], xpo[number] + 50, ypo[number] + 50);  //원이 사라지기
			number ++;
		}
		else if ((1270 - point.x < 100 && 1270 - point.x>0 && 40 - point.y < 40 && 40 - point.y>0))//retry 버튼
		{

			start = 1;
			stage = 1;
			number = 0;
			Fail_Num = 0;
			WaitTime = W_TIME;
			Max_number = 7;
			Invalidate();
		}
		else if ((1150 - point.x < 100 && 1150 - point.x>0 && 40 - point.y < 40 && 40 - point.y>0))// start 버튼
		{
			if (start == 0) {
				start = 1;
				stage = 1;
				number = 0;
				Fail_Num = 0;

				WaitTime = W_TIME;
				Max_number = 7;
				Invalidate();
			}
		}
		else
		{
			if (start == 1) {
				AfxMessageBox(L"실패",
					MB_OK | MB_ICONWARNING | MB_DEFBUTTON2);
				start = 0;
				stage = 1;
				number = 0;
				Fail_Num = 0;

				WaitTime = W_TIME;
				Max_number = 7;
				Invalidate();
			}
		}
		if ((point.x - xpo[Max_number-1]) < 50 && (point.x - xpo[Max_number-1]) > 0 && 
(point.y - ypo[Max_number-1]) > 0 && (point.y - ypo[Max_number-1]) < 50 && number==Max_number) //원을 클릭했을 때
		{
			AfxMessageBox(L"성공",
				MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON2);
			stage += 1;
			WaitTime -= 20;
			Max_number += 1;//난이도 상승

			number = 0;
			start = 1;
			Fail_Num = 0;

			Invalidate();
			if (stage > Max_Stage) {
				Max_Stage += 1;
			}
		}

	


	CView::OnLButtonDown(nFlags, point);
}


void CWinProjectView::OnEasy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Second = 600;
}


void CWinProjectView::OnNormal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Second = 500;

}


void CWinProjectView::OnHard()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Second = 400;

}


void CWinProjectView::OnHell()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Second = 300;

}
