#pragma once

#include <Windows.h>
#include <Windowsx.h>

#include <string>
#include <CommCtrl.h>
using namespace std;

//Ĭ������£��б���ͼ�ؼ�����ʾ��Ŀͼ��Ҫ��ʾ��Ŀͼ�������봴��ͼ���б���������ؼ�����
/*
��ʽ:
LVS_ICON ͼ��
LVS_REPORT ����
LVS_SMALLICON Сͼ��
LVS_LIST �б�

LVS_ALIGNLEFT ��Ŀ��ͼ���Сͼ����ͼ������롣 
LVS_ALIGNMASK �ؼ��ĵ�ǰ���뷽ʽ
LVS_ALIGNTOP ��Ŀ��ͼ���Сͼ����ͼ�е��б���ͼ�ؼ��Ķ������롣 
LVS_AUTOARRANGE ͼ���Զ�������ͼ���Сͼ����ͼ�С� 
LVS_EDITLABELS ���Ծ͵ر༭��Ŀ�ı�
LVS_NOCOLUMNHEADER  �б��ⲻ����ʾ�ڱ�����ͼ��
LVS_NOLABELWRAP ��Ŀ�ı���ʾ��ͼ����ͼ�еĵ�����
LVS_NOSCROLL �����ѽ���
LVS_NOSORTHEADER �б��ⲻ��ť��������
LVS_OWNERDATA ����ʽָ�������б���ͼ�ؼ�
LVS_OWNERDRAWFIXED �����ߴ��ڿ����ڱ�����ͼ�л�����Ŀ
LVS_SHAREIMAGELISTS �ؼ�������ʱ������ɾ��ͼ���б�
LVS_SHOWSELALWAYS  ��ʹ�ؼ�û�н��㣬Ҳʼ����ʾѡ��
LVS_SINGLESEL  һ��ֻ��ѡ��һ����Ŀ
LVS_SORTASCENDING ��Ŀ��������Ŀ�ı�����������
LVS_SORTDESCENDING ��Ŀ����������Ŀ�ı����������� 


�޸���չ���Ӧ��ʹ��ListView_SetExtendedListViewStyle��ListView_SetExtendedListViewStyleEx��ListView_GetExtendedListViewStyle
LVS_EX_AUTOAUTOARRANGE ���δ����ͼ��λ�ã����Զ�����ͼ��
LVS_EX_FULLROWSELECT ѡ�и���
LVS_EX_AUTOCHECKSELECT �������Զ�ѡ�и�ѡ��
LVS_EX_CHECKBOXES ��ѡ��
LVS_EX_AUTOSIZECOLUMNS �Զ�����listview�еĴ�С
LVS_EX_GRIDLINES ������
LVS_EX_BORDERSELECT ѡ����Ŀʱ���ı߿���ɫ��������ͻ����ʾ����Ŀ
LVS_EX_COLUMNSNAPPOINTS ���û������д�Сʱ��׽����С�п�
LVS_EX_DOUBLEBUFFER ͨ��˫����Ϳ�ϣ�������˸
LVS_EX_FLATSB  ���б���ͼ������ƽ�������
LVS_EX_FULLROWSELECT  ѡ����Ŀ����Ŀ������������Ŀ��ͻ����ʾ
LVS_EX_HEADERDRAGDROP  ���б���ͼ�ؼ��������е��Ϸ���������
LVS_EX_HEADERINALLVIEWS  ��������ͼģʽ����ʾ�б���
LVS_EX_HIDELABELS ����ͼ���Сͼ����ͼ�еı�ǩ 
LVS_EX_JUSTIFYCOLUMNS ͼ������������������ͼ������ 
LVS_EX_SUBITEMIMAGES ������ʾ����Ŀ��ͼ��
LVS_EX_TRANSPARENTBKGND �����ɸ�ĸͨ��WM_PRINTCLIENT����
LVS_EX_TRANSPARENTSHADOWTEXT  ����͸��������������Ӱ�ı�
https://docs.microsoft.com/zh-cn/windows/desktop/Controls/extended-list-view-styles
*/

