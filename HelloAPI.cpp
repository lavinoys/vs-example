#include <windows.h>
/*
 * stdio.h, conio.h, graphics.h ���� ���Խ��� �� �ʿ�� ����. Ư���� ��쿡�� �ش��ϴ� ��������� ���Խ��Ѿ� �Ѵ�.
 * windows.h ��� ������ �⺻���� �ڷ� Ÿ��, �Լ� ���� ���� �����ϸ� �׿� �ʿ��� ��� ������ �����ϰ� �ִ�.
 */

// �Լ� ���� ����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);										// �θ�(����) â
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);	// �ڽ�(����) â
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";		// ���� ������ Ŭ���� �̸�(������ Ŭ������ �����ϴµ� ���)
LPCTSTR ChildClassName = L"ChildWin";	// ���ϵ� ������ Ŭ���� �̸�

int APIENTRY WinMain(HINSTANCE hInstance,		// APIENTRY �����ڴ� _stdcall�� ȣ��Ծ��� ����Ѵٴ� ��
					 HINSTANCE hPrevInstance,	// hlnstance ���α׷��� ��ü �ڵ��̴�. ���α׷� ��ü�� ���´� �������̸� API �Լ����� ���÷� ���, �� ���������� WinMain�� �Ű������� ���޵� hlnstance���� �������� g_hInst�� ������ ��
					 LPSTR lpszCmdParam,		// lpszCmdParam ��������� �Էµ� ���α׷� �Ű������̴�. DOS�� argv �Ű������� �ش��Ѵ�.
					 int nCmdShow)				// nCmdShow ���α׷��� ����� ���¸� �ּ�ȭ, ���� ��� ���� ���޵ȴ�.
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;										// ���� ����
	WndClass.cbWndExtra=0;										// ���� ����
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);	// �������� ��� ����
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);				// �����찡 ����� ���콺 Ŀ��
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);				// �����찡 ����� ������
	WndClass.hInstance=hInstance;								// ���α׷��� ��ü �ڵ�
	WndClass.lpfnWndProc=(WNDPROC)WndProc;						// ������ ���ν��� ����
	WndClass.lpszClassName=lpszClass;							// ������ Ŭ���� �̸�
	WndClass.lpszMenuName=NULL;									// ���α׷��� ����� �޴�
	WndClass.style=CS_HREDRAW | CS_VREDRAW;						// Ŭ������ ��Ÿ��
	RegisterClass(&WndClass);									// ���� ������ Ŭ���� ���

	WndClass.lpfnWndProc = ChildWndProc;						// ���ϵ� ������ ���ν���
	WndClass.lpszClassName = ChildClassName;					// ���ϵ� ������ Ŭ���� �̸�
	RegisterClass(&WndClass);									//���ϵ� ������ Ŭ���� �̸�

	hWnd=CreateWindow(lpszClass,								//������ Ŭ���� �̸�
					L"������ ���α׷���",							//������ Ÿ��Ʋ
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,			//������ ��Ÿ��
					200, 200,									//�����찡 ���϶� X Y��ǥ
					600, 600,									//�������� ���� ����				
					(HWND)NULL,									//�θ������� �ڵ�
					(HMENU)NULL,								//�����찡 ������ �޴��ڵ�
					hInstance,									//�ν��Ͻ��ڵ�
					NULL);										//������ ������

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
		case WM_CREATE : 
			{
				HWND hChildWnd = CreateWindow(
									ChildClassName,					// ���ϵ� ������ Ŭ���� �̸�
									L"���ϵ� ������",					// ������ Ÿ��Ʋ
									WS_OVERLAPPEDWINDOW | WS_CHILD,	// ������ ��Ÿ��
									150,							// ������ ���� �� x ��ǥ
									150,							// ������ ���� �� y ��ǥ
									260,							// ������ ��
									200,							// ������ ����
									hWnd,							// �θ� ������
									(HMENU) 2000,					// ���ϵ� ������ ID
									g_hInst,						// ��ü �ڵ�
									(LPVOID) NULL);					// ������ ������
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
	LPCTSTR text = L"���ϵ� ������ ����";
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