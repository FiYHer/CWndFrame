#include "WndFrame.h"

CWndFrame* CWndFrame::m_CWindows = NULL;

CWndFrame::CWndFrame()
{
	m_Hinstance = NULL;//保存程序实例
	m_ShowCmd = CWWindowShow;//保存主窗口显示方式
	//////////初始化
	m_WszWndName = (char*)malloc(sizeof(char)*CWCHARlen);
	strcpy(m_WszWndName, CWWndClassName);
	m_WndClass = {};
	m_CreateWindowExInfo = {};
	m_WindowHwnd = NULL;
	m_lpWinProc = nullptr;
}


CWndFrame::~CWndFrame()
{
	//释放动态内存
	free(m_WszWndName);
}

//获取程序事例
VOID CWndFrame::CWGetHinstance(HINSTANCE hInstance)
{
	m_Hinstance = hInstance;
}

//获取程序显示方法
VOID CWndFrame::CWGetCmdShow(int nCmdShow)
{
	m_ShowCmd = nCmdShow;
}

CWndFrame* CWndFrame::CWGetStaticPoint(CWndFrame* WindowPoint/*=NULL*/)
{
	if (WindowPoint != NULL)
	{
		m_CWindows = WindowPoint;
	}
	return m_CWindows;
}


///窗口信息处理
int CWndFrame::CWMsgProc()
{
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

BOOL CWndFrame::CWCheckMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = FALSE;
	for (auto it : m_EventList)
	{
		if (it == message)
		{
			//这里查看信息，有就调用指定函数进行处理
			WinProcInfo ProcInfoTemp = {0};
			ProcInfoTemp.hWnd = hwnd;
			ProcInfoTemp.lParam = lParam;
			ProcInfoTemp.message = message;
			ProcInfoTemp.wParam = wParam;
			if (it == WM_HSCROLL || it == WM_VSCROLL)
				CWDefaultScrollBarEvent(&ProcInfoTemp);
			if (m_lpWinProc != nullptr)
				m_lpWinProc(&ProcInfoTemp);
			///标记为处理了，后面不需要处理了额
			bRet = TRUE;
			break;
		}
	}
	return bRet;
}

VOID CWndFrame::CWBaseCreateWindowExInfo()
{
	m_CreateWindowExInfo.dwExStyle = NULL;
	m_CreateWindowExInfo.dwStyle = WS_OVERLAPPEDWINDOW;
	m_CreateWindowExInfo.hInstance = m_Hinstance;
	m_CreateWindowExInfo.hMenu = NULL;
	m_CreateWindowExInfo.hWndParent = NULL;
	m_CreateWindowExInfo.lpClassName = m_WszWndName;
	m_CreateWindowExInfo.lpParam = NULL;
	m_CreateWindowExInfo.lpWindowName = m_WszWndName;
	m_CreateWindowExInfo.nHeight = CWnHeight;
	m_CreateWindowExInfo.nWidth = CWnWidth;
	m_CreateWindowExInfo.X = CWX;
	m_CreateWindowExInfo.Y = CWY;
}

//窗口过程处理函数
LRESULT CALLBACK CWndFrame::CWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//这个是静态成员函数，所有不能直接使用非静态成员，所以我们要使用一些技巧
	//我们这里就是使用了间接法
	CWndFrame* WindowProc = CWGetStaticPoint();

	int ExitCode = 0;
	if (!WindowProc->CWCheckMessage(hwnd, message, wParam, lParam))
	{
		if (message == WM_CLOSE)PostQuitMessage(0);
		else		//如果前面没处理的话，那就让系统默认处理吧
			ExitCode = DefWindowProc(hwnd, message, wParam, lParam);
	}
	return ExitCode;
}


BOOL CWndFrame::CWRegisterClassEx(WNDCLASSEX wnd)
{
	if (wnd.cbSize == NULL)
	{
		m_WndClass.cbSize = sizeof(WNDCLASSEX);
		m_WndClass.hInstance = m_Hinstance;
		m_WndClass.cbClsExtra = 0;
		m_WndClass.cbWndExtra = 0;
		m_WndClass.style = CS_HREDRAW | CS_VREDRAW;
		m_WndClass.lpfnWndProc = CWindowProc;
		m_WndClass.lpszClassName = m_WszWndName;
		m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	}
	else
	{
		memcpy((void*)&m_WndClass, (void*)&wnd, sizeof(WNDCLASSEX));
	}
	return RegisterClassEx(&m_WndClass);
}

