#pragma once

#include <Windows.h>

#include <string>
using namespace std;

class CListBox
{
private:
	//�����ھ��
	HWND m_hWnd;
	//�����ʵ��
	HINSTANCE m_hInstance;
	//�б�ľ��
	HWND m_hListBox;
	//�б��ID
	int m_nlistBoxID;
	//������
	HFONT m_hFont;

public:
	CListBox(HWND hWnd,HINSTANCE hInstance,int nFontSize = 15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_nlistBoxID = rand() % 1000;
		m_hListBox = 0;
		m_hFont = CreateFont(nFontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"����");
	}
	~CListBox()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
	}

public:
	//�޸��б��ID
	inline void SetID(long lValue)
	{
		m_nlistBoxID = lValue;
		if (m_hListBox)
			SetWindowLongA(m_hListBox, GWL_ID, lValue);
	}

	//�޸�����
	inline void SetStyle(long lValue)const
	{
		if (m_hListBox)
			SetWindowLongA(m_hListBox, GWL_STYLE, lValue);
	}

	//���ô�С
	inline void SetSize(int nValueX, int nValueY)const
	{
		if (m_hListBox)
		{
			RECT stListBoxRect;
			RECT stWindowRect;
			GetWindowRect(m_hListBox, &stListBoxRect);
			GetWindowRect(m_hWnd, &stWindowRect);
			MoveWindow(m_hListBox, stListBoxRect.left - stWindowRect.left,
				stListBoxRect.top - stWindowRect.top, nValueX, nValueY, TRUE);
		}
	}

	//����λ��
	inline void SetLocation(int nValueX,int nValueY)const
	{
		if (m_hListBox)
		{
			RECT stRect;
			GetWindowRect(m_hListBox, &stRect);
			MoveWindow(m_hListBox, nValueX, nValueY, stRect.right - stRect.left,
				stRect.bottom - stRect.top, TRUE);
		}
	}

	//�������
	inline void AddString(const string& strData)const
	{
		if (m_hListBox)
			SendMessageA(m_hListBox, LB_ADDSTRING,0,(LPARAM)strData.c_str());
	}


public:
	//����
	HWND Create(DWORD dwStyle = WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER)
	{
		if (m_hListBox)
			return 0;
		m_hListBox = CreateWindowExA(0, "ListBox", 0, dwStyle, 100, 100, 100, 100,
			m_hWnd, 0, m_hInstance, 0);
		if (m_hFont)
			PostMessageA(m_hListBox, WM_SETFONT, (WPARAM)m_hFont, 0);
		return m_hListBox;
	}

	//ɾ��
	void Delete()
	{
		if (m_hListBox)
			DestroyWindow(m_hListBox);
		m_hListBox = 0;
	}
};