#include "WndFrame.h"

CWndFrame* CWndFrame::m_CWindows = NULL;

CWndFrame::CWndFrame()
{
	m_Hinstance = NULL;//�������ʵ��
	m_ShowCmd = CWWindowShow;//������������ʾ��ʽ
	//////////��ʼ��
	m_WszWndName = (char*)malloc(sizeof(char)*CWCHARlen);
	strcpy(m_WszWndName, CWWndClassName);
	m_WndClass = {};
	m_CreateWindowExInfo = {};
	m_WindowHwnd = NULL;
	m_lpWinProc = nullptr;
}


CWndFrame::~CWndFrame()
{
	//�ͷŶ�̬�ڴ�
	free(m_WszWndName);
}

//��ȡ��������
VOID CWndFrame::CWGetHinstance(HINSTANCE hInstance)
{
	m_Hinstance = hInstance;
}

//��ȡ������ʾ����
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


///������Ϣ����
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
			//����鿴��Ϣ���о͵���ָ���������д���
			WinProcInfo ProcInfoTemp = {0};
			ProcInfoTemp.hWnd = hwnd;
			ProcInfoTemp.lParam = lParam;
			ProcInfoTemp.message = message;
			ProcInfoTemp.wParam = wParam;
			if (it == WM_HSCROLL || it == WM_VSCROLL)
				CWDefaultScrollBarEvent(&ProcInfoTemp);
			if (m_lpWinProc != nullptr)
				m_lpWinProc(&ProcInfoTemp);
			///���Ϊ�����ˣ����治��Ҫ�����˶�
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

//���ڹ��̴�����
LRESULT CALLBACK CWndFrame::CWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//����Ǿ�̬��Ա���������в���ֱ��ʹ�÷Ǿ�̬��Ա����������Ҫʹ��һЩ����
	//�����������ʹ���˼�ӷ�
	CWndFrame* WindowProc = CWGetStaticPoint();

	int ExitCode = 0;
	if (!WindowProc->CWCheckMessage(hwnd, message, wParam, lParam))
	{
		if (message == WM_CLOSE)PostQuitMessage(0);
		else		//���ǰ��û����Ļ����Ǿ���ϵͳĬ�ϴ����
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
	//����Ĭ�ϴ�����Ϣ
	CWBaseCreateWindowExInfo();
	//ע�ᴰ����
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

	//��������
	m_WindowHwnd = CreateWindowExA(m_CreateWindowExInfo.dwExStyle, m_CreateWindowExInfo.lpClassName,
		m_CreateWindowExInfo.lpWindowName, m_CreateWindowExInfo.dwStyle,
		m_CreateWindowExInfo.X, m_CreateWindowExInfo.Y,
		m_CreateWindowExInfo.nWidth, m_CreateWindowExInfo.nHeight,
		m_CreateWindowExInfo.hWndParent, m_CreateWindowExInfo.hMenu,
		m_CreateWindowExInfo.hInstance, m_CreateWindowExInfo.lpParam);

	if (m_WindowHwnd == NULL)return NULL;

	//��ʾ�͸��´���
	ShowWindow(m_WindowHwnd, m_ShowCmd);
	UpdateWindow(m_WindowHwnd);

	return m_WindowHwnd;
}

//���ô��ں����������
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
		//�ж������Ϣ�ǲ������б������ˣ����˵Ļ��Ͳ����ڼӽ�ȥ��
		if (it == message)
			bRet = TRUE;
	}
	if (!bRet)
	{
		//������ڵĻ��ͼӽ�ȥ
		m_EventList.push_back(message);
	}
}

//ɾ��һ��Ҫ����Ĵ��ڹ�����Ϣ
VOID CWndFrame::CWDeleteEvent(UINT message)
{
	for (EventList::iterator it = m_EventList.begin(); it != m_EventList.end(); it++)
	{
		if (*it == message)
		{
			m_EventList.erase(it);
			break;//һ��Ҫ���
		}
	}
}