HANDLE CWndFrame::CWCreateWindowExA(_In_ DWORD dwExStyle /*= NULL*/, _In_opt_ LPCSTR lpClassName /*= NULL*/, _In_opt_ LPCSTR lpWindowName /*= NULL*/, _In_ DWORD dwStyle /*= NULL*/, _In_ int X /*= NULL*/, _In_ int Y /*= NULL*/, _In_ int nWidth /*= NULL*/, _In_ int nHeight /*= NULL*/, _In_opt_ HWND hWndParent /*= NULL*/, _In_opt_ HMENU hMenu /*= NULL*/, _In_opt_ HINSTANCE hInstance/*=NULL*/, _In_opt_ LPVOID lpParam/*=NULL*/)
{
	//设置默认窗口信息
	CWBaseCreateWindowExInfo();
	//注册窗口类
	if (!CWRegisterClassEx())return NULL;

	if (dwExStyle != NULL)
		m_CreateWindowExInfo.dwExStyle = dwExStyle;

	if (lpClassName != NULL)
		m_CreateWindowExInfo.lpClassName = lpClassName;

	if (lpWindowName != NULL)
		m_CreateWindowExInfo.lpWindowName = lpWindowName;

	if (dwStyle != NULL)
		m_CreateWindowExInfo.dwStyle = dwStyle;

	if (X != NULL)
		m_CreateWindowExInfo.X = X;

	if (Y != NULL)
		m_CreateWindowExInfo.Y = Y;

	if (nWidth != NULL)
		m_CreateWindowExInfo.nWidth = nWidth;

	if (nHeight != NULL)
		m_CreateWindowExInfo.nHeight = nHeight;

	if (hWndParent != NULL)
		m_CreateWindowExInfo.hWndParent = hWndParent;

	if (hMenu != NULL)
		m_CreateWindowExInfo.hMenu = hMenu;

	if (hInstance != NULL)
		m_CreateWindowExInfo.hInstance = hInstance;

	if (lpParam != NULL)
		m_CreateWindowExInfo.lpParam = lpParam;

	//创建窗口
	m_WindowHwnd = CreateWindowExA(m_CreateWindowExInfo.dwExStyle, m_CreateWindowExInfo.lpClassName,
		m_CreateWindowExInfo.lpWindowName, m_CreateWindowExInfo.dwStyle,
		m_CreateWindowExInfo.X, m_CreateWindowExInfo.Y,
		m_CreateWindowExInfo.nWidth, m_CreateWindowExInfo.nHeight,
		m_CreateWindowExInfo.hWndParent, m_CreateWindowExInfo.hMenu,
		m_CreateWindowExInfo.hInstance, m_CreateWindowExInfo.lpParam);

	if (m_WindowHwnd == NULL)return NULL;

	//显示和更新窗口
	ShowWindow(m_WindowHwnd, m_ShowCmd);
	UpdateWindow(m_WindowHwnd);

	return m_WindowHwnd;
}

//设置窗口函数处理过程
VOID CWndFrame::CWSetWindowProc(VOID(*lpfn)(PWinProcInfo))
{
	if (lpfn == nullptr)return;
	m_lpWinProc = lpfn;
}

VOID CWndFrame::CWAddEvent(UINT message)
{
	BOOL bRet = FALSE;
	for (auto it : m_EventList)
	{
		//判断这个消息是不是在列表里面了，在了的话就不用在加进去了
		if (it == message)
			bRet = TRUE;
	}
	if (!bRet)
	{
		//如果不在的话就加进去
		m_EventList.push_back(message);
	}
}

//删除一个要处理的窗口过程消息
VOID CWndFrame::CWDeleteEvent(UINT message)
{
	for (EventList::iterator it = m_EventList.begin(); it != m_EventList.end(); it++)
	{
		if (*it == message)
		{
			m_EventList.erase(it);
			break;//一定要这个
		}
	}
}

