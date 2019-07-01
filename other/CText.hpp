#pragma once

#include <Windows.h>

#include <string>
using namespace std;

// ���ھ�̬���֪ͨ��,��֪ͨ�����ͨ��WM_COMMAND��Ϣ,��wParam�ĸ��ֽ�����ȡ.STN_CLICKED

/*
	//���þ�̬��ؼ��ı���Ϊ͸��
	if (uMsg == WM_CTLCOLORSTATIC)
	{
		//����HDC�Ļ���ģʽ
		SetBkMode((HDC)wParam, TRANSPARENT);
		//SetTextColor(...);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	}
*/

class CText
{
private:
	//�����ڵľ��'
	HWND m_hWnd;
	//�����ʵ��
	HINSTANCE m_hInstance;
	//�ı��ؼ����
	HWND m_hText;
	//����
	HFONT m_hFont;
	//λͼ���
	HBITMAP m_hBitmap;

public:
	CText(HWND hWnd,HINSTANCE hInstance,int nFontSize =15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hBitmap = 0;
		m_hText = 0;
		m_hFont = CreateFont(nFontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"����");
	}
	~CText()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
		if (m_hBitmap)
			DeleteObject(m_hBitmap);
	}

public:
	//����λ��
	inline void SetLocation(int nValueX,int nValueY)const
	{
		if (m_hText)
		{
			RECT stTextRect;
			GetWindowRect(m_hText, &stTextRect);
			MoveWindow(m_hText, nValueX, nValueY,
				stTextRect.right - stTextRect.left, stTextRect.bottom - stTextRect.top, TRUE);
		}
	}

	//���ô�С
	inline void SetSize(int nValueX,int nValueY)const
	{
		if (m_hText)
		{
			RECT stTextRect;
			RECT stWindowRect;
			GetWindowRect(m_hText, &stTextRect);
			GetWindowRect(m_hWnd, &stWindowRect);
			MoveWindow(m_hText, stTextRect.left - stWindowRect.left,
				stTextRect.top - stWindowRect.top, nValueX, nValueY, TRUE);
		}
	}

	//�����ı��ؼ���ID
	inline void SetID(long lValue)const
	{
		if (m_hText)
			SetWindowLongA(m_hText, GWL_ID, lValue);
	}

	//�����ı��ؼ�������
	inline void SetText(const string& strData)const
	{
		if (m_hText)
			SetWindowTextA(m_hText, strData.c_str());
	}

	//��ȡ�ı��ؼ�������
	inline void GetData(char* szData,int nSize)const
	{
		if(m_hText)
			GetWindowTextA(m_hText, szData, nSize);
	}

	//������ʾ��ͼƬ
	void SetBitmap(const string& str)
	{
		if (m_hText)
		{
			m_hBitmap = (HBITMAP)LoadImageA(0, str.c_str(), IMAGE_BITMAP, 0, 0,
				LR_LOADFROMFILE | LR_DEFAULTCOLOR);
			if (!m_hBitmap)
				return;
			SetWindowLongA(m_hText, GWL_STYLE, WS_VISIBLE | WS_CHILD | SS_BITMAP | SS_NOTIFY);
			PostMessageA(m_hText, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
		}
	}

public:
	//�����ı��ؼ�
	HWND Create(DWORD dwStyle = WS_CHILD |WS_VISIBLE | SS_CENTER | SS_NOTIFY)
	{
		if (m_hText)
			return 0;
		m_hText = CreateWindowExA(0, "Static", "This is text control", dwStyle, 
			100, 100, 100, 100,m_hWnd, (HMENU)0, m_hInstance, 0);
		if (m_hFont)
			SendMessageA(m_hText, WM_SETFONT, (WPARAM)m_hFont, 0);
		return m_hText;
	}

	//ɾ���ı��ؼ�
	void Delete()
	{
		if (m_hText)
			DestroyWindow(m_hText);
		m_hText = 0;
	}
};
