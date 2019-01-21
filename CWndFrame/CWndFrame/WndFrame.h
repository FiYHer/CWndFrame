#pragma once
#include "CWndFrame_Public.h"

class CWndFrame
{
private:
	//��������ʾ��ʽ
	int m_ShowCmd;
	//�����ھ��
	HWND m_WindowHwnd;
	//����������
	char* m_WszWndName;
	//����ʵ�����
	HINSTANCE m_Hinstance;
	//���򴰿���
	WNDCLASSEX m_WndClass;
	//���ڹ����¼��б�
	EventList m_EventList;
	//������Ϣ
	CreateWindowExInfo m_CreateWindowExInfo;
	//��ť����б�
	ButtonIDList m_ButtonIDList;
	//�༭�����б�
	EditList m_EditList;
	//�������б�
	ScrollBarList m_ScrollBarList;
	//���ڹ��̺���ָ��
	VOID(*m_lpWinProc)(PWinProcInfo);
	//��̬������ָ�룬��̬���ڹ��̺�����Ҫ���
	static CWndFrame* m_CWindows;
private:
	//��̬���ڹ���
	static LRESULT CALLBACK CWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	//Ĭ�Ϲ��캯��
	CWndFrame();
	//Ĭ����������
	virtual ~CWndFrame();
public:
	//��ȡ��������
	VOID CWGetHinstance(HINSTANCE);
	//��ȡ������ʾ����
	VOID CWGetCmdShow(int);
	//�ѷǾ�̬������ת��Ϊ��̬�����࣬�þ�̬����ʹ��
	static CWndFrame* CWGetStaticPoint(CWndFrame* WindowPoint = NULL);
	//�����MSG�ṹ��ѭ��
	int CWMsgProc();
	//������Ǽ��������Ҫ�������Ϣ
	BOOL CWCheckMessage(HWND, UINT, WPARAM, LPARAM);
	//��ָ���������һ���µ�ID
	LONG CWSetNewID(HWND, LONG);
	//������ǳ�ʼ��һ�´��ڵĻ�����Ϣ
	VOID CWBaseCreateWindowExInfo();
	//ע�ᴰ����
	BOOL CWRegisterClassEx(WNDCLASSEX wnd = {});
	//������Ǵ�������
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
	/////////////////������������ڵ�
	//���ô��ں����������
	VOID CWSetWindowProc(VOID(*lpfn)(PWinProcInfo));
	//���һ��Ҫ����Ĵ��ڹ���
	VOID CWAddEvent(UINT);
	//ɾ��һ��Ҫ����Ĵ��ڹ���
	VOID CWDeleteEvent(UINT);
	//���������ڴ�С
	VOID CWSetMainWindowSize(int, int);
	//����������λ��
	VOID CWSetMainWindowPos(int, int);
	//���ô��ڻ��߿ؼ��ķ��
	LONG CWSetStyle(HWND,LONG);
	//���ش��ڻ��߿ؼ�
	VOID CWSetHideStyle(HWND);
	//�жϴ��ڻ��߿ؼ��Ƿ�ɼ�
	BOOL CWGetVisible(HWND);
public:
	////////////////////////////////////////////////////////�����ǰ�ť��
	//��ʼ����ť��Ϣ
	VOID CWBaseButtonInfo();
	//Ѱ��ָ����ť�ĵ�����
	BOOL CWFindButton(HWND, ButtonIDList::iterator&);
	//���һ����ͨ��ť
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
	//���һ����ѡ��ѡ��
	HWND CWAddAutoCheckBoxButton();
	//���һ����ѡ��ѡ��
	HWND CWAddAuto3StateButton();
	//���һ����ѡ��
	HWND CWAddAutoRadioButton();
	//���һ�������
	HWND CWAddGroupBoxButton();
	//ɾ��һ����ť
	VOID CWDeleteButton(HWND);
	//ɾ�����а�ť
	VOID CWDeleteAllButton();
	//���һ��λͼ����ť
	VOID CWAddBmpToButton(HWND, CHAR*, int, int);
	//�ƶ���ťλ��
	VOID CWMoveButtonPos(HWND,int,int);
	//���ð�ť��С
	VOID CWSetButtonSize(HWND,int,int);
	//���ð�ť���ַ���
	BOOL CWSetButtonString(HWND, CHAR*);
	//��ȡ��ť���ַ���
	int CWGetButtonString(HWND, CHAR*);
	//���ð�ť�ĵ�ǰ״̬
	LRESULT CWSetButtonCheck(HWND, UINT);
	//��ȡ��ť�ĵ�ǰ״̬
	LRESULT CWGetButtonCheck(HWND);
	//���ð�ť
	VOID CWProhibitButton(HWND);
	//���ð�ť
	VOID CWEnableButton(HWND);
public:
	/////////�����Ǳ༭��
	//��ʼ���༭�������Ϣ
	VOID CWBaseEditInfo();
	//����ָ���ı༭����
	BOOL CWFindEdit(HWND, EditList::iterator&);
	//���һ���༭��
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
	//ɾ��һ���༭��
	VOID CWDeleteEdit();
	//ɾ��ȫ���༭��
	VOID CWDeleteAllEdit();
	//���ñ༭���ַ���
	VOID CWSetEditString(HWND, CHAR*);
	////��ȡ�༭���ַ���
	VOID CWGetEditString(HWND, CHAR*);

private:
	//////-------------------------�����ǹ�������
	//Ĭ�Ϲ����������¼�
	VOID CWDefaultScrollBarEvent(PWinProcInfo);
	//���û�����������Ϣ
	VOID CWBaseScrollBarInfo();
	//���ҹ�����
	BOOL CWFindSrcollBar(HWND, ScrollBarList::iterator&);
	//���ҹ�����
	BOOL CWFindSrcollBar(int, ScrollBarList::iterator&);
public:
	//���һ���������ؼ�
	HWND CWAddScrollBar(_In_ DWORD dwExStyle = NULL,
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
	//����Ĭ�Ϲ����������¼�
	VOID CWSetDefaultScrollBarEvent();
	//���ù��������ֵ
	VOID CWSetScrollBarMinAndMax(HWND,int,int);
	//���ù�������ǰ��ֵ
	VOID CWSetScrollBarCurrentIndex(HWND,int);
	//���ù�����������
	VOID CWSetScrollBarLineGranularity(HWND,int);
	//���ù�����ҳ����
	VOID CWSetScrollBarPageGranularity(HWND,int);
	//��ȡ��ǰ��������ֵ
	int CWGetCurrentScrollBarValue(HWND);

};

