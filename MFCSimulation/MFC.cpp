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
IMPLEMENT_DYNAMIC(CCmdTarget,CObject)
IMPLEMENT_DYNAMIC(CWinThread,CCmdTarget)
IMPLEMENT_DYNAMIC(CWinApp,CWinThread)
IMPLEMENT_DYNAMIC(CWnd,CCmdTarget)
IMPLEMENT_DYNAMIC(CFrameWnd,CWnd)
IMPLEMENT_DYNAMIC(CDocument,CCmdTarget)
IMPLEMENT_DYNAMIC(CView,CWnd)