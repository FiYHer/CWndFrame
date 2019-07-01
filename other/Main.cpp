
#define USE_STYLE//使用特殊效果的控件

#include "CWindow.hpp"
#include "CButton.hpp"
#include "CComboBox.hpp"
#include "CText.hpp"
#include "CEdit.hpp"
#include "CListBox.hpp"
#include "CAnimation.hpp"
#include "CListView.hpp"
#include "CToolTip.hpp"
#include "CSysLink.hpp"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	static PAINTSTRUCT stPs;
	switch (uMsg)
	{
	case WM_COMMAND:
		if (LOWORD(wParam) == 1000)
		{
			MessageBoxA(0, 0, 0, 0);
		}
		break;
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		MessageBoxA(0, 0, 0, 0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &stPs);
		EndPaint(hWnd, &stPs);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CTLCOLORSTATIC:
		//设置HDC的绘制模式
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	}
	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}


int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	CWindow MyWindow(hInstance);
	if (MyWindow.Create())
	{
		//MyWindow.SetTransparent(200);
		MyWindow.SetWindowLocation(300, 300);
		MyWindow.SetWndProc(WindowProc);
		MyWindow.SetCaption("First Windows");
		CSysLink MySysLink(MyWindow.GetHwnd(), hInstance);
		MySysLink.Create();
		MySysLink.SetItem(L"https://www.baidu.com");
		return MyWindow.GetMsgLoop();
	}
	return -1;
}
