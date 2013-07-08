#include "MFC.h"
#include "MY.h"
extern CMyWinApp theApp;

CWinApp * AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}