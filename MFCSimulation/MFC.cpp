#include "MFC.h"
#include "MY.h"
extern CMyWinApp theApp;

CWinApp * AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
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
