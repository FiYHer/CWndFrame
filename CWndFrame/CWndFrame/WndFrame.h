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
	//���һ��Ҫ����Ĵ��ڹ���
	VOID CWAddEvent(UINT, VOID(*lpfn)(HWND hWnd, WPARAM wParam, LPARAM lParam));
	//ɾ��һ��Ҫ����Ĵ��ڹ���
	VOID CWDeleteEvent(UINT);
public:
	///////////////////�����ǰ�ť��
	//��ʼ����ť��Ϣ
	VOID CWBaseButtonInfo();
	//Ѱ��ָ����ť�ĵ�����
	BOOL CWFindButton(HWND, ButtonIDList::iterator&);
	//���һ����ť
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
	//ɾ��һ����ť
	VOID CWDeleteButton(HWND);
	//ɾ�����а�ť
	VOID CWDeleteAllButton();
	//���һ��λͼ����ť
	VOID CWAddBmpToButton(HWND, CHAR*, int, int);
	//���ð�ť���ַ���
	VOID CWSetButtonString(HWND, CHAR*);
	//��ȡ��ť���ַ���
	VOID CWGetButtonString(HWND, CHAR*);
	//���ð�ť�ĵ�ǰ״̬
	LRESULT CWSetButtonCheck(HWND, UINT);
	//��ȡ��ť�ĵ�ǰ״̬
	LRESULT CWGetButtonCheck(HWND);
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
};