//设置主窗口大小
VOID CWndFrame::CWSetMainWindowSize(int Wide, int High)
{
	RECT RectTemp = { 0 };
	if (GetWindowRect(m_WindowHwnd, &RectTemp) == NULL)return;
	MoveWindow(m_WindowHwnd, RectTemp.left,RectTemp.top, Wide, High, FALSE);
}

//设置主窗口位置
VOID CWndFrame::CWSetMainWindowPos(int X, int Y)
{
	RECT RectTemp = { 0 };
	if (GetWindowRect(m_WindowHwnd, &RectTemp) == NULL)return;
	MoveWindow(m_WindowHwnd, X, Y, RectTemp.right-RectTemp.left, RectTemp.bottom-RectTemp.top, FALSE);
}

//设置窗口或者控件的风格
LONG CWndFrame::CWSetStyle(HWND hWnd,LONG style)
{
	if (hWnd == NULL)return -1;
	return SetWindowLongA(hWnd, GWL_STYLE, style);
}

//隐藏窗口或者控件
VOID CWndFrame::CWSetHideStyle(HWND hWnd)
{
	if (hWnd = NULL)return;
	ShowWindow(hWnd, SW_HIDE);
}

//判断窗口或者控件是否可见
BOOL CWndFrame::CWGetVisible(HWND hWnd)
{
	if (hWnd == NULL)return FALSE;
	return IsWindowVisible(hWnd);
}

//给指定句柄设置一个新的ID
LONG CWndFrame::CWSetNewID(HWND hWnd, LONG NewId)
{
	if (hWnd == NULL)return -1;
	return SetWindowLongA(hWnd, GWL_ID,NewId);
}

//初始化按钮信息
VOID CWndFrame::CWBaseButtonInfo()
{
	m_CreateWindowExInfo.dwExStyle = NULL;
	m_CreateWindowExInfo.dwStyle = WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON ;
	m_CreateWindowExInfo.hInstance = m_Hinstance;
	m_CreateWindowExInfo.hMenu = (HMENU)CWButtonID;
	m_CreateWindowExInfo.hWndParent = m_WindowHwnd;
	m_CreateWindowExInfo.lpClassName = CWButton;
	m_CreateWindowExInfo.lpParam = NULL;
	m_CreateWindowExInfo.lpWindowName = CWButtonName;
	m_CreateWindowExInfo.nHeight = CWButtonnHeight;
	m_CreateWindowExInfo.nWidth = CWButtonnWidth;
	m_CreateWindowExInfo.X = CWButtonX;
	m_CreateWindowExInfo.Y = CWButtonY;
}

//寻找指定按钮的迭代器
BOOL CWndFrame::CWFindButton(HWND hwnd, ButtonIDList::iterator& ls)
{
	BOOL bRet = FALSE;
	if (hwnd == NULL)return bRet;
	for (ButtonIDList::iterator it = m_ButtonIDList.begin(); it != m_ButtonIDList.end(); it++)
	{
		if (it->hwndinfo.ButtonHwnd == hwnd)
		{
			ls = it;
			bRet = TRUE;
			break;
		}
	}
	return bRet;
}