class CListView
{
private:
	//�����ڵľ��
	HWND m_hWnd;
	//�����ʵ��
	HINSTANCE m_hInstance;
	//�б���ͼ�ؼ��ľ��
	HWND m_hListView;

public:
	//�����б���ͼ�ؼ�����ͼ
	/*
	LV_VIEW_DETAILS ��ϸ��ͼ
	LV_VIEW_ICON ��ͼ����ͼ
	LV_VIEW_LIST �б���ͼ
	LV_VIEW_SMALLICON Сͼ��
	LV_VIEW_TILE ƽ��
	*/
	inline void SetView(DWORD dwType)const
	{
		ListView_SetView(m_hListView, dwType);
	}

	//������
	inline void SetColumn(const LPSTR strData,int nIndex,int nSize = 50)const
	{
		if (m_hListView)
		{
			//https://docs.microsoft.com/en-us/windows/desktop/api/Commctrl/ns-commctrl-taglvcolumna
			LVCOLUMNA stColumn;
			memset(&stColumn, 0, sizeof(LVCOLUMNA));
			//ָʾ��һЩ��Ա��Ч
			//LVCF_TEXT pszText��Ա��Ч
			//LVCF_FMT fmt��Ա��Ч
			//LVCF_WIDTH cx��Ա��Ч
			//LVCF_SUBITEM iSubItem��Ա��Ч
			//LVCF_IMAGE ��IIMAGE��Ա����Ч�ġ�
			//LVCF_ORDER ��iOrder��Ա����Ч��
			//LVCF_MINWIDTH ��cxMin��Ա����Ч��
			//LVCF_DEFAULTWIDTH ��cxDefault��Ա����Ч��
			//LVCF_IDEALWIDTH ��cxIdeal��Ա����Ч��
			stColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			//����ֵ
			//LVCFMT_LEFT �����
			//LVCFMT_RIGHT �Ҷ���
			//LVCFMT_CENTER ����
			//LVCFMT_IMAGE ����Ŀ��ʾͼ���б��е�ͼ��
			//LVCFMT_BITMAP_ON_RIGHT λͼ��ʾ���ı��Ҳ�
			//LVCFMT_COL_HAS_IMAGES ���������ͼ���б��е�ͼ��
			//LVCFMT_FIXED_WIDTH  �޷������еĴ�С
			//LVCFMT_FIXED_RATIO ��Ƚ����и�����
			//LVCFMT_SPLITBUTTON ����һ����ְ�ť
			stColumn.fmt = LVCFMT_CENTER;
			//�ı��ַ���
			stColumn.pszText = strData;
			//�еĿ��
			stColumn.cx = nSize;
			//�й�������������
			stColumn.iSubItem = nIndex;
			//0��ʼ����ƫ��
			stColumn.iOrder;
			//�е���С���
			stColumn.cxMin;
			//Ĭ�Ͽ��
			stColumn.cxDefault;
			//�е�������
			stColumn.cxIdeal;
			ListView_InsertColumn(m_hListView, nIndex, &stColumn);
		}
	}

	//������
	inline void SetItem(const LPSTR strData,int nItem,int nIndex)const
	{
		if (m_hListView)
		{
			//https://docs.microsoft.com/en-us/windows/desktop/api/Commctrl/ns-commctrl-taglvitema
			LVITEMA stItem;
			memset(&stItem, 0, sizeof(LVITEMA));
			stItem.pszText = strData;
			stItem.cchTextMax = MAX_PATH;
			//ָ���˽ṹ����Щ��Ա����
			//LVIF_COLFMT ��piColFmt��Ա��Ч���������
			//LVIF_COLUMNS ��cColumns ��cColumns��Ա��Ч���������
			//LVIF_GROUPID �� iGroupId��Ա��Ч���������
			//LVIF_IMAGE ��IIMAGE��Ա��Ч���������
			//LVIF_INDENT ��iIndent��Ա��Ч���������
			//LVIF_TEXT ��pszText��Ա��Ч���������
			stItem.mask = LVIF_TEXT;
			//��0��ʼ������
			stItem.iItem = nItem;
			//���������
			stItem.iSubItem = nIndex;
			if(nIndex == 0)
				ListView_InsertItem(m_hListView, &stItem);
			else 
				ListView_SetItem(m_hListView, &stItem);
		}
	}

