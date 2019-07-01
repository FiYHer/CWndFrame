#pragma once

#include <Windows.h>
#include <Windowsx.h>

#include <string>
#include <CommCtrl.h>
using namespace std;

//默认情况下，列表视图控件不显示项目图像。要显示项目图像，您必须创建图像列表并将它们与控件关联
/*
样式:
LVS_ICON 图标
LVS_REPORT 报表
LVS_SMALLICON 小图标
LVS_LIST 列表

LVS_ALIGNLEFT 项目在图标和小图标视图中左对齐。 
LVS_ALIGNMASK 控件的当前对齐方式
LVS_ALIGNTOP 项目与图标和小图标视图中的列表视图控件的顶部对齐。 
LVS_AUTOARRANGE 图标自动排列在图标和小图标视图中。 
LVS_EDITLABELS 可以就地编辑项目文本
LVS_NOCOLUMNHEADER  列标题不会显示在报表视图中
LVS_NOLABELWRAP 项目文本显示在图标视图中的单行上
LVS_NOSCROLL 滚动已禁用
LVS_NOSORTHEADER 列标题不像按钮那样工作
LVS_OWNERDATA 此样式指定虚拟列表视图控件
LVS_OWNERDRAWFIXED 所有者窗口可以在报表视图中绘制项目
LVS_SHAREIMAGELISTS 控件被销毁时，不会删除图像列表
LVS_SHOWSELALWAYS  即使控件没有焦点，也始终显示选择
LVS_SINGLESEL  一次只能选择一个项目
LVS_SORTASCENDING 项目索引按项目文本按升序排序
LVS_SORTDESCENDING 项目索引根据项目文本按降序排序。 


修改扩展风格应该使用ListView_SetExtendedListViewStyle，ListView_SetExtendedListViewStyleEx和ListView_GetExtendedListViewStyle
LVS_EX_AUTOAUTOARRANGE 如果未设置图标位置，则自动排列图标
LVS_EX_FULLROWSELECT 选中高亮
LVS_EX_AUTOCHECKSELECT 单击即自动选中复选框
LVS_EX_CHECKBOXES 勾选框
LVS_EX_AUTOSIZECOLUMNS 自动调整listview列的大小
LVS_EX_GRIDLINES 网格线
LVS_EX_BORDERSELECT 选择项目时更改边框颜色，而不是突出显示该项目
LVS_EX_COLUMNSNAPPOINTS 。用户调整列大小时捕捉到最小列宽
LVS_EX_DOUBLEBUFFER 通过双缓冲涂料，减少闪烁
LVS_EX_FLATSB  在列表视图中启用平面滚动条
LVS_EX_FULLROWSELECT  选择项目后，项目及其所有子项目将突出显示
LVS_EX_HEADERDRAGDROP  在列表视图控件中启用列的拖放重新排序
LVS_EX_HEADERINALLVIEWS  在所有视图模式下显示列标题
LVS_EX_HIDELABELS 隐藏图标和小图标视图中的标签 
LVS_EX_JUSTIFYCOLUMNS 图标排列在用完整个视图的列中 
LVS_EX_SUBITEMIMAGES 允许显示子项目的图像
LVS_EX_TRANSPARENTBKGND 背景由父母通过WM_PRINTCLIENT绘制
LVS_EX_TRANSPARENTSHADOWTEXT  仅在透明背景上启用阴影文本
https://docs.microsoft.com/zh-cn/windows/desktop/Controls/extended-list-view-styles
*/

class CListView
{
private:
	//主窗口的句柄
	HWND m_hWnd;
	//程序的实例
	HINSTANCE m_hInstance;
	//列表视图控件的句柄
	HWND m_hListView;

public:
	//设置列表视图控件的视图
	/*
	LV_VIEW_DETAILS 详细视图
	LV_VIEW_ICON 大图标视图
	LV_VIEW_LIST 列表视图
	LV_VIEW_SMALLICON 小图标
	LV_VIEW_TILE 平铺
	*/
	inline void SetView(DWORD dwType)const
	{
		ListView_SetView(m_hListView, dwType);
	}