//添加一个按钮
HWND CWndFrame::CWAddButton(_In_ DWORD dwExStyle /*= NULL*/, _In_opt_ LPCSTR lpClassName /*= NULL*/, _In_opt_ LPCSTR lpWindowName /*= NULL*/, _In_ DWORD dwStyle /*= NULL*/, _In_ int X /*= NULL*/, _In_ int Y /*= NULL*/, _In_ int nWidth /*= NULL*/, _In_ int nHeight /*= NULL*/, _In_opt_ HWND hWndParent /*= NULL*/, _In_opt_ HMENU hMenu /*= NULL*/, _In_opt_ HINSTANCE hInstance /*= NULL*/, _In_opt_ LPVOID lpParam /*= NULL*/)
{
	CWBaseButtonInfo();

	if (dwExStyle != NULL)
		m_CreateWindowExInfo.dwExStyle = dwExStyle;

	if (lpClassName != NULL)
		m_CreateWindowExInfo.lpClassName = lpClassName;

	if (lpWindowName != NULL)
		m_CreateWindowExInfo.lpWindowName = lpWindowName;

	if (dwStyle != NULL)
		m_CreateWindowExInfo.dwStyle = dwStyle;

	if (X != NULL)
		m_CreateWindowExInfo.X = X;

	if (Y != NULL)
		m_CreateWindowExInfo.Y = Y;

	if (nWidth != NULL)
		m_CreateWindowExInfo.nWidth = nWidth;

	if (nHeight != NULL)
		m_CreateWindowExInfo.nHeight = nHeight;

	if (hWndParent != NULL)
		m_CreateWindowExInfo.hWndParent = hWndParent;

	if (hMenu != NULL)
		m_CreateWindowExInfo.hMenu = hMenu;

	if (hInstance != NULL)
		m_CreateWindowExInfo.hInstance = hInstance;

	if (lpParam != NULL)
		m_CreateWindowExInfo.lpParam = lpParam;

	ButtonId ButtonIdTemp;

	ButtonIdTemp.hwndinfo.ButtonHwnd = CreateWindowExA(m_CreateWindowExInfo.dwExStyle, m_CreateWindowExInfo.lpClassName, m_CreateWindowExInfo.lpWindowName, m_CreateWindowExInfo.dwStyle,
		m_CreateWindowExInfo.X, m_CreateWindowExInfo.Y, m_CreateWindowExInfo.nWidth, m_CreateWindowExInfo.nHeight,
		m_CreateWindowExInfo.hWndParent, m_CreateWindowExInfo.hMenu, m_CreateWindowExInfo.hInstance, m_CreateWindowExInfo.lpParam);

	if (ButtonIdTemp.hwndinfo.ButtonHwnd != NULL)
	{
		ButtonIdTemp.hwndinfo.ButtonNumber = (UINT)m_CreateWindowExInfo.hMenu;
		m_ButtonIDList.push_back(ButtonIdTemp);
	}

	return ButtonIdTemp.hwndinfo.ButtonHwnd;
}

//添加一个二选复选框
HWND CWndFrame::CWAddAutoCheckBoxButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonCheckBox);
}

//添加一个三选复选框
HWND CWndFrame::CWAddAuto3StateButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonState);
}

//添加一个单选框
HWND CWndFrame::CWAddAutoRadioButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonRadio);
}

//添加一个分组框
HWND CWndFrame::CWAddGroupBoxButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonGroup);
}

//删除一个按钮
VOID CWndFrame::CWDeleteButton(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return;
	ButtonIDList::iterator ls;
	if (CWFindButton(ButtonHwnd, ls))
	{
		DestroyWindow(ls->hwndinfo.ButtonHwnd);
		if (ls->hBitmap != NULL)
			DeleteObject(ls->hBitmap);
		m_ButtonIDList.erase(ls);
	}
}

//删除所有按钮
VOID CWndFrame::CWDeleteAllButton()
{
	for (ButtonIDList::iterator it = m_ButtonIDList.begin(); it != m_ButtonIDList.end(); it++)
	{
		DestroyWindow(it->hwndinfo.ButtonHwnd);
		if (it->hBitmap != NULL)
			DeleteObject(it->hBitmap);
	}
	//删除后在清空
	m_ButtonIDList.clear();
}

//添加一张位图给按钮
VOID CWndFrame::CWAddBmpToButton(HWND ButtonHwnd, CHAR* pFile, int nWidth, int nHeight)
{
	if (ButtonHwnd == NULL || pFile == nullptr || nWidth == NULL || nHeight == NULL)return;
	ButtonIDList::iterator ls;
	if (CWFindButton(ButtonHwnd, ls))
	{
		ls->hBitmap = (HBITMAP)LoadImageA(NULL, pFile, IMAGE_BITMAP, nWidth, nHeight, LR_LOADFROMFILE);
		if (ls->hBitmap != NULL)
		{
			SendMessage(ButtonHwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ls->hBitmap);
		}
	}
}

//移动按钮位置
VOID CWndFrame::CWMoveButtonPos(HWND ButtonHwnd,int X, int Y)
{
	if (ButtonHwnd == NULL)return;
	RECT RectTemp = { 0 };
	if (GetWindowRect(ButtonHwnd, &RectTemp) == NULL)return;
	MoveWindow(ButtonHwnd, X, Y, (RectTemp.right-RectTemp.left), (RectTemp.bottom-RectTemp.top), FALSE);
}