	//��ȡ��ǰѡ�е������к�
	inline int GetSelectMask()const
	{
		int nRet = -1;
		if (m_hListView)
			nRet = ListView_GetSelectionMark(m_hListView);
		return nRet;
	}

	//ɾ��ָ������ һ��(����)
	inline void DeleteColumn(int nIndex)const
	{
		if (m_hListView)
			ListView_DeleteColumn(m_hListView, nIndex);
	}

	//ɾ��ָ�������� һ��(����)
	inline void DeleteItem(int nIndex)const
	{
		if (m_hListView)
			ListView_DeleteItem(m_hListView, nIndex);
	}

	//�Ƿ���ʾΪ��
	inline void EnableGruopView(bool bUse)const
	{
		if (m_hListView)
			ListView_EnableGroupView(m_hListView, bUse);
	}

	//����Ƿ�ѡ�� LVS_EX_CHECKBOXES��ʽ
	inline bool GetCheckState(int nIndex)const
	{
		bool bRet = false;
		if (m_hListView)
			bRet = ListView_GetCheckState(m_hListView, nIndex);
		return bRet;
	}

	//��ȡ�������
	inline int GetGruopCount()const
	{
		int nRet = 0;
		if (m_hListView)
			nRet = ListView_GetGroupCount(m_hListView);
		return nRet;
	}

	//��ȡ�������
	inline int GetItemCount()const
	{
		int nRet = 0;
		if (m_hListView)
			nRet = ListView_GetItemCount(m_hListView);
		return nRet;
	}

	//��ȡָ������ַ���
	inline void GetItemText(int nIndex,int nItem,LPSTR pStr,int nMaxLen)const
	{
		if (m_hListView)
			ListView_GetItemText(m_hListView, nIndex, nItem, pStr, nMaxLen);
	}

	//��ȡ�ı�������ɫ
	inline COLORREF GetTextBkColor()const
	{
		COLORREF stRGB = { 0 };
		if (m_hListView)
			stRGB = ListView_GetTextBkColor(m_hListView);
		return stRGB;
	}

	//��ȡ�ı���ɫ
	inline COLORREF GetTextColor()const
	{
		COLORREF stRGB = { 0 };
		if (m_hListView)
			stRGB = ListView_GetTextColor(m_hListView);
		return stRGB;
	}

	//��ȡ��ͼ����
	/*LV_VIEW_DETAILS
	ÿ����Ŀ����ʾ���Լ������ϣ���Ϣ�������С�����ߵ���ʼ������룬����Сͼ��ͱ�ǩ
		LV_VIEW_ICON
		ÿ����Ŀ����ʾΪһ��Сͼ�꣬���Ҳ��Ǳ�ǩ���û����Խ���Ŀ�϶����κ�λ�á�
		LV_VIEW_LIST
		ÿ����Ŀ����ʾΪһ��Сͼ�꣬�Ҳ���һ����ǩ����Ŀ�������У��û��޷��������϶�������λ��
		LV_VIEW_SMALLICON 
		ÿ����Ŀ����ʾΪһ��Сͼ�꣬���Ҳ��Ǳ�ǩ���û����Խ���Ŀ�϶����κ�λ��
		LV_VIEW_TILE 
		ÿ����Ŀ��ʾΪһ��������С��ͼ�꣬�Ա���һ�л���б�ǩ*/
	inline DWORD GetView()const
	{
		DWORD dwView = 0;
		if (m_hListView)
			dwView = ListView_GetView(m_hListView);
		return dwView;
	}

	//�ػ�
	inline void RenderAgain(int nBegin,int nEnd)const
	{
		if (m_hListView)
			ListView_RedrawItems(m_hListView, nBegin, nEnd);
	}

