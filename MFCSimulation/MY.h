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
/****************************************
* definition
*****************************************/
class CMyWinApp:public CWinApp{
public:
	CMyWinApp(){}
	~CMyWinApp(){}
	bool InitInstance();
};
class CMyView:public CView{
public:
	CMyView(){}
	~CMyView(){}
};
class CMyFrameWnd:public CFrameWnd{
public:
	CMyFrameWnd();
	virtual	~CMyFrameWnd(){}
};
class CMyDoc:public CDocument{
public:
	CMyDoc(){}
	~CMyDoc(){}
};

#endif