//设置按钮大小
VOID CWndFrame::CWSetButtonSize(HWND ButtonHwnd, int Wide, int High)
{
	if (ButtonHwnd == NULL)return;
	RECT RectWindow = { 0 };
	RECT RectButton = { 0 };
	if (GetWindowRect(m_WindowHwnd, &RectWindow) == NULL)return;
	if (GetWindowRect(ButtonHwnd, &RectButton) == NULL)return;
	//我也不知道，但是非客户区的上是30，左边是8吧
	MoveWindow(ButtonHwnd, RectButton.left-RectWindow.left-8,RectButton.top-RectWindow.top-30, Wide, High, FALSE);
}

//设置按钮的字符串
BOOL CWndFrame::CWSetButtonString(HWND Buttonhwnd, CHAR* ButtonString)
{
	if (Buttonhwnd == NULL)return FALSE;
	return SetWindowTextA(Buttonhwnd, ButtonString);
}

//获取按钮的字符串
int CWndFrame::CWGetButtonString(HWND Buttonhwnd, CHAR* ButtonString)
{
	if (Buttonhwnd == NULL)return -1;
	return GetWindowTextA(Buttonhwnd, ButtonString, MAX_PATH);
}

//设置按钮的当前状态
LRESULT CWndFrame::CWSetButtonCheck(HWND ButtonHwnd, UINT Check)
{
	if (ButtonHwnd == NULL)return -1;
	return SendMessageA(ButtonHwnd, BM_SETCHECK, Check, 0);
}

//获取按钮的当前状态
LRESULT CWndFrame::CWGetButtonCheck(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return -1;
	return SendMessageA(ButtonHwnd, BM_GETCHECK, 0, 0);
}

//禁用按钮
VOID CWndFrame::CWProhibitButton(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return;
	EnableWindow(ButtonHwnd,FALSE);
}

//启用按钮
VOID CWndFrame::CWEnableButton(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return;
	EnableWindow(ButtonHwnd, TRUE);
}

//初始化编辑框基本信息
VOID CWndFrame::CWBaseEditInfo()
{
	m_CreateWindowExInfo.dwExStyle = 0;
	m_CreateWindowExInfo.dwStyle = CWEditStyle;
	m_CreateWindowExInfo.hInstance = m_Hinstance;
	m_CreateWindowExInfo.hMenu = (HMENU)CWEditID;
	m_CreateWindowExInfo.hWndParent = m_WindowHwnd;
	m_CreateWindowExInfo.lpClassName = CWEdit;
	m_CreateWindowExInfo.lpParam = NULL;
	m_CreateWindowExInfo.lpWindowName = CWEditName;
	m_CreateWindowExInfo.nHeight = CWEditHeight;
	m_CreateWindowExInfo.nWidth = CWEditWidth;
	m_CreateWindowExInfo.X = CWEditX;
	m_CreateWindowExInfo.Y = CWEditY;
}

//查找指定的编辑框句柄
BOOL CWndFrame::CWFindEdit(HWND, EditList::iterator&)
{
	return FALSE;
}

