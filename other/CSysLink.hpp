#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>

class CSysLink
{
private:
	//主窗口的句柄
	HWND m_hWnd;
	//程序的实例
	HINSTANCE m_hInstance;
	//超链接控件句柄
	HWND m_hSysLink;
	//字体句柄
	HFONT m_hFont;

public:
	CSysLink(HWND hWnd,HINSTANCE hInstance,int nFrontSize = 15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hSysLink = 0;
		m_hFont = CreateFont(nFrontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"宋体");
	}
	~CSysLink()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
	}

public:
	//设置大小
	inline void SetSize(int nValueX, int nValueY)const
	{
		if (m_hSysLink)
		{
			RECT stSysLinkRect;
			RECT stWindowRect;
			GetWindowRect(m_hWnd, &stWindowRect);
			GetWindowRect(m_hSysLink, &stSysLinkRect);
			MoveWindow(m_hSysLink, stSysLinkRect.left - stWindowRect.left,
				stSysLinkRect.top - stWindowRect.top, nValueX, nValueY, true);
		}
	}

	//设置位置
	inline void SetLocation(int nValueX,int nValueY)const
	{
		if (m_hSysLink)
		{
			RECT stRect;
			GetWindowRect(m_hSysLink, &stRect);
			MoveWindow(m_hSysLink, nValueX, nValueY, stRect.right - stRect.left,
				stRect.bottom - stRect.top, true);
		}
	}

	//设置状态和属性
	inline void SetItem(const WCHAR* wcStr)const
	{
		if (m_hSysLink)
		{
			LITEM stItem;
			memset(&stItem, 0, sizeof(LITEM));
			stItem.mask = LIF_URL;
			stItem.state = LIS_ENABLED | LIS_FOCUSED | LIS_HOTTRACK;
			wcsncpy_s(stItem.szUrl, wcStr, L_MAX_URL_LENGTH);
			SendMessageA(m_hSysLink, LM_SETITEM, 0, (LPARAM)&stItem);
		}
	}

public:
	//创建
	HWND Create(DWORD dwStyle = WS_VISIBLE |WS_CHILD | WS_TABSTOP)
	{
		if (m_hSysLink)
			return 0;

		m_hSysLink = CreateWindowExA(0, "SysLink", "Text", dwStyle, 100, 100,
			100, 100, m_hWnd, 0, m_hInstance, 0);

		if (m_hSysLink && m_hFont)
			PostMessageA(m_hSysLink, WM_SETFONT, (WPARAM)m_hFont, 0);

		return m_hSysLink;
	}

	//销毁
	void Delete()
	{
		if (m_hSysLink)
			DestroyWindow(m_hSysLink);
		m_hSysLink = 0;
	}

};