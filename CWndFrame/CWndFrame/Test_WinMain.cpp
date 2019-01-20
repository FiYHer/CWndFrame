#include "WndFrame.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	CWndFrame MyWnd;
	MyWnd.CWGetCmdShow(nShowCmd);
	MyWnd.CWGetHinstance(hInstance);
	MyWnd.CWGetStaticPoint(&MyWnd);
	if (MyWnd.CWCreateWindowExA())
	{
		////other code.....

		MyWnd.CWMsgProc();
	}

	return 0;
}