//添加一个编辑框
HWND CWndFrame::CWAddEdit(_In_ DWORD dwExStyle /*= NULL*/, _In_opt_ LPCSTR lpClassName /*= NULL*/, _In_opt_ LPCSTR lpWindowName /*= NULL*/, _In_ DWORD dwStyle /*= NULL*/, _In_ int X /*= NULL*/, _In_ int Y /*= NULL*/, _In_ int nWidth /*= NULL*/, _In_ int nHeight /*= NULL*/, _In_opt_ HWND hWndParent /*= NULL*/, _In_opt_ HMENU hMenu /*= NULL*/, _In_opt_ HINSTANCE hInstance /*= NULL*/, _In_opt_ LPVOID lpParam /*= NULL*/)
{
	CWBaseEditInfo();

	if (dwExStyle != NULL)
		m_CreateWindowExInfo.dwExStyle = dwExStyle;

	if (lpClassName != NULL)
		m_CreateWindowExInfo.lpClassName = lpClassName;

	if (lpWindowName != NULL)
		m_CreateWindowExInfo.lpWindowName = lpWindowName;

	if (dwStyle != NULL)
		m_CreateWindowExInfo.dwStyle = dwStyle;

	if (X != NULL)
		m_CreateWindowExInfo.X = X;

	if (Y != NULL)
		m_CreateWindowExInfo.Y = Y;

	if (nWidth != NULL)
		m_CreateWindowExInfo.nWidth = nWidth;

	if (nHeight != NULL)
		m_CreateWindowExInfo.nHeight = nHeight;

	if (hWndParent != NULL)
		m_CreateWindowExInfo.hWndParent = hWndParent;

	if (hMenu != NULL)
		m_CreateWindowExInfo.hMenu = hMenu;

	if (hInstance != NULL)
		m_CreateWindowExInfo.hInstance = hInstance;

	if (lpParam != NULL)
		m_CreateWindowExInfo.lpParam = lpParam;

	EditInfo EditInfoTemp;

	EditInfoTemp.hwndInfo.ButtonHwnd = CreateWindowExA(m_CreateWindowExInfo.dwExStyle, m_CreateWindowExInfo.lpClassName, m_CreateWindowExInfo.lpWindowName, m_CreateWindowExInfo.dwStyle,
		m_CreateWindowExInfo.X, m_CreateWindowExInfo.Y, m_CreateWindowExInfo.nWidth, m_CreateWindowExInfo.nHeight,
		m_CreateWindowExInfo.hWndParent, m_CreateWindowExInfo.hMenu, m_CreateWindowExInfo.hInstance, m_CreateWindowExInfo.lpParam);

	if (EditInfoTemp.hwndInfo.ButtonHwnd != NULL)
	{
		EditInfoTemp.hwndInfo.ButtonNumber = (UINT)m_CreateWindowExInfo.hMenu;
		m_EditList.push_back(EditInfoTemp);
	}

	return EditInfoTemp.hwndInfo.ButtonHwnd;
}

//删除一个编辑框
VOID CWndFrame::CWDeleteEdit()
{

}

//删除全部编辑框
VOID CWndFrame::CWDeleteAllEdit()
{

}

//设置编辑框字符串
VOID CWndFrame::CWSetEditString(HWND EditHwnd, CHAR* EditString)
{
	if (EditHwnd == NULL)return;
	SetWindowTextA(EditHwnd, EditString);
}

////获取编辑框字符串
VOID CWndFrame::CWGetEditString(HWND EditHwnd, CHAR* EditString)
{
	if (EditHwnd == NULL )return;
	GetWindowTextA(EditHwnd, EditString, MAX_PATH);
}

