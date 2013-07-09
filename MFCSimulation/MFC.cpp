#include "MFC.h"
#include "MY.h"
extern CMyWinApp theApp;

CWinApp * AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}
bool CCmdTarget::OnCmdMsg(UINT nID,int nCode)
{
	AFX_MSGMAP* pMessageMap;
	AFX_MSGMAP_ENTRY* lpEntry;
	for(pMessageMap=GetMessageMap();pMessageMap!=NULL;pMessageMap=pMessageMap->pBaseMessageMap)
	{
		lpEntry=pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}
	return false;
}
LRESULT AfxWndProc(HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam,CWnd *pWnd)
{
	cout<<"AfxWndProc()"<<endl;
	return AfxCallWndProc(pWnd,hWnd,nMsg,wParam,lParam);
}
LRESULT AfxCallWndProc(CWnd* pWnd,HWND hWnd,UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	cout<<"AfxCallWndProc()"<<endl;
	LRESULT lResult=pWnd->WindowProc(nMsg,wParam,lParam);
	return lResult;
}
/**********************************************
* RTTI definition
**********************************************/

CRuntimeClass* CRuntimeClass::pFirstClass=NULL;
static char _lpszCObject[]="CObject";
CRuntimeClass CObject::classCObject={
	_lpszCObject,sizeof(CObject),0xffff,NULL,NULL
};
static AFX_CLASSINIT _init_CObject(&CObject::classCObject);

CRuntimeClass* CObject::GetRuntimeClass() const
{
	return &CObject::classCObject;
}
bool CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	CRuntimeClass* pClassThis=GetRuntimeClass();
	while(pClassThis!=NULL)
	{
		if(pClassThis==pClass)
			return true;
		pClassThis=pClassThis->m_pBaseClass;
	}
	return false;
}
CObject* CArchive::ReadObject(const CRuntimeClass* pClass)
{
	return (*(pClass->m_pfnCreateObject))();
}
////////////////////////////////////////////////
LRESULT CWnd::WindowProc(UINT nMsg,WPARAM wParam,LPARAM lParam)
{
	AFX_MSGMAP* pMessageMap;
	AFX_MSGMAP_ENTRY* lpEntry;

	if(nMsg==WM_COMMAND)
	{
		if(OnCommand(wParam,lParam))
			return 1L;
		else 
			return (LRESULT)DefWindowProc(nMsg,wParam,lParam);
	}
	pMessageMap=GetMessageMap();
	for(;pMessageMap!=NULL;pMessageMap=pMessageMap->pBaseMessageMap)
	{
		lpEntry=pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}
	return 0;
}
LRESULT CWnd::DefWindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	return true;
}
bool CWnd::OnCommand(WPARAM wParam,LPARAM lParam)
{
	cout<<"CWnd::OnCommand()"<<endl;
	return OnCmdMsg(0,0);
}
bool CFrameWnd::OnCommand(WPARAM wParam,LPARAM lParam)
{
	cout<<"CFrameWnd::OnCommand()"<<endl;
	return CWnd::OnCommand(wParam,lParam);
}
CView* CFrameWnd::GetActiveView() const
{
	return m_pViewActive;
}
bool CFrameWnd::OnCmdMsg(UINT nID, int nCode)
{
	CView*pView=GetActiveView();
	if(pView->OnCmdMsg(nID,nCode))
		return true;
	if(CWnd::OnCmdMsg(nID,nCode))
		return true;
	CWinApp* pApp=AfxGetApp();
	if(pApp->OnCmdMsg(nID,nCode))
		return true;
	return false;
}
bool CDocument::OnCmdMsg(UINT nID,int nCode)
{
	if(CCmdTarget::OnCmdMsg(nID,nCode))
		return true;
	return false;
}
bool CView::OnCmdMsg(UINT nID,int nCode)
{
	if(CWnd::OnCmdMsg(nID,nCode))
		return true;
	bool bHandled=false;
	bHandled=m_pDocument->OnCmdMsg(nID,nCode);
	return bHandled;
}

IMPLEMENT_DYNAMIC(CCmdTarget,CObject)
IMPLEMENT_DYNAMIC(CWinThread,CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp,CWinThread)
IMPLEMENT_DYNCREATE(CWnd,CCmdTarget)
IMPLEMENT_DYNCREATE(CFrameWnd,CWnd)
IMPLEMENT_DYNAMIC(CDocument,CCmdTarget)
IMPLEMENT_DYNAMIC(CView,CWnd)
IMPLEMENT_DYNCREATE(CMyFrameWnd,CFrameWnd)
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
IMPLEMENT_DYNCREATE(CMyView,CView)

AFX_MSGMAP* CCmdTarget::GetMessageMap() const
{
	return &CCmdTarget::messageMap;
}
AFX_MSGMAP CCmdTarget::messageMap={
	NULL,
	(AFX_MSGMAP_ENTRY*)&(CCmdTarget::_messageEntries)
};
AFX_MSGMAP_ENTRY CCmdTarget::_messageEntries[]=
{
	{0,0,CCmdTargetid,0,AfxSig_end,0}
};
BEGIN_MESSAGE_MAP(CWnd,CCmdTarget)
ON_COMMAND(CWndid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFrameWnd,CWnd)
ON_COMMAND(CFrameWndid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDocument,CCmdTarget)
ON_COMMAND(CFrameWndid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CView,CWnd)
ON_COMMAND(CViewid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWinApp,CCmdTarget)
ON_COMMAND(CWinAppid,0)
END_MESSAGE_MAP()
