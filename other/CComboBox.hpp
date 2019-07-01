#pragma once

#include <Windows.h>
#include <Windowsx.h>//�ؼ������

#include <string>
using namespace std;

/*
��ʽ:
CBS_SIMPLE �򵥵�
CBS_DROPDOWN �ɱ༭������    
CBS_DROPDOWNLIST ���������ɱ༭
CBS_AUTOHSCROLL �Զ�������
CBS_SORT�Զ����� 

��Ϣ:
CB_GETEDITSEL ��ȡ��Ͽ�ı༭�ؼ��е�ǰѡ��Ŀ�ʼ�ͽ����ַ�λ��
CB_LIMITTEXT �����û���������Ͽ�ı༭�ؼ��м�����ı��ĳ��� wparam
CB_DIR ��ʾĿ¼ wparam������ lparam��Ŀ¼
CB_FINDSTRING �����ַ��� wparam����ʼλ�� lparam���ַ���


*/

class CComboBox
{
private:
	//�����ڵľ��
	HWND m_hWnd;
	//�����ʵ��
	HINSTANCE m_hInstance;
	//��Ͽ�Ŀؼ�
	HWND m_hComboBox;
	//��Ͽ������
	HFONT m_hFont;

public:
	CComboBox(HWND hWnd,HINSTANCE hInstance,int nFrontSize = 15):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hComboBox = 0;
		m_hFont = CreateFont(nFrontSize, 0, 0, 0, FW_HEAVY,
			0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, (TCHAR*)"����");
	}
	~CComboBox()
	{
		Delete();
		if (m_hFont)
			DeleteObject(m_hFont);
	}

public:
	//������� CB_ADDSTRING
	inline void AddData(const string& strData)const
	{
		if (m_hComboBox)
			ComboBox_AddItemData(m_hComboBox, strData.c_str());
	}

	//����ַ��� CB_ADDSTRING
	inline void AddString(const string& str)const
	{
		if (m_hComboBox)
			ComboBox_AddString(m_hComboBox, str.c_str());
	}

	//ɾ��ָ��λ�õ��ַ��� CB_DELETESTRING
	inline void DeleteString(int nIndex)const
	{
		if (m_hComboBox)
			ComboBox_DeleteString(m_hComboBox, nIndex);
	}

	//���û��߽���
	inline void Enable(bool bUse)const
	{
		if (m_hComboBox)
			ComboBox_Enable(m_hComboBox, bUse);
	}

	//������󳤶�
	inline void SetLimit(int nLen)const
	{
		if (m_hComboBox)
			ComboBox_LimitText(m_hComboBox, nLen);
	}

	//��������
	inline void InserString(int nIndex,const string& strData)const
	{
		if (m_hComboBox)
			SendMessageA(m_hComboBox, CB_INSERTSTRING, nIndex, (LPARAM)strData.c_str());
	}
	 
	//ɾ���������� CB_RESETCONTENT
	inline void DeleteAllString()const
	{
		if (m_hComboBox)
			ComboBox_ResetContent(m_hComboBox);
	}

	//��ȡ��ǰ�������� 
	inline UINT GetNumber()const
	{
		if (m_hComboBox)
			PostMessageA(m_hComboBox, CB_GETCOUNT, 0, 0);
	}

	//��ȡָ������������
	inline void GetString(int nIndex,char* szData)const
	{
		if (m_hComboBox)
			SendMessageA(m_hComboBox, CB_GETLBTEXT, nIndex, (LPARAM)szData);
	}

	//���õ�ǰ��ѡ��
	inline void SetDefault(int nIndex)const
	{
		if (m_hComboBox)
			PostMessageA(m_hComboBox, CB_SETCURSEL, nIndex, 0);
	}

	//��ȡ��ǰ��ѡ��
	inline UINT GetDefault()const
	{
		UINT nIndex;
		if (m_hComboBox)
			nIndex = SendMessageA(m_hComboBox, CB_GETCURSEL, 0, 0);
		return nIndex;
	}

	//���ô�С
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

	//����λ��
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
	//����һ����Ͽ�    CBS_DROPDOWN       CBS_DROPDOWNLIST    
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

	//ɾ��һ����Ͽ�
	void Delete()
	{
		if (m_hComboBox)
			DestroyWindow(m_hComboBox);
		m_hComboBox = 0;
	}
};