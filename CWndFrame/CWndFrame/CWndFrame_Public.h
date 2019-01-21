#ifndef _CWndFrame_Public_
#define _CWndFrame_Public_

/*
win32窗口框架的必备头文件


*/

////window系统下必备
#include <windows.h>
#include <string.h>//字符串
#include <malloc.h>//内存
#include <process.h>//进程

//需要用到C++的STL
#include <list>
using namespace std;//必备命名空间

//让按钮具有XP风格
#pragma comment(linker,"\"/manifestdependency:type='win32' "\
						"name='Microsoft.Windows.Common-Controls' "\
						"version='6.0.0.0' processorArchitecture='*' "\
						"publicKeyToken='6595b64144ccf1df' language='*'\"")


#define CWWindowShow 10//默认显示方法
#define CWWndClassName "WindowFrame"//窗口类名
#define CWCHARlen 100//字符串长度
#define CWnWidth 500//窗口默认宽
#define CWnHeight 500//窗口默认高
#define CWX 0//窗口默认显示位置x
#define CWY 0//窗口默认显示位置y

#define CWButton "Button"//按钮类
#define CWButtonName "ButtonName"//按钮默认名字！
#define CWButtonnWidth 100//按钮默认宽
#define CWButtonnHeight 100//按钮默认高
#define CWButtonX 0//默认位置x
#define CWButtonY 0//默认位置Y
#define CWButtonID 5000//按钮的默认ID
#define CWButtonPushDown (WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON)//下压式按钮
#define CWButtonCheckBox (WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX )//复选框按钮
#define CWButtonState (WS_CHILD | WS_VISIBLE | BS_AUTO3STATE)//三选按钮
#define CWButtonRadio (WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON)//复选按钮
#define CWButtonGroup (WS_CHILD | WS_VISIBLE | BS_GROUPBOX)//分组按钮
#define CWButtonCheck 1//选择状态
#define CWButtonUnCheck 0//不选择状态
#define CWButtonMinate 2//灰色状态





#define CWEdit "EDIT"//编辑框类名
#define CWEditStyle (WS_CHILD|WS_VISIBLE|ES_MULTILINE)//编辑框类型
#define CWEditID 6000//编辑框默认ID
#define CWEditName "Edit"//编辑框的名字
#define CWEditHeight 200//编辑框的高度
#define CWEditWidth 200//编辑框的宽度
#define CWEditX 0//编辑框的开始坐标轴x
#define CWEditY 0//编辑框的开始坐标轴y
#define CWEditPassWord (WS_CHILD|WS_VISIBLE|ES_PASSWORD)//密码编辑框
#define CWEditAutoScroll (WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_AUTOVSCROLL)//自动滚动编辑框
#define CWEditNumber (WS_CHILD|WS_VISIBLE|ES_NUMBER)//数字编辑框
#define CWEditReadOnly (WS_CHILD|WS_VISIBLE|ES_READONLY)//只读编辑框





#define CWScrollBar "SCROLLBAR"//滚动条类名
#define CWScrollBarVertStyle WS_CHILD|WS_VISIBLE|SB_VERT//滚动条垂直类型
#define CWscrollBarHorzStyle WS_CHILD|WS_VISIBLE|SB_VERT//滚动条水平类型
#define CWScrollBarId 9000//滚动条默认ID
#define CWScrollBarName "ScrollBar"//默认滚动条名字
#define CWScrollBarX 0//默认滚动条x位置
#define CWScrollBarY 0//默认滚动条y位置
#define CWScrollBarHeight 100//默认滚动条高
#define CWScrollBarWidth 100//默认滚动条宽





typedef list<UINT> EventList;

typedef struct strWinProcInfo
{
	HWND hWnd;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
}WinProcInfo,*PWinProcInfo;


//创建函数【CreateaWindowExA】参数结构体
typedef struct strCreateWindowExInfo
{
	//各个成员函数参见CeateWindowExA函数
	DWORD dwExStyle;
	LPCSTR lpClassName;
	LPCSTR lpWindowName;
	DWORD dwStyle;
	int X;
	int Y;
	int nWidth;
	int nHeight;
	HWND hWndParent;
	HMENU hMenu;
	HINSTANCE hInstance;
	LPVOID lpParam;
}CreateWindowExInfo, *PCreateWindowExInfo;


//公共窗口控件句柄结构体
typedef struct strHwndIndo
{
	HWND ButtonHwnd;//控件的句柄
	UINT ButtonNumber;//控件的ID
}HwndIndo, *PHwndIndo;

//按钮控件句柄结构体
typedef struct strButtonId
{
	HwndIndo hwndinfo;//控件基本信息
	HBITMAP hBitmap;//按钮的位图句柄
}ButtonId, *PButtonId;
typedef list<ButtonId> ButtonIDList;

//编辑框控件句柄结构体
typedef struct strEditInfo
{
	HwndIndo hwndInfo;//控件的基本信息
}EditInfo, *PEditInfo;
typedef list<EditInfo> EditList;

//滚动条控件
typedef struct strScrollBarInfo
{
	HwndIndo hwndInfo;
	int Min;//最大值
	int Max;//最小值
	int CurrentIndex;//当前值
	bool Vert;//是否是垂直
	int LineGranularity;//行粒度
	int PageGranularity;//页粒度
}ScrollBarInfo,*PScrollBarInfo;
typedef list<ScrollBarInfo> ScrollBarList;




#endif