//默认滚动条处理事件
VOID CWndFrame::CWDefaultScrollBarEvent(PWinProcInfo pWinProcTemp)
{
	ScrollBarList::iterator ScrollBarTemp;
	int nID = GetWindowLongA((HWND)pWinProcTemp->lParam,GWL_ID);
	if (!CWFindSrcollBar(nID, ScrollBarTemp))return;

	if (ScrollBarTemp->Vert)
	{
		switch (LOWORD(pWinProcTemp->wParam))
		{
		case SB_PAGEUP:
			ScrollBarTemp->CurrentIndex -= ScrollBarTemp->PageGranularity;
			break;
		case SB_PAGEDOWN:
			ScrollBarTemp->CurrentIndex += ScrollBarTemp->PageGranularity;
			break;
		case SB_LINEUP:
			ScrollBarTemp->CurrentIndex -= ScrollBarTemp->LineGranularity;
			break;
		case SB_LINEDOWN:
			ScrollBarTemp->CurrentIndex += ScrollBarTemp->LineGranularity;
			break;
		case SB_THUMBPOSITION:
			ScrollBarTemp->CurrentIndex = HIWORD(pWinProcTemp->wParam);
			break;
		case SB_TOP:
			ScrollBarTemp->CurrentIndex = ScrollBarTemp->Min;
			break;
		case SB_BOTTOM:
			ScrollBarTemp->CurrentIndex = ScrollBarTemp->Max;
			break;
		}
	}
	else
	{
		switch (LOWORD(pWinProcTemp->wParam))
		{
		case SB_PAGELEFT:
			ScrollBarTemp->CurrentIndex -= ScrollBarTemp->PageGranularity;
			break;
		case SB_PAGERIGHT:
			ScrollBarTemp->CurrentIndex += ScrollBarTemp->PageGranularity;
			break;
		case SB_LINELEFT:
			ScrollBarTemp->CurrentIndex -= ScrollBarTemp->LineGranularity;
			break;
		case SB_LINERIGHT:
			ScrollBarTemp->CurrentIndex += ScrollBarTemp->LineGranularity;
			break;
		case SB_THUMBPOSITION:
			ScrollBarTemp->CurrentIndex = HIWORD(pWinProcTemp->wParam);
			break;
		case SB_TOP:
			ScrollBarTemp->CurrentIndex = ScrollBarTemp->Min;
			break;
		case SB_BOTTOM:
			ScrollBarTemp->CurrentIndex = ScrollBarTemp->Max;
			break;
		}
	}
	SetScrollPos(ScrollBarTemp->hwndInfo.ButtonHwnd,SB_CTL,ScrollBarTemp->CurrentIndex,TRUE);
}
//设置基本滚动条信息
VOID CWndFrame::CWBaseScrollBarInfo()
{
	m_CreateWindowExInfo.dwExStyle = 0;
	m_CreateWindowExInfo.dwStyle = CWScrollBarVertStyle;
	m_CreateWindowExInfo.hInstance = m_Hinstance;
	m_CreateWindowExInfo.hMenu = (HMENU)CWScrollBarId;
	m_CreateWindowExInfo.hWndParent = m_WindowHwnd;
	m_CreateWindowExInfo.lpClassName = CWScrollBar;
	m_CreateWindowExInfo.lpParam = NULL;
	m_CreateWindowExInfo.lpWindowName = CWScrollBarName;
	m_CreateWindowExInfo.nHeight = CWScrollBarHeight;
	m_CreateWindowExInfo.nWidth = CWScrollBarWidth;
	m_CreateWindowExInfo.X = CWScrollBarX;
	m_CreateWindowExInfo.Y = CWScrollBarY;
}

//查找滚动条
BOOL CWndFrame::CWFindSrcollBar(HWND ScrollBarHwnd, ScrollBarList::iterator& pScrollBar)
{
	BOOL bRet = FALSE;
	if (ScrollBarHwnd == NULL)return bRet;
	for (ScrollBarList::iterator it = m_ScrollBarList.begin(); it != m_ScrollBarList.end();it++)
	{
		if (it->hwndInfo.ButtonHwnd == ScrollBarHwnd)
		{
			pScrollBar = it;
			bRet = TRUE;
			break;
		}
	}
	return bRet;
}

//查找滚动条
BOOL CWndFrame::CWFindSrcollBar(int nID, ScrollBarList::iterator& pScrollBar)
{
	BOOL bRet = FALSE;
	if (nID == NULL)return bRet;
	for (ScrollBarList::iterator it = m_ScrollBarList.begin(); it != m_ScrollBarList.end(); it++)
	{
		if (it->hwndInfo.ButtonNumber == nID)
		{
			pScrollBar = it;
			bRet = TRUE;
			break;
		}
	}
	return bRet;
}