//���������ڴ�С
VOID CWndFrame::CWSetMainWindowSize(int Wide, int High)
{
	RECT RectTemp = { 0 };
	if (GetWindowRect(m_WindowHwnd, &RectTemp) == NULL)return;
	MoveWindow(m_WindowHwnd, RectTemp.left,RectTemp.top, Wide, High, FALSE);
}

//����������λ��
VOID CWndFrame::CWSetMainWindowPos(int X, int Y)
{
	RECT RectTemp = { 0 };
	if (GetWindowRect(m_WindowHwnd, &RectTemp) == NULL)return;
	MoveWindow(m_WindowHwnd, X, Y, RectTemp.right-RectTemp.left, RectTemp.bottom-RectTemp.top, FALSE);
}

//���ô��ڻ��߿ؼ��ķ��
LONG CWndFrame::CWSetStyle(HWND hWnd,LONG style)
{
	if (hWnd == NULL)return -1;
	return SetWindowLongA(hWnd, GWL_STYLE, style);
}

//���ش��ڻ��߿ؼ�
VOID CWndFrame::CWSetHideStyle(HWND hWnd)
{
	if (hWnd = NULL)return;
	ShowWindow(hWnd, SW_HIDE);
}

//�жϴ��ڻ��߿ؼ��Ƿ�ɼ�
BOOL CWndFrame::CWGetVisible(HWND hWnd)
{
	if (hWnd == NULL)return FALSE;
	return IsWindowVisible(hWnd);
}

//��ָ���������һ���µ�ID
LONG CWndFrame::CWSetNewID(HWND hWnd, LONG NewId)
{
	if (hWnd == NULL)return -1;
	return SetWindowLongA(hWnd, GWL_ID,NewId);
}

//��ʼ����ť��Ϣ
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

//Ѱ��ָ����ť�ĵ�����
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

//���һ����ť
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

//���һ����ѡ��ѡ��
HWND CWndFrame::CWAddAutoCheckBoxButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonCheckBox);
}

//���һ����ѡ��ѡ��
HWND CWndFrame::CWAddAuto3StateButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonState);
}

//���һ����ѡ��
HWND CWndFrame::CWAddAutoRadioButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonRadio);
}

//���һ�������
HWND CWndFrame::CWAddGroupBoxButton()
{
	return CWAddButton(NULL, NULL, NULL, CWButtonGroup);
}

//ɾ��һ����ť
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

//ɾ�����а�ť
VOID CWndFrame::CWDeleteAllButton()
{
	for (ButtonIDList::iterator it = m_ButtonIDList.begin(); it != m_ButtonIDList.end(); it++)
	{
		DestroyWindow(it->hwndinfo.ButtonHwnd);
		if (it->hBitmap != NULL)
			DeleteObject(it->hBitmap);
	}
	//ɾ���������
	m_ButtonIDList.clear();
}

//���һ��λͼ����ť
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

//�ƶ���ťλ��
VOID CWndFrame::CWMoveButtonPos(HWND ButtonHwnd,int X, int Y)
{
	if (ButtonHwnd == NULL)return;
	RECT RectTemp = { 0 };
	if (GetWindowRect(ButtonHwnd, &RectTemp) == NULL)return;
	MoveWindow(ButtonHwnd, X, Y, (RectTemp.right-RectTemp.left), (RectTemp.bottom-RectTemp.top), FALSE);
}

//���ð�ť��С
VOID CWndFrame::CWSetButtonSize(HWND ButtonHwnd, int Wide, int High)
{
	if (ButtonHwnd == NULL)return;
	RECT RectWindow = { 0 };
	RECT RectButton = { 0 };
	if (GetWindowRect(m_WindowHwnd, &RectWindow) == NULL)return;
	if (GetWindowRect(ButtonHwnd, &RectButton) == NULL)return;
	//��Ҳ��֪�������Ƿǿͻ���������30�������8��
	MoveWindow(ButtonHwnd, RectButton.left-RectWindow.left-8,RectButton.top-RectWindow.top-30, Wide, High, FALSE);
}

