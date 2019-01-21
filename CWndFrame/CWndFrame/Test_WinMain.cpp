#include "WndFrame.h"

CWndFrame MyWnd;
HWND Hwnd = NULL;

VOID WinProc(PWinProcInfo pWin)
{

}

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	
	MyWnd.CWGetCmdShow(nShowCmd);
	MyWnd.CWGetHinstance(hInstance);
	MyWnd.CWGetStaticPoint(&MyWnd);
	if (MyWnd.CWCreateWindowExA())
	{
		////other code.....
		MyWnd.CWAddEvent(WM_LBUTTONDOWN);
		MyWnd.CWSetWindowProc(WinProc);
		Hwnd = MyWnd.CWAddScrollBar(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE | SB_HORZ,
			10, 10, 150, 20, NULL, (HMENU)400, NULL, NULL);
		MyWnd.CWSetDefaultScrollBarEvent();
		MyWnd.CWSetScrollBarMinAndMax(Hwnd, 0, 100);
		MyWnd.CWSetScrollBarCurrentIndex(Hwnd, 0);
		MyWnd.CWSetScrollBarLineGranularity(Hwnd, 1);
		MyWnd.CWSetScrollBarPageGranularity(Hwnd, 10);
		
		MyWnd.CWMsgProc();
	}

	return 0;
}