//添加一个滚动条控件
HWND CWndFrame::CWAddScrollBar(_In_ DWORD dwExStyle /*= NULL*/, _In_opt_ LPCSTR lpClassName /*= NULL*/, _In_opt_ LPCSTR lpWindowName /*= NULL*/, _In_ DWORD dwStyle /*= NULL*/, _In_ int X /*= NULL*/, _In_ int Y /*= NULL*/, _In_ int nWidth /*= NULL*/, _In_ int nHeight /*= NULL*/, _In_opt_ HWND hWndParent /*= NULL*/, _In_opt_ HMENU hMenu /*= NULL*/, _In_opt_ HINSTANCE hInstance /*= NULL*/, _In_opt_ LPVOID lpParam /*= NULL*/)
{
	CWBaseScrollBarInfo();

	if (dwExStyle != NULL)
		m_CreateWindowExInfo.dwExStyle = dwExStyle;

	if (lpClassName != NULL)
		m_CreateWindowExInfo.lpClassName = lpClassName;

	if (lpWindowName != NULL)
		m_CreateWindowExInfo.lpWindowName = lpWindowName;

	if (dwStyle != NULL)
		m_CreateWindowExInfo.dwStyle = dwStyle;

	if (X != NULL)
		m_CreateWindowExInfo.X = X;

	if (Y != NULL)
		m_CreateWindowExInfo.Y = Y;

	if (nWidth != NULL)
		m_CreateWindowExInfo.nWidth = nWidth;

	if (nHeight != NULL)
		m_CreateWindowExInfo.nHeight = nHeight;

	if (hWndParent != NULL)
		m_CreateWindowExInfo.hWndParent = hWndParent;

	if (hMenu != NULL)
		m_CreateWindowExInfo.hMenu = hMenu;

	if (hInstance != NULL)
		m_CreateWindowExInfo.hInstance = hInstance;

	if (lpParam != NULL)
		m_CreateWindowExInfo.lpParam = lpParam;

	ScrollBarInfo ScrollBarTemp;

	ScrollBarTemp.hwndInfo.ButtonHwnd = CreateWindowExA(m_CreateWindowExInfo.dwExStyle, m_CreateWindowExInfo.lpClassName, m_CreateWindowExInfo.lpWindowName, m_CreateWindowExInfo.dwStyle,
		m_CreateWindowExInfo.X, m_CreateWindowExInfo.Y, m_CreateWindowExInfo.nWidth, m_CreateWindowExInfo.nHeight,
		m_CreateWindowExInfo.hWndParent, m_CreateWindowExInfo.hMenu, m_CreateWindowExInfo.hInstance, m_CreateWindowExInfo.lpParam);

	if (ScrollBarTemp.hwndInfo.ButtonHwnd != NULL)
	{
		ScrollBarTemp.hwndInfo.ButtonNumber = (int)m_CreateWindowExInfo.hMenu;
		m_ScrollBarList.push_back(ScrollBarTemp);
		if (m_CreateWindowExInfo.dwStyle&SB_VERT)
			ScrollBarTemp.Vert = true;
		else 
			ScrollBarTemp.Vert = false;
	}

	return ScrollBarTemp.hwndInfo.ButtonHwnd;
}

//设置默认滚动条处理事件
VOID CWndFrame::CWSetDefaultScrollBarEvent()
{
	CWAddEvent(WM_VSCROLL);
	CWAddEvent(WM_HSCROLL);
}

//设置滚动条最大值
VOID CWndFrame::CWSetScrollBarMinAndMax(HWND ScrollBarHwnd, int MinValue,int MaxValue)
{
	if (ScrollBarHwnd == NULL)return;
	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		ScrollBarTemp->Max = MaxValue;
		ScrollBarTemp->Min = MinValue;
		SetScrollRange(ScrollBarTemp->hwndInfo.ButtonHwnd, SB_CTL, MinValue, MaxValue, TRUE);
	}
}

//设置滚动条当前的值
VOID CWndFrame::CWSetScrollBarCurrentIndex(HWND ScrollBarHwnd, int CurrentValue)
{
	if (ScrollBarHwnd == NULL)return;
	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		ScrollBarTemp->CurrentIndex = CurrentValue;
		SetScrollPos(ScrollBarTemp->hwndInfo.ButtonHwnd, SB_CTL, ScrollBarTemp->CurrentIndex, TRUE);
	}
}

//设置滚动条行粒度
VOID CWndFrame::CWSetScrollBarLineGranularity(HWND ScrollBarHwnd, int LineValue)
{
	if (ScrollBarHwnd == NULL)return;

	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		ScrollBarTemp->LineGranularity = LineValue;
	}
}

//设置滚动条页粒度
VOID CWndFrame::CWSetScrollBarPageGranularity(HWND ScrollBarHwnd, int PageValue)
{
	if (ScrollBarHwnd == NULL)return;

	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		ScrollBarTemp->PageGranularity = PageValue;
	}
}

//获取当前滚动条的值
int CWndFrame::CWGetCurrentScrollBarValue(HWND ScrollBarHwnd)
{
	int nCurrent = -1;
	if (ScrollBarHwnd == NULL)return nCurrent;
	
	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		nCurrent = ScrollBarTemp->CurrentIndex;
	}
	return nCurrent;
}

