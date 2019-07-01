#pragma once

#include <Windows.h>
#include <Windowsx.h>//控件宏相关

#include <string>
using namespace std;

//按钮基本类型
#define BASESTYLE WS_CHILD | WS_VISIBLE
//下压式按钮
#define BUTTONDOWN BASESTYLE | BS_PUSHBUTTON | BS_BITMAP
//单选框按钮
#define BUTTONRADIO BASESTYLE | BS_AUTORADIOBUTTON
//复选框按钮
#define BUTTONCHECK BASESTYLE | BS_AUTO3STATE
//分组框按钮
#define BUTTONGRUOP BASESTYLE | BS_GROUPBOX

/*
样式:
BS_PUSHBUTTON BS_DEFPUSHBUTTON 正常的按钮
BS_CHECKBOX BS_AUTOCHECKBOX 复选框
BS_OWNERDRAW 自绘类型按钮
BS_TEXT 用来显示的文字按钮
BS_ICON 用来显示Icon的按钮
BS_BITMAP 用来显示位图的按钮
BS_LEFT 左对齐
BS_RIGHT 右对齐
BS_CENTER 中心对齐
BS_NOTIFY 接受通知

通知：
BN_CLICKED 单击按钮
BN_PAINT 自绘按钮
BN_SETFOCUS 获取焦点
BN_KILLFOCUS 失去焦点

消息
BM_GETCHECK 获取当前的状态
BM_SETCHECK 设置当前的状态
BM_GETSTATE
BM_SETSTATE
BM_SETSTYLE 设置Style


*/

class CButton
{
private:
	HWND m_hWnd;			//主窗口的句柄
	HWND m_hButton;			//按钮的句柄
	HINSTANCE m_hInstance;	//程序的实例
	string m_strCaption;	//按钮的标题
	int m_nButtonID;		//按钮的ID
	HBITMAP m_hBitmap;		//按钮的位图
	HFONT m_hFont;			//按钮的字体

public:
	CButton(HWND hWnd, HINSTANCE hInstance,int nFrontSize = 15) :m_hWnd(hWnd), m_hInstance(hInstance) 
	{
		m_hButton = 0;
		m_hBitmap = 0;
		m_nButtonID = rand() % 10000;
		m_hFont = CreateFont(nFrontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"宋体");
	}
	~CButton() 
	{
		Delete();
		if (m_hBitmap)
			DeleteObject(m_hBitmap);
		if (m_hFont)
			DeleteObject(m_hFont);
	};

public:
	//显示按钮
	inline void Show()const
	{
		if (m_hButton)
			ShowWindow(m_hButton, SW_SHOW);
	}

	//隐藏按钮
	inline void Hide()const
	{
		if (m_hButton)
			ShowWindow(m_hButton, SW_HIDE);
	}

	//设置按钮的风格
	inline void SetStyle(long lValue)const
	{
		if (m_hButton)
			Button_SetStyle(m_hButton, lValue, true);
			//SetWindowLongA(m_hButton, GWL_STYLE, lValue);
	}

	//设置窗口的ID
	inline void SetID(long lValue)
	{
		m_nButtonID = lValue;
		if(m_hButton)
			SetWindowLongA(m_hButton, GWL_ID, lValue);
	}

	//设置按钮标题
	inline void SetCaption(const string& strCaption)
	{
		m_strCaption = strCaption;
		if (m_hButton)
			SetWindowTextA(m_hButton, m_strCaption.c_str());
	}

	//获取按钮标题
	inline string GetCaption()const
	{
		return m_strCaption;
	}

	//设置按钮的大小
	inline void SetSize(int nValueX,int nValueY)const
	{
		if (m_hButton)
		{
			RECT stRect;
			GetWindowRect(m_hButton, &stRect);
			MoveWindow(m_hButton, stRect.left, stRect.top, nValueX, nValueY, TRUE);
		}
	}

	//设置按钮的位置
	inline void SetLocation(int nValueX,int nValueY)const
	{
		if (m_hButton)
		{
			RECT stRect;
			GetWindowRect(m_hButton, &stRect);
			MoveWindow(m_hButton, nValueX, nValueY,
				stRect.right - stRect.left, stRect.bottom - stRect.top, TRUE);
		}
	}

	//设置一张位图给按钮
	inline void SetPicture(const string& strPath)
	{
		if (m_hBitmap)
			DeleteObject(m_hBitmap);
		m_hBitmap = (HBITMAP)LoadImageA(0, strPath.c_str(), IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE);
		if (m_hBitmap && m_hButton)
			PostMessageA(m_hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
	}

	//获取按钮的状态 BST_CHECKED 
	inline LRESULT  GetState()
	{
		LRESULT lRet = 0;
		if (m_hButton)
			lRet = SendMessageA(m_hButton, BM_GETCHECK, 0, 0);
		return lRet;
	}

	//设置按钮的状态
	//BST_INDETERMINATE - 设置灰色
	//BST_CHECKED-- - 设置选择
	//BST_UNCHECKED  --设置不选择
	inline void SetState(LRESULT lValue)
	{
		if (m_hButton)
			PostMessageA(m_hButton, BM_SETCHECK, lValue, 0);
	}

	//启用或者禁用
	inline void Enable(bool bUse)const
	{
		if (m_hButton)
			Button_Enable(m_hButton, bUse);
	}

public:
	//创建按钮
	HWND Create(DWORD dwStyle = BUTTONDOWN)
	{
		if (m_hButton)
			return 0;
		m_hButton = CreateWindowExA(0, "Button", m_strCaption.c_str(),
			dwStyle, 100, 100, 100, 100, m_hWnd, (HMENU)m_nButtonID, m_hInstance, 0);
		if (m_hFont)
			PostMessageA(m_hButton, WM_SETFONT, (WPARAM)m_hFont, 0);
		return m_hButton;
	}

	//删除一个按钮
	void Delete()
	{
		if(m_hButton)
			DestroyWindow(m_hButton);
		m_hButton = 0;
	}

};

