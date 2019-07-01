#pragma once

/*
<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0">
<assemblyIdentity
	version="1.0.0.0"
	processorArchitecture="*"
	name="CompanyName.ProductName.YourApplication"
	type="win32"
/>
<description>Your application description here.</description>
<dependency>
	<dependentAssembly>
		<assemblyIdentity
			type="win32"
			name="Microsoft.Windows.Common-Controls"
			version="6.0.0.0"
			processorArchitecture="*"
			publicKeyToken="6595b64144ccf1df"
			language="*"
		/>
	</dependentAssembly>
</dependency>
</assembly>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

关闭视觉样式
SetWindowTheme(hwnd, L" ", L" ");
*/

//设置控件的样式
#ifdef USE_STYLE
#if defined _M_IX86  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#elif defined _M_X64  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#else  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")  
#endif  
#endif

#include <Windows.h>
#include <CommCtrl.h>
#include <windowsx.h>
#include <assert.h>
#pragma comment(lib,"ComCtl32")
#include <string>
using namespace std;

/*
C++封装的Window窗口
*/

class CWindow
{
private:
	HWND m_hWnd;				//窗体的句柄
	string m_strWindowCaption;	//窗口的标题
	WNDCLASSEXA m_stWndClass;	//窗口类结构体
	HINSTANCE m_hInstance;		//程序的实例
private:
	//初始化
	void Init()
	{
		INITCOMMONCONTROLSEX stCommonInfo = { 0 };
		stCommonInfo.dwSize = sizeof(INITCOMMONCONTROLSEX);
		stCommonInfo.dwICC = ICC_ANIMATE_CLASS | ICC_BAR_CLASSES | ICC_COOL_CLASSES | ICC_DATE_CLASSES | ICC_HOTKEY_CLASS | ICC_INTERNET_CLASSES | ICC_LINK_CLASS | ICC_LISTVIEW_CLASSES | ICC_NATIVEFNTCTL_CLASS | ICC_PAGESCROLLER_CLASS | ICC_PROGRESS_CLASS | ICC_STANDARD_CLASSES | ICC_TAB_CLASSES | ICC_TREEVIEW_CLASSES | ICC_UPDOWN_CLASS | ICC_USEREX_CLASSES | ICC_WIN95_CLASSES;
		assert(InitCommonControlsEx(&stCommonInfo));

		m_hWnd = 0;
		m_strWindowCaption = "TestWindow";

		memset(&m_stWndClass, 0, sizeof(WNDCLASSEXA));
		m_stWndClass.cbSize = sizeof(WNDCLASSEXA);
		m_stWndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		m_stWndClass.hCursor = LoadCursorA(0, IDC_ARROW);
		m_stWndClass.hIcon = LoadIconA(0, IDI_EXCLAMATION);
		m_stWndClass.hInstance = m_hInstance;
		m_stWndClass.lpfnWndProc = _DefaultProc;
		m_stWndClass.lpszClassName = m_strWindowCaption.c_str();
		m_stWndClass.style = CS_VREDRAW | CS_HREDRAW;
	}

	//清理
	void Clear()
	{

	}

	//默认窗口过程
	static LRESULT CALLBACK _DefaultProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}
public:
	//GetModuleHandle(0)
	CWindow(HINSTANCE hInstance) :m_hInstance(hInstance)
	{
		Init();
	}
	~CWindow()
	{
		Clear();
	}

public:
	//设置窗口的扩展风格
	inline void SetExstyle(long lValue)const
	{
		if(m_hWnd)
			SetWindowLongA(m_hWnd, GWL_EXSTYLE, lValue);
	}

	//添加指定的拓展风格
	inline void AddExstyle(long lValue)const
	{
		if (m_hWnd)
		{
			DWORD dwExstyle = GetWindowLongA(m_hWnd, GWL_EXSTYLE);
			SetWindowLongA(m_hWnd, GWL_EXSTYLE, dwExstyle & ~lValue);
		}
	}

	//去除指定的拓展风格
	inline void RemoveExstyle(long lValue)const
	{
		if (m_hWnd)
		{
			DWORD dwExstyle = GetWindowLongA(m_hWnd, GWL_EXSTYLE);
			SetWindowLongA(m_hWnd, GWL_EXSTYLE, dwExstyle | lValue);
		}
	}

	//设置窗口的风格
	inline void SetStyle(long lValue)const
	{
		if (m_hWnd)
			SetWindowLongA(m_hWnd, GWL_STYLE, lValue);
	}

	//设置窗口的过程函数
	inline void SetWndProc(WNDPROC fWndProc)const
	{
		if (m_hWnd)
			SetWindowLongA(m_hWnd, GWL_WNDPROC, (long)fWndProc);
	}

	//设置窗口的标题
	inline void SetCaption(const char* szCaption)
	{
		m_strWindowCaption = szCaption;
		if (m_hWnd)
			SetWindowTextA(m_hWnd, m_strWindowCaption.c_str());
	}

	//设置窗口透明
	//指定透明度
	inline void SetTransparent(int nValue)const
	{
		if (nValue < 0 || nValue > 255)
			nValue = 100;
		SetExstyle(WS_EX_LAYERED);
		if (m_hWnd)
			SetLayeredWindowAttributes(m_hWnd, 0, nValue, LWA_ALPHA);
	}

	//指定透明颜色
	inline void SetTransparent(COLORREF stValue)const
	{
		SetExstyle(WS_EX_LAYERED);
		if (m_hWnd)
			SetLayeredWindowAttributes(m_hWnd, stValue, 0, LWA_COLORKEY);
	}

	//设置窗口的大小
	inline void SetWindowSize(int nValueX,int nValueY)const
	{
		RECT stRect;
		GetWindowRect(m_hWnd, &stRect);
		if (m_hWnd)
			MoveWindow(m_hWnd, stRect.left, stRect.top,nValueX, nValueY, true);
	}

	//设置窗口的位置
	inline void SetWindowLocation(int nValueX,int nValueY)const
	{
		RECT stRect;
		GetWindowRect(m_hWnd, &stRect);
		if (m_hWnd)
			MoveWindow(m_hWnd, nValueX, nValueY,
			stRect.right - stRect.left, stRect.bottom - stRect.top, true);
	}

	//获取窗口的句柄
	inline HWND GetHwnd()const
	{
		return m_hWnd;
	}

	//获取窗口的实例
	inline HINSTANCE GetHinstance()const
	{
		return m_hInstance;
	}

	//获取窗口标题
	inline string GetCaption()const
	{
		return m_strWindowCaption;
	}

public:
	//创建一个窗体
	HWND Create()
	{
		if (!RegisterClassExA(&m_stWndClass))
			return 0;

		if (m_hWnd)
			return 0;

		m_hWnd = CreateWindowExA(0, m_strWindowCaption.c_str(), m_strWindowCaption.c_str(),
			WS_OVERLAPPEDWINDOW, 100, 100, 500, 300, 0, 0, m_hInstance, 0);

		if (m_hWnd)
		{
			ShowWindow(m_hWnd, SW_SHOW);
			UpdateWindow(m_hWnd);
		}

		return m_hWnd;
	}

	//默认窗口消息循环
	int GetMsgLoop()
	{
		MSG stMsg;
		while (GetMessageA(&stMsg, 0, 0, 0))
		{
			TranslateMessage(&stMsg);
			DispatchMessageA(&stMsg);
		}
		return stMsg.wParam;
	}
};

