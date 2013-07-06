#include<iostream>

/*********************************
* declaration
**********************************/
class CObject;
class CCmdTarget;
class CWinApp;
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
class CWinApp:public CCmdTarget{
public:
	CWinApp(){}
	~CWinApp(){}
};
class CWnd:public CCmdTarget{
public:
	CWnd(){}
	~CWnd(){}
};
class CView:public CWnd{
public:
	CView(){}
	~CView(){}
};
class CFrameWnd:public CWnd{
public:
	CFrameWnd(){}
	~CFrameWnd(){}
};
class CDocument:public CCmdTarget
{
public:
	CDocument(){}
	~CDocument(){}
};