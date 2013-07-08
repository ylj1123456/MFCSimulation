#include "MY.h"

CMyWinApp theApp;
CMyFrameWnd::CMyFrameWnd(){
	cout<<"CMyFrameWnd::CMyFrameWnd \n";
	Create();
	
}
bool CMyWinApp::InitInstance(){
		cout<<"CMyWinApp::InitInstance"<<endl;
		m_pMainWnd=new CMyFrameWnd;
		return true;
	}
void PrintAllClasses()
{
	CRuntimeClass *pClass;
	for(pClass=CRuntimeClass::pFirstClass;pClass!=NULL; pClass=pClass->m_pNextClass)
	{
		cout<<pClass->m_lpszClassName<<endl;
	}
}
int main(int argc,char* argv[])
{
	/*
	CWinApp* pApp=AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
	*/
	//PrintAllClasses();
	CArchive ar;
	ar<<"123";
}