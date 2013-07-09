#include"MFC.h"
using namespace std;
#ifndef _MY_H_
#define _MY_H_
/*****************************************
* declaration
******************************************/
class CMyWinApp;
class CMyView;
class CMyFrameWnd;
class CMyDoc;
/****************************************
* global function
****************************************/
void PrintAllClasses();
void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry);
void MsgMapPrinting(AFX_MSGMAP* pMessageMap);
/****************************************
* definition
*****************************************/
class CMyWinApp:public CWinApp{
public:
	CMyWinApp(){}
	~CMyWinApp(){}
	bool InitInstance();
	DECLARE_MESSAGE_MAP()
};
class CMyView:public CView{
	DECLARE_DYNCREATE(CMyView)
public:
	CMyView(){}
	~CMyView(){}
	DECLARE_MESSAGE_MAP()
};
class CMyFrameWnd:public CFrameWnd{
	DECLARE_DYNCREATE(CMyFrameWnd)
public:
	CMyFrameWnd();
	virtual	~CMyFrameWnd(){}
	DECLARE_MESSAGE_MAP()
};
class CMyDoc:public CDocument{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CMyDoc(){}
	~CMyDoc(){}
	DECLARE_MESSAGE_MAP()
};

#endif