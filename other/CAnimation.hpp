#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>

#include <string>
using namespace std;

class CAnimation
{
private:
	//主窗口句柄
	HWND m_hWnd;
	//程序的实例
	HINSTANCE m_hInstance;
	//动画控件句柄
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
	//创建动画控件
	HWND Create(DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_BORDER)
	{
		if (m_hAnimation)
			return 0;

		m_hAnimation = Animate_Create(m_hWnd, 0, dwStyle, m_hInstance);
		return m_hAnimation;
	}

	//删除动画控件
	void Delete()
	{
		if (m_hAnimation)
			DestroyWindow(m_hAnimation);
	}

	//设置大小
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

	//设置位置
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

	//打开动画文件
	inline void OpenAVI(const string& strPath)const
	{
		if(m_hAnimation)
			Animate_Open(m_hAnimation, strPath.c_str());
	}

	//判断释放正在播放
	inline bool IsPlaying()const
	{
		bool bRet = false;
		if(m_hAnimation)
			bRet = (bool)Animate_IsPlaying(m_hAnimation);
		return bRet;
	}

	//开始动画播放
	inline void Satrt()
	{
		if(m_hAnimation)
		//0-从0开始 -1-播放到最后 -1无限播放
			Animate_Play(m_hAnimation, 0, -1, -1);
	}

	//暂停动画播放
	inline void Stop()
	{
		if(m_hAnimation)
			Animate_Stop(m_hAnimation);
	}

	//关闭动画播放
	inline void Close()
	{
		if(m_hAnimation)
			Animate_Close(m_hAnimation);
	}

};
