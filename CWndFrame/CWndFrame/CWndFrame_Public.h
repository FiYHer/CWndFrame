#ifndef _CWndFrame_Public_
#define _CWndFrame_Public_

/*
win32���ڿ�ܵıر�ͷ�ļ�


*/

////windowϵͳ�±ر�
#include <windows.h>
#include <string.h>//�ַ���
#include <malloc.h>//�ڴ�
#include <process.h>//����

//��Ҫ�õ�C++��STL
#include <list>
using namespace std;//�ر������ռ�

//�ð�ť����XP���
#pragma comment(linker,"\"/manifestdependency:type='win32' "\
						"name='Microsoft.Windows.Common-Controls' "\
						"version='6.0.0.0' processorArchitecture='*' "\
						"publicKeyToken='6595b64144ccf1df' language='*'\"")


#define CWWindowShow 10//Ĭ����ʾ����
#define CWWndClassName "WindowFrame"//��������
#define CWCHARlen 100//�ַ�������
#define CWnWidth 500//����Ĭ�Ͽ�
#define CWnHeight 500//����Ĭ�ϸ�
#define CWX 0//����Ĭ����ʾλ��x
#define CWY 0//����Ĭ����ʾλ��y

#define CWButton "Button"//��ť��
#define CWButtonName "ButtonName"//��ťĬ�����֣�
#define CWButtonnWidth 100//��ťĬ�Ͽ�
#define CWButtonnHeight 100//��ťĬ�ϸ�
#define CWButtonX 0//Ĭ��λ��x
#define CWButtonY 0//Ĭ��λ��Y
#define CWButtonID 5000//��ť��Ĭ��ID
#define CWButtonPushDown (WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON)//��ѹʽ��ť
#define CWButtonCheckBox (WS_CHILD | WS_VISIBLE | BS_CHECKBOX)//��ѡ��ť
#define CWButtonState (WS_CHILD | WS_VISIBLE | BS_3STATE)//��ѡ��ť
#define CWButtonRadio (WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON)//��ѡ��ť
#define CWButtonGroup (WS_CHILD | WS_VISIBLE | BS_GROUPBOX)//���鰴ť
#define CWButtonCheck 1//ѡ��״̬
#define CWButtonUnCheck 0//��ѡ��״̬
#define CWButtonMinate 2//��ɫ״̬

#define CWEdit "EDIT"//�༭������
#define CWEditStyle (WS_CHILD|WS_VISIBLE|ES_MULTILINE)//�༭������
#define CWEditID 6000//�༭��Ĭ��ID
#define CWEditName "Edit"//�༭�������
#define CWEditHeight 200//�༭��ĸ߶�
#define CWEditWidth 200//�༭��Ŀ��
#define CWEditX 0//�༭��Ŀ�ʼ������x
#define CWEditY 0//�༭��Ŀ�ʼ������y
#define CWEditPassWord (WS_CHILD|WS_VISIBLE|ES_PASSWORD)//����༭��
#define CWEditAutoScroll (WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_AUTOVSCROLL)//�Զ������༭��
#define CWEditNumber (WS_CHILD|WS_VISIBLE|ES_NUMBER)//���ֱ༭��
#define CWEditReadOnly (WS_CHILD|WS_VISIBLE|ES_READONLY)//ֻ���༭��

///���ڹ�����Ϣ��ؽṹ��
typedef struct strEventInfo
{
	UINT message;//������Ϣ
	VOID(*lpfn)(HWND, WPARAM, LPARAM);//����Ϣ��Ӧ�Ĵ�����
}EventInfo, *PEventInfo;
typedef list<EventInfo> EventList;

//����������CreateaWindowExA�������ṹ��
typedef struct strCreateWindowExInfo
{
	//������Ա�����μ�CeateWindowExA����
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


//�������ڿؼ�����ṹ��
typedef struct strHwndIndo
{
	HWND ButtonHwnd;//�ؼ��ľ��
	UINT ButtonNumber;//�ؼ���ID
}HwndIndo, *PHwndIndo;

//��ť�ؼ�����ṹ��
typedef struct strButtonId
{
	HwndIndo hwndinfo;//�ؼ�������Ϣ
	HBITMAP hBitmap;//��ť��λͼ���
}ButtonId, *PButtonId;
typedef list<ButtonId> ButtonIDList;

//�༭��ؼ�����ṹ��
typedef struct strEditInfo
{
	HwndIndo hwndInfo;//�ؼ��Ļ�����Ϣ
}EditInfo, *PEditInfo;
typedef list<EditInfo> EditList;





#endif
