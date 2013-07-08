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
struct CRuntimeClass;
struct AFX_CLASSINIT;/********************************
* macro
********************************/
#define DECLARE_DYNAMIC(class_name) \
	public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass * GetRuntimeClass() const;
#define RUNTIME_CLASS(class_name) \
	(&class_name::class##class_name)
#define _IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,wSchema,pfnNew) \
	static char _lpsz##class_name[]=#class_name; \
	CRuntimeClass class_name::class##class_name={ \
	_lpsz##class_name,sizeof(class_name),wSchema,pfnNew, \
RUNTIME_CLASS(base_class_name),NULL}; \
	static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
	CRuntimeClass * class_name::GetRuntimeClass() const \
{ return &class_name::class##class_name; } 
#define IMPLEMENT_DYNAMIC(class_name,base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,0xffff,NULL)
/********************************
* definition
*********************************/
//Runtime Class to record the type of each class
struct CRuntimeClass{
	char *m_lpszClassName;	//class name
	int m_nObjectSize;		//class size
	unsigned int m_wSchema;	//schema number
	CObject* (_stdcall* m_pfnCreateObject)();//pointer to class create function, null equals to abstract class
	CRuntimeClass *m_pBaseClass;	//Base Class
	static CRuntimeClass* pFirstClass;// start of the class list
	CRuntimeClass* m_pNextClass;	//linked to the next class
};
class CObject{
public:
	static CRuntimeClass classCObject;
	virtual CRuntimeClass* GetRuntimeClass() const;
public:
	CObject(){}
	~CObject(){}
public:
	bool IsKindOf(const CRuntimeClass* pClass) const;
};
class CCmdTarget:public CObject{
	DECLARE_DYNAMIC(CCmdTarget)
public:
	CCmdTarget() {}
	~CCmdTarget(){}

};
class CWinThread:public CCmdTarget{
	DECLARE_DYNAMIC(CWinThread)
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
	DECLARE_DYNAMIC(CWinApp)
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
	DECLARE_DYNAMIC(CWnd)
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
	DECLARE_DYNAMIC(CView)
public:
	CView(){}
	~CView(){}
};
class CFrameWnd:public CWnd{
	DECLARE_DYNAMIC(CFrameWnd)
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
	DECLARE_DYNAMIC(CDocument)
public:
	CDocument(){}
	~CDocument(){}
};
struct AFX_CLASSINIT{
	AFX_CLASSINIT(CRuntimeClass * pNewClass)
	{
		pNewClass->m_pNextClass=CRuntimeClass::pFirstClass;
		CRuntimeClass::pFirstClass=pNewClass;
	}
};
/**************************************
* global function
**************************************/
CWinApp* AfxGetApp();

#endif