	//设置列
	inline void SetColumn(const LPSTR strData,int nIndex,int nSize = 50)const
	{
		if (m_hListView)
		{
			//https://docs.microsoft.com/en-us/windows/desktop/api/Commctrl/ns-commctrl-taglvcolumna
			LVCOLUMNA stColumn;
			memset(&stColumn, 0, sizeof(LVCOLUMNA));
			//指示哪一些成员有效
			//LVCF_TEXT pszText成员有效
			//LVCF_FMT fmt成员有效
			//LVCF_WIDTH cx成员有效
			//LVCF_SUBITEM iSubItem成员有效
			//LVCF_IMAGE 该IIMAGE成员是有效的。
			//LVCF_ORDER 该iOrder成员是有效的
			//LVCF_MINWIDTH 该cxMin成员是有效的
			//LVCF_DEFAULTWIDTH 该cxDefault成员是有效的
			//LVCF_IDEALWIDTH 该cxIdeal成员是有效的
			stColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
			//对齐值
			//LVCFMT_LEFT 左对齐
			//LVCFMT_RIGHT 右对齐
			//LVCFMT_CENTER 居中
			//LVCFMT_IMAGE 该项目显示图像列表中的图像
			//LVCFMT_BITMAP_ON_RIGHT 位图显示在文本右侧
			//LVCFMT_COL_HAS_IMAGES 标题项包含图像列表中的图像
			//LVCFMT_FIXED_WIDTH  无法调整列的大小
			//LVCFMT_FIXED_RATIO 宽度将随行高增加
			//LVCFMT_SPLITBUTTON 列是一个拆分按钮
			stColumn.fmt = LVCFMT_CENTER;
			//文本字符串
			stColumn.pszText = strData;
			//列的宽度
			stColumn.cx = nSize;
			//列关联的子项索引
			stColumn.iSubItem = nIndex;
			//0开始的列偏移
			stColumn.iOrder;
			//列的最小宽度
			stColumn.cxMin;
			//默认宽度
			stColumn.cxDefault;
			//列的理想宽度
			stColumn.cxIdeal;
			ListView_InsertColumn(m_hListView, nIndex, &stColumn);
		}
	}

	//设置项
	inline void SetItem(const LPSTR strData,int nItem,int nIndex)const
	{
		if (m_hListView)
		{
			//https://docs.microsoft.com/en-us/windows/desktop/api/Commctrl/ns-commctrl-taglvitema
			LVITEMA stItem;
			memset(&stItem, 0, sizeof(LVITEMA));
			stItem.pszText = strData;
			stItem.cchTextMax = MAX_PATH;
			//指定此结构的哪些成员包含
			//LVIF_COLFMT 该piColFmt成员有效或必须设置
			//LVIF_COLUMNS 该cColumns 该cColumns成员有效或必须设置
			//LVIF_GROUPID 该 iGroupId成员有效或必须设置
			//LVIF_IMAGE 该IIMAGE成员有效或必须设置
			//LVIF_INDENT 该iIndent成员有效或必须设置
			//LVIF_TEXT 该pszText成员有效或必须设置
			stItem.mask = LVIF_TEXT;
			//从0开始的索引
			stItem.iItem = nItem;
			//子项的索引
			stItem.iSubItem = nIndex;
			if(nIndex == 0)
				ListView_InsertItem(m_hListView, &stItem);
			else 
				ListView_SetItem(m_hListView, &stItem);
		}
	}

	//获取当前选中的索引行号
	inline int GetSelectMask()const
	{
		int nRet = -1;
		if (m_hListView)
			nRet = ListView_GetSelectionMark(m_hListView);
		return nRet;
	}

	//删除指定的列 一列(向下)
	inline void DeleteColumn(int nIndex)const
	{
		if (m_hListView)
			ListView_DeleteColumn(m_hListView, nIndex);
	}

	//删除指定的子项 一行(向右)
	inline void DeleteItem(int nIndex)const
	{
		if (m_hListView)
			ListView_DeleteItem(m_hListView, nIndex);
	}

	//是否显示为组
	inline void EnableGruopView(bool bUse)const
	{
		if (m_hListView)
			ListView_EnableGroupView(m_hListView, bUse);
	}

	//检查是否选择 LVS_EX_CHECKBOXES样式
	inline bool GetCheckState(int nIndex)const
	{
		bool bRet = false;
		if (m_hListView)
			bRet = ListView_GetCheckState(m_hListView, nIndex);
		return bRet;
	}

	//获取组的数量
	inline int GetGruopCount()const
	{
		int nRet = 0;
		if (m_hListView)
			nRet = ListView_GetGroupCount(m_hListView);
		return nRet;
	}

	//获取项的数量
	inline int GetItemCount()const
	{
		int nRet = 0;
		if (m_hListView)
			nRet = ListView_GetItemCount(m_hListView);
		return nRet;
	}

