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
class CArchive;
struct CRuntimeClass;
struct AFX_CLASSINIT;
struct AFX_MSGMAP;
struct AFX_MSGMAP_ENTRY;
typedef void (CCmdTarget::*AFX_PMSG)(void);
/********************************
* enum
*********************************/
enum AfxSig{
	AfxSig_end=0,		//marks end of message map
	AfxSig_vv,
};
/********************************
* macro
********************************/
#define WM_COMMAND		0x0111
#define CObjectid		0xffff
#define CCmdTargetid	1
#define CWinThreadid	11
#define CWinAppid		111
#define CMyWinAppid		1111
#define CWndid			12
#define CFrameWndid		121
#define CMyFrameWndid	1211
#define CViewid			122
#define CMyViewid		1221
#define CDocumentid		13
#define CMyDocid		131
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
#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name)	\
	static CObject* _stdcall CreateObject();
#define IMPLEMENT_DYNCREATE(class_name,base_class_name) \
	CObject* _stdcall class_name::CreateObject() \
{ return new class_name; } \
	_IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,0xffff, \
	class_name::CreateObject)
#define DECLARE_SERIAL(class_name) \
	DECLARE_DYNCREATE(class_name) \
	friend CArchive& _stdcall operator>>(CArchive& ar,class_name* &pOb);
#define IMPLEMENT_SERIAL(class_name,base_class_name,wSchema) \
		CObject* _stdcall class_name::CreateObject() \
{ return new class_name; } \
		_IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,wSchema, \
			class_name::CreateObject) \
		CArchive& _stdcall operator>>(CArchive& ar,class_name* &pOb) \
{ pOb=(class_name*)ar.ReadObject(RUNTIME_CLASS(class_name)); \
	return ar; } 
#define DECLARE_MESSAGE_MAP() \
		static AFX_MSGMAP_ENTRY _messageEntries[]; \
		static AFX_MSGMAP messageMap; \
		virtual AFX_MSGMAP* GetMessageMap() const;
#define BEGIN_MESSAGE_MAP(theClass,baseClass) \
	AFX_MSGMAP* theClass::GetMessageMap() const \
{ return &theClass::messageMap; } \
	AFX_MSGMAP theClass::messageMap= \
{ &(baseClass::messageMap), \
	(AFX_MSGMAP_ENTRY*) &(theClass::_messageEntries) }; \
AFX_MSGMAP_ENTRY theClass::_messageEntries[] = \
{
//command
#define ON_COMMAND(id,memberFxn) \
	{ WM_COMMAND,0,(unsigned int)id,(unsigned int)id,AfxSig_vv,(AFX_PMSG)memberFxn },
#define END_MESSAGE_MAP() \
	{ 0,0,0,0,AfxSig_end,(AFX_PMSG)0} \
};
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
//message struct 
struct AFX_MSGMAP{
	AFX_MSGMAP* pBaseMessageMap;
	AFX_MSGMAP_ENTRY* lpEntries;
};

struct AFX_MSGMAP_ENTRY
{
	unsigned int nMessage;	//windows message
	unsigned int nCode;		//control code or WM_NOTIFY code
	unsigned int nID;		//control ID( or 0 for windows message)
	unsigned int nLastID;	//used for entries specifying a range of control id's
	unsigned int nSig;		//signature type (action) or pointer to message #
	AFX_PMSG pfn;			//routine to call ( or special value)
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

	DECLARE_MESSAGE_MAP()
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
	DECLARE_MESSAGE_MAP()
};
class CWnd:public CCmdTarget{
	DECLARE_DYNCREATE(CWnd)
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
	DECLARE_MESSAGE_MAP()
};
class CView:public CWnd{
	DECLARE_DYNAMIC(CView)
public:
	CView(){}
	~CView(){}
	DECLARE_MESSAGE_MAP()
};
class CFrameWnd:public CWnd{
	DECLARE_DYNCREATE(CFrameWnd)
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
	DECLARE_MESSAGE_MAP()
};
class CDocument:public CCmdTarget
{
	DECLARE_DYNAMIC(CDocument)
	DECLARE_MESSAGE_MAP()
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
class CArchive{

private:
	//	istream m_input;
	//	ostream m_output;
public:
	template<class T> 
	CArchive& operator>>(T& t)
	{
		cout<<"read in "<<t<<endl;
		return *this;
	}
	template<class T>
	CArchive& operator<<(const T& t)
	{
		cout<<"write out "<<t<<endl;
		return *this;
	}
	CObject* ReadObject( const CRuntimeClass *pClass);

};
/**************************************
* global function
**************************************/
CWinApp* AfxGetApp();

#endif