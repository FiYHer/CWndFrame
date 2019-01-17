#pragma once
#include "CWndFrame_Public.h"

class CWndFrame
{
private:
	//主窗口显示方式
	int m_ShowCmd;
	//主窗口句柄
	HWND m_WindowHwnd;
	//主窗口类名
	char* m_WszWndName;
	//程序实例句柄
	HINSTANCE m_Hinstance;
	//程序窗口类
	WNDCLASSEX m_WndClass;
	//窗口过程事件列表
	EventList m_EventList;
	//创建信息
	CreateWindowExInfo m_CreateWindowExInfo;
	//按钮句柄列表
	ButtonIDList m_ButtonIDList;
	//编辑框句柄列表
	EditList m_EditList;
	//静态窗口类指针，静态窗口过程函数需要这个
	static CWndFrame* m_CWindows;
private:
	//静态窗口过程
	static LRESULT CALLBACK CWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	//默认构造函数
	CWndFrame();
	//默认析构函数
	virtual ~CWndFrame();
public:
	//获取程序事例
	VOID CWGetHinstance(HINSTANCE);
	//获取程序显示方法
	VOID CWGetCmdShow(int);
	//把非静态窗口类转化为静态窗口类，让静态函数使用
	static CWndFrame* CWGetStaticPoint(CWndFrame* WindowPoint = NULL);
	//这个是MSG结构体循环
	int CWMsgProc();
	//这个就是检查我们需要处理的消息
	BOOL CWCheckMessage(HWND, UINT, WPARAM, LPARAM);
	//这里就是初始化一下窗口的基本信息
	VOID CWBaseCreateWindowExInfo();
	//注册窗口类
	BOOL CWRegisterClassEx(WNDCLASSEX wnd = {});
	//这个就是创建窗口
	HANDLE CWCreateWindowExA(_In_ DWORD dwExStyle = NULL,
		_In_opt_ LPCSTR lpClassName = NULL,
		_In_opt_ LPCSTR lpWindowName = NULL,
		_In_ DWORD dwStyle = NULL,
		_In_ int X = NULL,
		_In_ int Y = NULL,
		_In_ int nWidth = NULL,
		_In_ int nHeight = NULL,
		_In_opt_ HWND hWndParent = NULL,
		_In_opt_ HMENU hMenu = NULL,
		_In_opt_ HINSTANCE hInstance = NULL,
		_In_opt_ LPVOID lpParam = NULL);
	/////////////////这里就是主窗口的
	//添加一个要处理的窗口过程
	VOID CWAddEvent(UINT, VOID(*lpfn)(HWND hWnd, WPARAM wParam, LPARAM lParam));
	//删除一个要处理的窗口过程
	VOID CWDeleteEvent(UINT);
public:
	///////////////////这里是按钮的
	//初始化按钮信息
	VOID CWBaseButtonInfo();
	//寻找指定按钮的迭代器
	BOOL CWFindButton(HWND, ButtonIDList::iterator&);
	//添加一个按钮
	HWND CWAddButton(_In_ DWORD dwExStyle = NULL,
		_In_opt_ LPCSTR lpClassName = NULL,
		_In_opt_ LPCSTR lpWindowName = NULL,
		_In_ DWORD dwStyle = NULL,
		_In_ int X = NULL,
		_In_ int Y = NULL,
		_In_ int nWidth = NULL,
		_In_ int nHeight = NULL,
		_In_opt_ HWND hWndParent = NULL,
		_In_opt_ HMENU hMenu = NULL,
		_In_opt_ HINSTANCE hInstance = NULL,
		_In_opt_ LPVOID lpParam = NULL);
	//删除一个按钮
	VOID CWDeleteButton(HWND);
	//删除所有按钮
	VOID CWDeleteAllButton();
	//添加一张位图给按钮
	VOID CWAddBmpToButton(HWND, CHAR*, int, int);
	//设置按钮的字符串
	VOID CWSetButtonString(HWND, CHAR*);
	//获取按钮的字符串
	VOID CWGetButtonString(HWND, CHAR*);
	//设置按钮的当前状态
	LRESULT CWSetButtonCheck(HWND, UINT);
	//获取按钮的当前状态
	LRESULT CWGetButtonCheck(HWND);
public:
	/////////这里是编辑框
	//初始化编辑框基本信息
	VOID CWBaseEditInfo();
	//查找指定的编辑框句柄
	BOOL CWFindEdit(HWND, EditList::iterator&);
	//添加一个编辑框
	HWND CWAddEdit(_In_ DWORD dwExStyle = NULL,
		_In_opt_ LPCSTR lpClassName = NULL,
		_In_opt_ LPCSTR lpWindowName = NULL,
		_In_ DWORD dwStyle = NULL,
		_In_ int X = NULL,
		_In_ int Y = NULL,
		_In_ int nWidth = NULL,
		_In_ int nHeight = NULL,
		_In_opt_ HWND hWndParent = NULL,
		_In_opt_ HMENU hMenu = NULL,
		_In_opt_ HINSTANCE hInstance = NULL,
		_In_opt_ LPVOID lpParam = NULL);
	//删除一个编辑框
	VOID CWDeleteEdit();
	//删除全部编辑框
	VOID CWDeleteAllEdit();
	//设置编辑框字符串
	VOID CWSetEditString(HWND, CHAR*);
	////获取编辑框字符串
	VOID CWGetEditString(HWND, CHAR*);
};