	//获取指定项的字符串
	inline void GetItemText(int nIndex,int nItem,LPSTR pStr,int nMaxLen)const
	{
		if (m_hListView)
			ListView_GetItemText(m_hListView, nIndex, nItem, pStr, nMaxLen);
	}

	//获取文本背景颜色
	inline COLORREF GetTextBkColor()const
	{
		COLORREF stRGB = { 0 };
		if (m_hListView)
			stRGB = ListView_GetTextBkColor(m_hListView);
		return stRGB;
	}

	//获取文本颜色
	inline COLORREF GetTextColor()const
	{
		COLORREF stRGB = { 0 };
		if (m_hListView)
			stRGB = ListView_GetTextColor(m_hListView);
		return stRGB;
	}

	//获取视图类型
	/*LV_VIEW_DETAILS
	每个项目都显示在自己的行上，信息按列排列。最左边的列始终左对齐，包含小图标和标签
		LV_VIEW_ICON
		每个项目都显示为一个小图标，其右侧是标签。用户可以将项目拖动到任何位置。
		LV_VIEW_LIST
		每个项目都显示为一个小图标，右侧有一个标签。项目按列排列，用户无法将它们拖动到任意位置
		LV_VIEW_SMALLICON 
		每个项目都显示为一个小图标，其右侧是标签。用户可以将项目拖动到任何位置
		LV_VIEW_TILE 
		每个项目显示为一个完整大小的图标，旁边有一行或多行标签*/
	inline DWORD GetView()const
	{
		DWORD dwView = 0;
		if (m_hListView)
			dwView = ListView_GetView(m_hListView);
		return dwView;
	}

	//重绘
	inline void RenderAgain(int nBegin,int nEnd)const
	{
		if (m_hListView)
			ListView_RedrawItems(m_hListView, nBegin, nEnd);
	}

	//删除指定的组
	inline void RemoveGruop(int nGruopID)const
	{
		if (m_hListView)
			ListView_RemoveGroup(m_hListView, nGruopID);
	}

	//删除所有的组
	inline void RemoveAllGruop()const
	{
		if (m_hListView)
			ListView_RemoveAllGroups(m_hListView);
	}

	////获取指定的列信息
	//inline void GetColumnInfo(int nIndex, LPLVCOLUMN pColumn)const
	//{
	//	if (m_hListView)
	//		ListView_GetColumn(m_hListView, nIndex, pColumn);
	//}

	//确保视图列表的可见
	//inline void SureVisible(int nIndex,bool bUse)const
	//{
	//	if (m_hListView)
	//		ListView_EnsureVisible(m_hListView, nIndex, bUse);
	//}

	//开始修改指定的项
	//inline void EditLable(int nIndex)const
	//{
	//	if (m_hListView)
	//		ListView_EditLabel(m_hListView, nIndex);
	//}

	//设置文本颜色
	inline void SetTextColor(COLORREF stRGB)const
	{
		if (m_hListView)
			ListView_SetTextColor(m_hListView, stRGB);
	}

	//设置文本得分背景颜色
	inline void SetBkTextColor(COLORREF stRGB)const
	{
		if (m_hListView)
			ListView_SetTextBkColor(m_hListView, stRGB);
	}

	//更新视图列表
	inline void Update(int nIndex)const
	{
		if (m_hListView)
			ListView_Update(m_hListView, nIndex);
	}

	//设置拓展样式
	inline void SetExstyle(DWORD dwStyle)const
	{
		if(m_hListView)
			ListView_SetExtendedListViewStyle(m_hListView, dwStyle);
	}

	//清空所有
	inline void DeleteAllItems()const
	{
		if(m_hListView)
			ListView_DeleteAllItems(m_hListView);
	}

	//设置大小
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

	//设置位置
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
	//创建
	HWND Create(DWORD dwStyle = WS_VISIBLE |WS_CHILD | LVS_AUTOARRANGE | LVS_REPORT | LVS_SHOWSELALWAYS)
	{
		if (m_hListView)
			return 0;
		//syslistview32
		m_hListView = CreateWindowExA(WS_EX_CLIENTEDGE, WC_LISTVIEW, 0, dwStyle, 100, 
			100, 100, 100,m_hWnd, 0, m_hInstance, 0);
		if (m_hListView)
			//超过10000后数据再进行插入将不可预料,需要的话可以修改成更大的值
			ListView_SetItemCountEx(m_hListView, 10000, LVSICF_NOINVALIDATEALL);
		return m_hListView;
	}

	//删除
	void Delete()
	{
		if (m_hListView)
			DestroyWindow(m_hListView);
	}

};


