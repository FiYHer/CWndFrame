#pragma once

#include <Windows.h>
#include <Windowsx.h>//�ؼ������

#include <string>
using namespace std;

//��ť��������
#define BASESTYLE WS_CHILD | WS_VISIBLE
//��ѹʽ��ť
#define BUTTONDOWN BASESTYLE | BS_PUSHBUTTON | BS_BITMAP
//��ѡ��ť
#define BUTTONRADIO BASESTYLE | BS_AUTORADIOBUTTON
//��ѡ��ť
#define BUTTONCHECK BASESTYLE | BS_AUTO3STATE
//�����ť
#define BUTTONGRUOP BASESTYLE | BS_GROUPBOX

/*
��ʽ:
BS_PUSHBUTTON BS_DEFPUSHBUTTON �����İ�ť
BS_CHECKBOX BS_AUTOCHECKBOX ��ѡ��
BS_OWNERDRAW �Ի����Ͱ�ť
BS_TEXT ������ʾ�����ְ�ť
BS_ICON ������ʾIcon�İ�ť
BS_BITMAP ������ʾλͼ�İ�ť
BS_LEFT �����
BS_RIGHT �Ҷ���
BS_CENTER ���Ķ���
BS_NOTIFY ����֪ͨ

֪ͨ��
BN_CLICKED ������ť
BN_PAINT �Ի水ť
BN_SETFOCUS ��ȡ����
BN_KILLFOCUS ʧȥ����

��Ϣ
BM_GETCHECK ��ȡ��ǰ��״̬
BM_SETCHECK ���õ�ǰ��״̬
BM_GETSTATE
BM_SETSTATE
BM_SETSTYLE ����Style


*/

class CButton
{
private:
	HWND m_hWnd;			//�����ڵľ��
	HWND m_hButton;			//��ť�ľ��
	HINSTANCE m_hInstance;	//�����ʵ��
	string m_strCaption;	//��ť�ı���
	int m_nButtonID;		//��ť��ID
	HBITMAP m_hBitmap;		//��ť��λͼ
	HFONT m_hFont;			//��ť������

public:
	CButton(HWND hWnd, HINSTANCE hInstance,int nFrontSize = 15) :m_hWnd(hWnd), m_hInstance(hInstance) 
	{
		m_hButton = 0;
		m_hBitmap = 0;
		m_nButtonID = rand() % 10000;
		m_hFont = CreateFont(nFrontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"����");
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
	//��ʾ��ť
	inline void Show()const
	{
		if (m_hButton)
			ShowWindow(m_hButton, SW_SHOW);
	}

	//���ذ�ť
	inline void Hide()const
	{
		if (m_hButton)
			ShowWindow(m_hButton, SW_HIDE);
	}

	//���ð�ť�ķ��
	inline void SetStyle(long lValue)const
	{
		if (m_hButton)
			Button_SetStyle(m_hButton, lValue, true);
			//SetWindowLongA(m_hButton, GWL_STYLE, lValue);
	}

	//���ô��ڵ�ID
	inline void SetID(long lValue)
	{
		m_nButtonID = lValue;
		if(m_hButton)
			SetWindowLongA(m_hButton, GWL_ID, lValue);
	}

	//���ð�ť����
	inline void SetCaption(const string& strCaption)
	{
		m_strCaption = strCaption;
		if (m_hButton)
			SetWindowTextA(m_hButton, m_strCaption.c_str());
	}

	//��ȡ��ť����
	inline string GetCaption()const
	{
		return m_strCaption;
	}

	//���ð�ť�Ĵ�С
	inline void SetSize(int nValueX,int nValueY)const
	{
		if (m_hButton)
		{
			RECT stRect;
			GetWindowRect(m_hButton, &stRect);
			MoveWindow(m_hButton, stRect.left, stRect.top, nValueX, nValueY, TRUE);
		}
	}

	//���ð�ť��λ��
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

	//����һ��λͼ����ť
	inline void SetPicture(const string& strPath)
	{
		if (m_hBitmap)
			DeleteObject(m_hBitmap);
		m_hBitmap = (HBITMAP)LoadImageA(0, strPath.c_str(), IMAGE_BITMAP, 0, 0,
			LR_LOADFROMFILE | LR_DEFAULTSIZE);
		if (m_hBitmap && m_hButton)
			PostMessageA(m_hButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hBitmap);
	}

	//��ȡ��ť��״̬ BST_CHECKED 
	inline LRESULT  GetState()
	{
		LRESULT lRet = 0;
		if (m_hButton)
			lRet = SendMessageA(m_hButton, BM_GETCHECK, 0, 0);
		return lRet;
	}

	//���ð�ť��״̬
	//BST_INDETERMINATE - ���û�ɫ
	//BST_CHECKED-- - ����ѡ��
	//BST_UNCHECKED  --���ò�ѡ��
	inline void SetState(LRESULT lValue)
	{
		if (m_hButton)
			PostMessageA(m_hButton, BM_SETCHECK, lValue, 0);
	}

	//���û��߽���
	inline void Enable(bool bUse)const
	{
		if (m_hButton)
			Button_Enable(m_hButton, bUse);
	}

public:
	//������ť
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

	//ɾ��һ����ť
	void Delete()
	{
		if(m_hButton)
			DestroyWindow(m_hButton);
		m_hButton = 0;
	}

};

