#include <windows.h>
/*
 * stdio.h, conio.h, graphics.h 등을 포함시켜 줄 필요는 없다. 특별한 경우에는 해당하는 헤더파일을 포함시켜야 한다.
 * windows.h 헤더 파일은 기본적인 자료 타입, 함수 원형 등을 정의하며 그외 필요한 헤더 파일을 포함하고 있다.
 */

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass= L"HelloAPI";

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)

/*
 * APIENTRY 지정자는 _stdcall형 호출규약을 사용한다는 뜻
 * hlnstance 프로그램의 객체 핸들이다. 프로그램 자체를 일컫는 정수값이며 API 함수에서 수시로 사용, 이 예제에서는 WinMain의 매개변수로 전달된 hlnstance값을 전역변수 g_hInst에 대입해 둠
 * hPrevInstance 바로 앞에 실행된 현재 프로그램의 객체 핸들. 없을 경우에는 NULL이 되며 WIN32에서는 항상 NULL이다. 호환성을 위해서만 존재하는 매개변수다.
 * lpszCmdParam 명령행으로 입력된 프로그램 매개변수이다. DOS의 argv 매개변수에 해당한다.
 * nCmdShow 프로그램이 실행될 형태며 최소화, 보통 모양 등이 전달된다.
 */
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); 
	WndClass.hCursor=LoadCursor(NULL,IDC_WAIT );    
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,			//윈도우클래스 이름
					L"윈도우 프로그래밍",			    //윈도우타이틀
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
					200, 200,							//윈도우가 보일때 X Y좌표
					600, 600,							//윈도우의 폭과 높이				
					(HWND)NULL,							//부모윈도우 핸들
					(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
					hInstance,							//인스턴스핸들
					NULL);								//여분의 데이터

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
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
