#pragma once
//https://docs.microsoft.com/zh-cn/windows/desktop/Controls/edit-controls
#include <Windows.h>
#include <Windowsx.h>//�ؼ������

#include <string>
using namespace std;

/*
���:
ES_AUTOHSCROLL ˮƽ����
ES_AUTOVSCROLL ��ֱ����
ES_PASSWORD �����
ES_READONLY ֻ��
ES_CENTER ������ʾ
ES_LEFT ������ʾ.
ES_MUTILINE ���з��
WS_EX_CLIENTEDGE ����չ������ʹ֮������� ����

��Ϣ:
WM_GETTEXTLENGTH �����ı��ĳ���
WM_GETTEXT �����ı����� WPARAM-��������С LPARAM-����������
WM_SETTEXT �����ı����� LPARAM-��������ַ

֪ͨ:
EN_CHANGE �༭�����ݱ��޸�ʱ֪ͨ
EN_SETFOCUS �༭�ؼ�������뽹��
EN_KILLFOCUS �༭�ؼ�ʧȥ���뽹��
EN_CHANGE �༭�ؼ������ݽ��ı�
EN_UPDATE �༭�ؼ��������ѱ仯
EN_ERRSPACE �༭�ؼ�û�пռ���
EN_MAXTEXT �༭�ؼ�û�пؼ���ɲ�����
EN_HSCROLL �༭�ؼ�ˮƽ��������������
EN_VSCROLL �༭�ؼ���ֱ��������������

WM_CUT WM_COPY WM_CLEAR ���� ���� ɾ����ǰ���� WPARAM LPARAMû��
WM_PASTE �����а��ϵ����ݲ��뵽��ǰλ�� W/Lû����
EM_GETSEL ��ȡ��ǰ�ı�����ʼλ�úͽ���λ�� WPARAM������ʼλ�õ�ַ LPARAM���ؽ���λ�õ�ַ
*/


class CEdit
{
private:
	//�����ڵľ��
	HWND m_hWnd;
	//�����ʵ��
	HINSTANCE m_hInstance;
	//�༭��ľ��
	HWND m_hEdit;
	//����
	HFONT m_hFont;

public:
	CEdit(HWND hWnd,HINSTANCE hInstance,int nFontSize = 15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hFont = CreateFont(nFontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"����");
	}
	~CEdit()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
	}

public:
	//�޸ķ��
	inline void SetStyle(long lValue)const
	{
		if(m_hEdit)
			SetWindowLongA(m_hEdit, GWL_STYLE, lValue);
	}

	//���û��߽���
	inline void SetEnable(bool bUse)const
	{
		if (m_hEdit)
			Edit_Enable(m_hEdit, bUse);
	}

	//��ȡ�༭�������
	inline int GetLineNumber()const
	{
		int nCount = 0;
		if (m_hEdit)
			nCount = SendMessageA(m_hEdit, EM_GETLINECOUNT, 0, 0);
		return nCount;
	}

	//���ñ༭��ؼ���ID
	inline void SetID(long lValue)const
	{
		if (m_hEdit)
			SetWindowLongA(m_hEdit, GWL_ID, lValue);
	}

	//����λ��
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

	//���ô�С
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

	//��������ַ�����
	inline void SetLimit(int nLen)const
	{
		if (m_hEdit)
			Edit_LimitText(m_hEdit, nLen);
	}

	//��������
	inline void SetData(const string& strData)const
	{
		SetWindowTextA(m_hEdit, strData.c_str());
	}

	//��ȡ����
	inline void GetData(char* szData,int nSize)const
	{
		//Edit_GetText(m_hEdit, szData, nSize);
		GetWindowTextA(m_hEdit, szData, nSize);
	}

public:
	//�����༭��ؼ�
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

	//ɾ���༭��ؼ�
	void Delete()
	{
		if (m_hEdit)
			DestroyWindow(m_hEdit);
		m_hEdit = 0;
	}

};
