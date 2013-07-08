#include<iostream>
using namespace std;
#ifndef _MFC_H_
#define _MFC_H_
/*********************************
* declaration
**********************************/
class CObject;
class CCmdTarget;
class CWinApp;
class CWinThread;
class CWnd;
class CView;
class CFrameWnd;
class CDocument;
/********************************
* definition
*********************************/
class CObject{
public:
	CObject(){}
	~CObject(){}
};
class CCmdTarget:public CObject{
public:
	CCmdTarget() {}
	~CCmdTarget(){}

};
class CWinThread:public CCmdTarget{
public:
	CWinThread(){}
	~CWinThread(){}
	virtual bool InitInstance(){
		cout<<"CCmdTarget::InitInstance"<<endl;
		return true;
	}
	virtual int Run(){
		cout<<"CWinThread::Run \n";
		return 1;
	}
};
class CWinApp:public CWinThread{
public:
	CWinApp(){ m_pCurrentWinApp=this;}
	~CWinApp(){}
	virtual bool InitApplication(){
		cout<<"CWinApp::InitApplication"<<endl;
		return true;
	}
	virtual bool InitInstance(){
		cout<<"CWinApp::Inistance"<<endl;
		return true;
	}
	virtual int Run()
	{
		cout<<"CWinApp::Run\n";
		return CWinThread::Run();
	}
public:
	CWnd *m_pMainWnd; //pointer to the current main Window
	CWinApp* m_pCurrentWinApp;
};
class CWnd:public CCmdTarget{
public:
	CWnd(){}
	~CWnd(){}
	virtual bool Create(){ cout<<"CWnd::Create\n";
	 return true;
	}
	bool CreateEx(){
		cout<<"CWnd::CreateEx"<<endl;
		PreCreateWindow();
		return true;
	}
	virtual bool PreCreateWindow(){
		cout<<"CWnd::PreCreateWindow"<<endl;
		return true;
	}
};
class CView:public CWnd{
public:
	CView(){}
	~CView(){}
};
class CFrameWnd:public CWnd{
public:
	CFrameWnd(){
	}
	~CFrameWnd(){}
	virtual bool Create(){
		cout<<"CFrameWnd::Create"<<endl;
		CreateEx();
		return true;
	}
	virtual bool PreCreateWindow(){ cout<<"CFrameWnd::PreCreateWindow"<<endl; return true;}
};
class CDocument:public CCmdTarget
{
public:
	CDocument(){}
	~CDocument(){}
};

/**************************************
* global function
**************************************/
CWinApp* AfxGetApp();
#endif