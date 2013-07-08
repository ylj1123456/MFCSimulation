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
	_lpszCObject,sizeof(CObject),6000,NULL,NULL
};
static void link(CRuntimeClass* classNew)
{
	classNew->m_pNextClass=CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass=classNew;
}