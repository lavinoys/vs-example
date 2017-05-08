#include <windows.h>
/*
 * stdio.h, conio.h, graphics.h 등을 포함시켜 줄 필요는 없다. 특별한 경우에는 해당하는 헤더파일을 포함시켜야 한다.
 * windows.h 헤더 파일은 기본적인 자료 타입, 함수 원형 등을 정의하며 그외 필요한 헤더 파일을 포함하고 있다.
 */

// 함수 원형 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);										// 부모(메인) 창
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	// 자식(하위) 창
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";		// 메인 윈도우 클래스 이름(윈도우 클래스를 정의하는데 사용)
LPCTSTR ChildClassName = L"ChildWin";	// 차일드 윈도우 클래스 이름

int APIENTRY WinMain(HINSTANCE hInstance,		// APIENTRY 지정자는 _stdcall형 호출규약을 사용한다는 뜻
					 HINSTANCE hPrevInstance,	// hlnstance 프로그램의 객체 핸들이다. 프로그램 자체를 일컫는 정수값이며 API 함수에서 수시로 사용, 이 예제에서는 WinMain의 매개변수로 전달된 hlnstance값을 전역변수 g_hInst에 대입해 둠
					 LPSTR lpszCmdParam,		// lpszCmdParam 명령행으로 입력된 프로그램 매개변수이다. DOS의 argv 매개변수에 해당한다.
					 int nCmdShow)				// nCmdShow 프로그램이 실행될 형태며 최소화, 보통 모양 등이 전달된다.
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;										// 예약 영역
	WndClass.cbWndExtra=0;										// 예약 영역
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);	// 윈도우의 배경 색상
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);				// 윈도우가 사용할 마우스 커서
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);				// 윈도우가 사용할 아이콘
	WndClass.hInstance=hInstance;								// 프로그램의 객체 핸들
	WndClass.lpfnWndProc=(WNDPROC)WndProc;						// 윈도우 프로시저 지정
	WndClass.lpszClassName=lpszClass;							// 윈도우 클래스 이름
	WndClass.lpszMenuName=NULL;									// 프로그램이 사용할 메뉴
	WndClass.style=CS_HREDRAW | CS_VREDRAW;						// 클래스의 스타일
	RegisterClass(&WndClass);									// 메인 윈도우 클래스 등록

	WndClass.lpfnWndProc = ChildWndProc;						// 차일드 윈도우 프로시져
	WndClass.lpszClassName = ChildClassName;					// 차일드 윈도우 클래스 이름
	RegisterClass(&WndClass);									//차일드 윈도우 클래스 이름

	hWnd=CreateWindow(lpszClass,								//윈도우 클래스 이름
					L"윈도우 프로그래밍",							//윈도우 타이틀
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,			//윈도우 스타일
					200, 200,									//윈도우가 보일때 X Y좌표
					600, 600,									//윈도우의 폭과 높이				
					(HWND)NULL,									//부모윈도우 핸들
					(HMENU)NULL,								//윈도우가 가지는 메뉴핸들
					hInstance,									//인스턴스핸들
					NULL);										//여분의 데이터

 	   ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
						 WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성";
	switch(iMessage) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd,&ps);
				TextOut(hdc,100,100,text,lstrlen(text));
				EndPaint(hWnd,&ps);
				return 0;
			}
		case WM_CREATE : 
			{
				HWND hChildWnd = CreateWindow(
									ChildClassName,					// 차일드 윈도우 클래스 이름
									L"차일드 윈도우",					// 윈도우 타이틀
									WS_OVERLAPPEDWINDOW | WS_CHILD,	// 윈도우 스타일
									150,							// 윈도우 보일 때 x 좌표
									150,							// 윈도우 보일 때 y 좌표
									260,							// 윈도우 폭
									200,							// 윈도우 높이
									hWnd,							// 부모 윈도우
									(HMENU) 2000,					// 차일드 윈도우 ID
									g_hInst,						// 객체 핸들
									(LPVOID) NULL);					// 여분의 데이터
				if (!hChildWnd) return -1;
				ShowWindow(hChildWnd, SW_SHOW);
				return 0;
			}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}


LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMessage,
						 WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"차일드 윈도우 생성";
	switch(iMessage)
	{
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				TextOut(hdc, 10, 10, text, lstrlen(text));
				EndPaint(hWnd, &ps);
				return 0;
			}
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}