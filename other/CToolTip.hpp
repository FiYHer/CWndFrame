#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>

/*
标准工具提示文本的最大长度为80个字符
*/

class CToolTip
{
private:
	//主窗口句柄
	HWND m_hWnd;
	//程序的实例
	HINSTANCE m_hInstance;
	//提示控件的句柄
	HWND m_hToolTip;

public:
	CToolTip(HWND hWnd,HINSTANCE hInstance):m_hWnd(hWnd),m_hInstance(hInstance)
	{

	}
	~CToolTip()
	{
		Delete();
	}

public:
	//指定目标控件
	inline void SetTargetControl(HWND hWnd,const LPSTR pStr)const
	{
		if (m_hToolTip)
		{
			//https://docs.microsoft.com/en-us/windows/desktop/api/Commctrl/ns-commctrl-tagtoolinfoa
			TOOLINFOA stTool;
			memset(&stTool, 0, sizeof(TOOLINFOA));
			stTool.cbSize = sizeof(TOOLINFOA);
			stTool.hwnd = m_hWnd;
			stTool.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
			stTool.uId = (UINT_PTR)hWnd;
			stTool.lpszText = pStr;
			SendMessageA(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&stTool);
		}
	}

	//设置目标区域
	inline void SetTargetRect(RECT stRect,const LPSTR pStr)const
	{
		if (m_hToolTip)
		{
			TOOLINFOA stTool;
			memset(&stTool,0,sizeof(TOOLINFOA));
			stTool.uFlags = TTF_SUBCLASS;
			stTool.hwnd = m_hWnd;
			stTool.hinst = m_hInstance;
			stTool.lpszText = pStr;
			stTool.rect = stRect;
			SendMessageA(m_hToolTip, TTM_ADDTOOL, 0, (LPARAM)&stTool);
		}
	}

	//激活或者取消激活
	inline void Active(bool bUse)const
	{
		if (m_hToolTip)
			PostMessageA(m_hToolTip, TTM_ACTIVATE, bUse, 0);
	}

	//激活或者取消激活跟踪
	inline void TrackActive(bool bUse)const
	{
		if (m_hToolTip)
			PostMessageA(m_hToolTip, TTM_TRACKACTIVATE, bUse, 0);
	}

	//强制重绘
	inline void Update()const
	{
		if (m_hToolTip)
			PostMessageA(m_hToolTip, TTM_UPDATE, 0, 0);
	}

	//设置提示文本颜色
	inline void SetTextColor(COLORREF stRGB)const
	{
		if (m_hToolTip)
			SendMessageA(m_hToolTip, TTM_SETTIPTEXTCOLOR, stRGB, 0);
	}

public:
	//创建
	HWND Create(DWORD dwType = WS_VISIBLE |WS_CHILD | WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON)
	{
		if (m_hToolTip)
			return 0;

		m_hToolTip = CreateWindowExA(0, TOOLTIPS_CLASS, 0, dwType, 100, 100,
			100, 100, m_hWnd, 0, m_hInstance, 0);

		return m_hToolTip;
	}

	//删除
	void Delete()
	{
		if (m_hToolTip)
			DestroyWindow(m_hToolTip);
		m_hToolTip = 0;
	}
};