//���ð�ť���ַ���
BOOL CWndFrame::CWSetButtonString(HWND Buttonhwnd, CHAR* ButtonString)
{
	if (Buttonhwnd == NULL)return FALSE;
	return SetWindowTextA(Buttonhwnd, ButtonString);
}

//��ȡ��ť���ַ���
int CWndFrame::CWGetButtonString(HWND Buttonhwnd, CHAR* ButtonString)
{
	if (Buttonhwnd == NULL)return -1;
	return GetWindowTextA(Buttonhwnd, ButtonString, MAX_PATH);
}

//���ð�ť�ĵ�ǰ״̬
LRESULT CWndFrame::CWSetButtonCheck(HWND ButtonHwnd, UINT Check)
{
	if (ButtonHwnd == NULL)return -1;
	return SendMessageA(ButtonHwnd, BM_SETCHECK, Check, 0);
}

//��ȡ��ť�ĵ�ǰ״̬
LRESULT CWndFrame::CWGetButtonCheck(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return -1;
	return SendMessageA(ButtonHwnd, BM_GETCHECK, 0, 0);
}

//���ð�ť
VOID CWndFrame::CWProhibitButton(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return;
	EnableWindow(ButtonHwnd,FALSE);
}

//���ð�ť
VOID CWndFrame::CWEnableButton(HWND ButtonHwnd)
{
	if (ButtonHwnd == NULL)return;
	EnableWindow(ButtonHwnd, TRUE);
}

//��ʼ���༭�������Ϣ
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

//����ָ���ı༭����
BOOL CWndFrame::CWFindEdit(HWND, EditList::iterator&)
{
	return FALSE;
}

//���һ���༭��
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

//ɾ��һ���༭��
VOID CWndFrame::CWDeleteEdit()
{

}

//ɾ��ȫ���༭��
VOID CWndFrame::CWDeleteAllEdit()
{

}

//���ñ༭���ַ���
VOID CWndFrame::CWSetEditString(HWND EditHwnd, CHAR* EditString)
{
	if (EditHwnd == NULL)return;
	SetWindowTextA(EditHwnd, EditString);
}

////��ȡ�༭���ַ���
VOID CWndFrame::CWGetEditString(HWND EditHwnd, CHAR* EditString)
{
	if (EditHwnd == NULL )return;
	GetWindowTextA(EditHwnd, EditString, MAX_PATH);
}

//Ĭ�Ϲ����������¼�
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
//���û�����������Ϣ
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

//���ҹ�����
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

//���ҹ�����
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

//���һ���������ؼ�
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

//����Ĭ�Ϲ����������¼�
VOID CWndFrame::CWSetDefaultScrollBarEvent()
{
	CWAddEvent(WM_VSCROLL);
	CWAddEvent(WM_HSCROLL);
}

//���ù��������ֵ
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

//���ù�������ǰ��ֵ
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

//���ù�����������
VOID CWndFrame::CWSetScrollBarLineGranularity(HWND ScrollBarHwnd, int LineValue)
{
	if (ScrollBarHwnd == NULL)return;

	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		ScrollBarTemp->LineGranularity = LineValue;
	}
}

//���ù�����ҳ����
VOID CWndFrame::CWSetScrollBarPageGranularity(HWND ScrollBarHwnd, int PageValue)
{
	if (ScrollBarHwnd == NULL)return;

	ScrollBarList::iterator ScrollBarTemp;
	if (CWFindSrcollBar(ScrollBarHwnd, ScrollBarTemp))
	{
		ScrollBarTemp->PageGranularity = PageValue;
	}
}

//��ȡ��ǰ��������ֵ
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

