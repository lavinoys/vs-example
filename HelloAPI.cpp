#include <windows.h>
/*
 * stdio.h, conio.h, graphics.h ���� ���Խ��� �� �ʿ�� ����. Ư���� ��쿡�� �ش��ϴ� ��������� ���Խ��Ѿ� �Ѵ�.
 * windows.h ��� ������ �⺻���� �ڷ� Ÿ��, �Լ� ���� ���� �����ϸ� �׿� �ʿ��� ��� ������ �����ϰ� �ִ�.
 */

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass= L"HelloAPI";

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)

/*
 * APIENTRY �����ڴ� _stdcall�� ȣ��Ծ��� ����Ѵٴ� ��
 * hlnstance ���α׷��� ��ü �ڵ��̴�. ���α׷� ��ü�� ���´� �������̸� API �Լ����� ���÷� ���, �� ���������� WinMain�� �Ű������� ���޵� hlnstance���� �������� g_hInst�� ������ ��
 * hPrevInstance �ٷ� �տ� ����� ���� ���α׷��� ��ü �ڵ�. ���� ��쿡�� NULL�� �Ǹ� WIN32������ �׻� NULL�̴�. ȣȯ���� ���ؼ��� �����ϴ� �Ű�������.
 * lpszCmdParam ��������� �Էµ� ���α׷� �Ű������̴�. DOS�� argv �Ű������� �ش��Ѵ�.
 * nCmdShow ���α׷��� ����� ���¸� �ּ�ȭ, ���� ��� ���� ���޵ȴ�.
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

	hWnd=CreateWindow(lpszClass,			//������Ŭ���� �̸�
					L"������ ���α׷���",			    //������Ÿ��Ʋ
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
					200, 200,							//�����찡 ���϶� X Y��ǥ
					600, 600,							//�������� ���� ����				
					(HWND)NULL,							//�θ������� �ڵ�
					(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
					hInstance,							//�ν��Ͻ��ڵ�
					NULL);								//������ ������

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
	LPCTSTR text = L"���������� ����";
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
