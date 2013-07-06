#include"MFC.h"

/*****************************************
* declaration
******************************************/
class CMyWinApp;
class CMyView;
class CMyFrameWnd;
class CMyDoc;

/****************************************
* definition
*****************************************/
class CMyWinApp:public CWinApp{
public:
	CMyWinApp(){}
	~CMyWinApp(){}
};
class CMyView:public CView{
public:
	CMyView(){}
	~CMyView(){}
};
class CMyFrameWnd:public CFrameWnd{
public:
	CMyFrameWnd(){}
	~CMyFrameWnd(){}
};
class CMyDoc:public CDocument{
public:
	CMyDoc(){}
	~CMyDoc(){}
};