#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>

#include <string>
using namespace std;

class CAnimation
{
private:
	//�����ھ��
	HWND m_hWnd;
	//�����ʵ��
	HINSTANCE m_hInstance;
	//�����ؼ����
	HWND m_hAnimation;

public:
	CAnimation(HWND hWnd,HINSTANCE hInstance):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hAnimation = 0;
	}
	~CAnimation()
	{
		Delete();
	}
public:
	//���������ؼ�
	HWND Create(DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_BORDER)
	{
		if (m_hAnimation)
			return 0;

		m_hAnimation = Animate_Create(m_hWnd, 0, dwStyle, m_hInstance);
		return m_hAnimation;
	}

	//ɾ�������ؼ�
	void Delete()
	{
		if (m_hAnimation)
			DestroyWindow(m_hAnimation);
	}

	//���ô�С
	inline void SetSize(int nValueX,int nValueY)const
	{
		if (m_hAnimation)
		{
			RECT stAnimateRect;
			RECT stWindowRect;
			GetWindowRect(m_hAnimation, &stAnimateRect);
			GetWindowRect(m_hWnd, &stWindowRect);
			MoveWindow(m_hAnimation, stAnimateRect.left - stWindowRect.left,
				stAnimateRect.top - stWindowRect.top, nValueX, nValueY, true);
		}
	}

	//����λ��
	inline void SetLocation(int nValueX, int nValueY)const
	{
		if (m_hAnimation)
		{
			RECT stRect;
			GetWindowRect(m_hAnimation, &stRect);
			MoveWindow(m_hAnimation, nValueX, nValueY, stRect.right - stRect.left,
				stRect.bottom - stRect.top, true);
		}
	}

	//�򿪶����ļ�
	inline void OpenAVI(const string& strPath)const
	{
		if(m_hAnimation)
			Animate_Open(m_hAnimation, strPath.c_str());
	}

	//�ж��ͷ����ڲ���
	inline bool IsPlaying()const
	{
		bool bRet = false;
		if(m_hAnimation)
			bRet = (bool)Animate_IsPlaying(m_hAnimation);
		return bRet;
	}

	//��ʼ��������
	inline void Satrt()
	{
		if(m_hAnimation)
		//0-��0��ʼ -1-���ŵ���� -1���޲���
			Animate_Play(m_hAnimation, 0, -1, -1);
	}

	//��ͣ��������
	inline void Stop()
	{
		if(m_hAnimation)
			Animate_Stop(m_hAnimation);
	}

	//�رն�������
	inline void Close()
	{
		if(m_hAnimation)
			Animate_Close(m_hAnimation);
	}

};