	//ɾ��ָ������
	inline void RemoveGruop(int nGruopID)const
	{
		if (m_hListView)
			ListView_RemoveGroup(m_hListView, nGruopID);
	}

	//ɾ�����е���
	inline void RemoveAllGruop()const
	{
		if (m_hListView)
			ListView_RemoveAllGroups(m_hListView);
	}

	////��ȡָ��������Ϣ
	//inline void GetColumnInfo(int nIndex, LPLVCOLUMN pColumn)const
	//{
	//	if (m_hListView)
	//		ListView_GetColumn(m_hListView, nIndex, pColumn);
	//}

	//ȷ����ͼ�б�Ŀɼ�
	//inline void SureVisible(int nIndex,bool bUse)const
	//{
	//	if (m_hListView)
	//		ListView_EnsureVisible(m_hListView, nIndex, bUse);
	//}

	//��ʼ�޸�ָ������
	//inline void EditLable(int nIndex)const
	//{
	//	if (m_hListView)
	//		ListView_EditLabel(m_hListView, nIndex);
	//}

	//�����ı���ɫ
	inline void SetTextColor(COLORREF stRGB)const
	{
		if (m_hListView)
			ListView_SetTextColor(m_hListView, stRGB);
	}

	//�����ı��÷ֱ�����ɫ
	inline void SetBkTextColor(COLORREF stRGB)const
	{
		if (m_hListView)
			ListView_SetTextBkColor(m_hListView, stRGB);
	}

	//������ͼ�б�
	inline void Update(int nIndex)const
	{
		if (m_hListView)
			ListView_Update(m_hListView, nIndex);
	}

	//������չ��ʽ
	inline void SetExstyle(DWORD dwStyle)const
	{
		if(m_hListView)
			ListView_SetExtendedListViewStyle(m_hListView, dwStyle);
	}

	//�������
	inline void DeleteAllItems()const
	{
		if(m_hListView)
			ListView_DeleteAllItems(m_hListView);
	}

	//���ô�С
	inline void SetSize(int nValueX, int nValueY)const
	{
		if (m_hListView)
		{
			RECT stWindowRect;
			RECT stListViewRect;
			GetWindowRect(m_hListView, &stListViewRect);
			GetWindowRect(m_hWnd, &stWindowRect);
			MoveWindow(m_hListView, stListViewRect.left - stWindowRect.left,
				stListViewRect.top - stWindowRect.top, nValueX, nValueY, true);
		}
	}

	//����λ��
	inline void SetLcation(int nValueX, int nValueY)const
	{
		if (m_hListView)
		{
			RECT stRect;
			GetWindowRect(m_hListView, &stRect);
			MoveWindow(m_hListView, nValueX, nValueY, stRect.right - stRect.left,
				stRect.bottom - stRect.top, true);
		}
	}

public:
	CListView(HWND hWnd,HINSTANCE hInstance):m_hWnd(hWnd),m_hInstance(hInstance)
	{
		m_hListView = 0;
	}
	~CListView()
	{
		Delete();
	}
public:
	//����
	HWND Create(DWORD dwStyle = WS_VISIBLE |WS_CHILD | LVS_AUTOARRANGE | LVS_REPORT | LVS_SHOWSELALWAYS)
	{
		if (m_hListView)
			return 0;
		//syslistview32
		m_hListView = CreateWindowExA(WS_EX_CLIENTEDGE, WC_LISTVIEW, 0, dwStyle, 100, 
			100, 100, 100,m_hWnd, 0, m_hInstance, 0);
		if (m_hListView)
			//����10000�������ٽ��в��뽫����Ԥ��,��Ҫ�Ļ������޸ĳɸ����ֵ
			ListView_SetItemCountEx(m_hListView, 10000, LVSICF_NOINVALIDATEALL);
		return m_hListView;
	}

	//ɾ��
	void Delete()
	{
		if (m_hListView)
			DestroyWindow(m_hListView);
	}

};


