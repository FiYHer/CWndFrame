#pragma once

#include <Windows.h>
#include <Windowsx.h>//控件宏相关

#include <string>
using namespace std;

/*
样式:
CBS_SIMPLE 简单的
CBS_DROPDOWN 可编辑可下拉    
CBS_DROPDOWNLIST 可下拉不可编辑
CBS_AUTOHSCROLL 自动滚动条
CBS_SORT自动排序 

消息:
CB_GETEDITSEL 获取组合框的编辑控件中当前选择的开始和结束字符位置
CB_LIMITTEXT 限制用户可以在组合框的编辑控件中键入的文本的长度 wparam
CB_DIR 显示目录 wparam：类型 lparam：目录
CB_FINDSTRING 查找字符串 wparam：起始位置 lparam：字符串


*/

class CComboBox
{
private:
	//主窗口的句柄
	HWND m_hWnd;
	//程序的实例
	HINSTANCE m_hInstance;
	//组合框的控件
	HWND m_hComboBox;
	//组合框的字体
	HFONT m_hFont;

public:
	CComboBox(HWND hWnd,HINSTANCE hInstance,int nFrontSize = 15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hComboBox = 0;
		m_hFont = CreateFont(nFrontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"宋体");
	}
	~CComboBox()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
	}

public:
	//添加数据 CB_ADDSTRING
	inline void AddData(const string& strData)const
	{
		if (m_hComboBox)
			ComboBox_AddItemData(m_hComboBox, strData.c_str());
	}

	//添加字符串 CB_ADDSTRING
	inline void AddString(const string& str)const
	{
		if (m_hComboBox)
			ComboBox_AddString(m_hComboBox, str.c_str());
	}

	//删除指定位置的字符串 CB_DELETESTRING
	inline void DeleteString(int nIndex)const
	{
		if (m_hComboBox)
			ComboBox_DeleteString(m_hComboBox, nIndex);
	}

	//启用或者禁用
	inline void Enable(bool bUse)const
	{
		if (m_hComboBox)
			ComboBox_Enable(m_hComboBox, bUse);
	}

	//设置最大长度
	inline void SetLimit(int nLen)const
	{
		if (m_hComboBox)
			ComboBox_LimitText(m_hComboBox, nLen);
	}

	//插入数据
	inline void InserString(int nIndex,const string& strData)const
	{
		if (m_hComboBox)
			SendMessageA(m_hComboBox, CB_INSERTSTRING, nIndex, (LPARAM)strData.c_str());
	}
	 
	//删除所有数据 CB_RESETCONTENT
	inline void DeleteAllString()const
	{
		if (m_hComboBox)
			ComboBox_ResetContent(m_hComboBox);
	}

	//获取当前的数据量 
	inline UINT GetNumber()const
	{
		if (m_hComboBox)
			PostMessageA(m_hComboBox, CB_GETCOUNT, 0, 0);
	}

	//获取指定索引的数据
	inline void GetString(int nIndex,char* szData)const
	{
		if (m_hComboBox)
			SendMessageA(m_hComboBox, CB_GETLBTEXT, nIndex, (LPARAM)szData);
	}

	//设置当前的选项
	inline void SetDefault(int nIndex)const
	{
		if (m_hComboBox)
			PostMessageA(m_hComboBox, CB_SETCURSEL, nIndex, 0);
	}

	//获取当前的选项
	inline UINT GetDefault()const
	{
		UINT nIndex;
		if (m_hComboBox)
			nIndex = SendMessageA(m_hComboBox, CB_GETCURSEL, 0, 0);
		return nIndex;
	}

	//设置大小
	inline void SetSize(int nValueX,int nValueY)const
	{
		if (m_hComboBox)
		{
			RECT stComboBoxRect;
			GetWindowRect(m_hComboBox, &stComboBoxRect);
			RECT stWindowRect;
			GetWindowRect(m_hWnd, &stWindowRect);
			MoveWindow(m_hComboBox, stComboBoxRect.left - stWindowRect.left,
				stComboBoxRect.top - stWindowRect.top, nValueX, nValueY, TRUE);
		}
	}

	//设置位置
	inline void SetLocation(int nValueX,int nValueY)const
	{
		if (m_hComboBox)
		{
			RECT stRect;
			GetWindowRect(m_hComboBox, &stRect);
			MoveWindow(m_hComboBox, nValueX, nValueY, 
				stRect.right-stRect.left,stRect.bottom-stRect.top,TRUE);
		}
	}

public:
	//创建一个组合框    CBS_DROPDOWN       CBS_DROPDOWNLIST    
	HWND Create(DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWN)
	{
		if (m_hComboBox)
			return 0;
		m_hComboBox = CreateWindowExA(0, "ComboBox", 0, dwStyle, 100, 100, 100, 100,
			m_hWnd, 0, m_hInstance, 0);
		if (m_hFont)
			PostMessageA(m_hComboBox, WM_SETFONT, (WPARAM)m_hFont, 0);
		return m_hComboBox;
	}

	//删除一个组合框
	void Delete()
	{
		if (m_hComboBox)
			DestroyWindow(m_hComboBox);
		m_hComboBox = 0;
	}
};