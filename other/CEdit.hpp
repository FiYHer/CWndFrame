#pragma once
//https://docs.microsoft.com/zh-cn/windows/desktop/Controls/edit-controls
#include <Windows.h>
#include <Windowsx.h>//控件宏相关

#include <string>
using namespace std;

/*
风格:
ES_AUTOHSCROLL 水平滚动
ES_AUTOVSCROLL 垂直滚动
ES_PASSWORD 密码框
ES_READONLY 只读
ES_CENTER 居中显示
ES_LEFT 向左显示.
ES_MUTILINE 多行风格
WS_EX_CLIENTEDGE 该扩展风格可以使之有立体感 凹陷

消息:
WM_GETTEXTLENGTH 返回文本的长度
WM_GETTEXT 返回文本数据 WPARAM-缓冲区大小 LPARAM-缓冲区长度
WM_SETTEXT 设置文本数据 LPARAM-缓冲区地址

通知:
EN_CHANGE 编辑框数据被修改时通知
EN_SETFOCUS 编辑控件获得输入焦点
EN_KILLFOCUS 编辑控件失去输入焦点
EN_CHANGE 编辑控件的内容将改变
EN_UPDATE 编辑控件的内容已变化
EN_ERRSPACE 编辑控件没有空间了
EN_MAXTEXT 编辑控件没有控件完成插入了
EN_HSCROLL 编辑控件水平滚动条被单击了
EN_VSCROLL 编辑控件垂直滚动条被单击了

WM_CUT WM_COPY WM_CLEAR 剪切 复制 删除当前内容 WPARAM LPARAM没用
WM_PASTE 将剪切板上的内容插入到当前位置 W/L没有用
EM_GETSEL 获取当前文本的起始位置和结束位置 WPARAM返回起始位置地址 LPARAM返回结束位置地址
*/


class CEdit
{
private:
	//主窗口的句柄
	HWND m_hWnd;
	//程序的实例
	HINSTANCE m_hInstance;
	//编辑框的句柄
	HWND m_hEdit;
	//字体
	HFONT m_hFont;

public:
	CEdit(HWND hWnd,HINSTANCE hInstance,int nFontSize = 15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hFont = CreateFont(nFontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"宋体");
	}
	~CEdit()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
	}

public:
	//修改风格
	inline void SetStyle(long lValue)const
	{
		if(m_hEdit)
			SetWindowLongA(m_hEdit, GWL_STYLE, lValue);
	}

	//启用或者禁用
	inline void SetEnable(bool bUse)const
	{
		if (m_hEdit)
			Edit_Enable(m_hEdit, bUse);
	}

	//获取编辑框的行数
	inline int GetLineNumber()const
	{
		int nCount = 0;
		if (m_hEdit)
			nCount = SendMessageA(m_hEdit, EM_GETLINECOUNT, 0, 0);
		return nCount;
	}

	//设置编辑框控件的ID
	inline void SetID(long lValue)const
	{
		if (m_hEdit)
			SetWindowLongA(m_hEdit, GWL_ID, lValue);
	}

	//设置位置
	inline void SetLocation(int nValueX,int nValueY)const
	{
		if (m_hEdit)
		{
			RECT stRect;
			GetWindowRect(m_hEdit, &stRect);
			MoveWindow(m_hEdit, nValueX, nValueY,
				stRect.right - stRect.left, stRect.bottom - stRect.top, TRUE);
		}
	}

	//设置大小
	inline void SetSize(int nValueX,int nValueY)const
	{
		if (m_hEdit)
		{
			RECT stEditRect;
			RECT stWindowRect;
			GetWindowRect(m_hWnd, &stWindowRect);
			GetWindowRect(m_hEdit, &stEditRect);
			MoveWindow(m_hEdit, stEditRect.left - stWindowRect.left,
				stEditRect.top - stWindowRect.top, nValueX, nValueY, TRUE);
		}
	}

	//限制最大字符数量
	inline void SetLimit(int nLen)const
	{
		if (m_hEdit)
			Edit_LimitText(m_hEdit, nLen);
	}

	//设置内容
	inline void SetData(const string& strData)const
	{
		SetWindowTextA(m_hEdit, strData.c_str());
	}

	//获取内容
	inline void GetData(char* szData,int nSize)const
	{
		//Edit_GetText(m_hEdit, szData, nSize);
		GetWindowTextA(m_hEdit, szData, nSize);
	}

public:
	//创建编辑框控件
	HWND Create(
		DWORD dwStyle = WS_CHILD |WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL |ES_LEFT |ES_MULTILINE)
	{
		if (m_hEdit)
			return 0;
		m_hEdit = CreateWindowExA(0, "Edit", 0, dwStyle, 100, 100, 100, 100,
			m_hWnd, 0, m_hInstance, 0);
		if (m_hFont)
			PostMessageA(m_hEdit, WM_SETFONT, (WPARAM)m_hFont, 0);
		return m_hWnd;
	}

	//删除编辑框控件
	void Delete()
	{
		if (m_hEdit)
			DestroyWindow(m_hEdit);
		m_hEdit = 0;
	}

};
