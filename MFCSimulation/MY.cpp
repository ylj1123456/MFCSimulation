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
int main(int argc,char* argv[])
{
	CWinApp* pApp=AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();
}