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
void printlpEntries(AFX_MSGMAP_ENTRY* lpEntry)
{
	struct{
		int classid;
		char* classname;
	} classinfo[]={
		CCmdTargetid,	"CCmdTarget",
		CWinThreadid,	"CWinThread",
		CWinAppid,		"CWinApp",
		CMyWinAppid,	"CMyWinApp",
		CWndid,			"CWnd",
		CFrameWndid,	"CFrameWnd",
		CMyFrameWndid,	"CMyFrameWnd",
		CViewid,		"CView",
		CMyViewid,		"CMyView",
		CDocumentid,	"CDocument",
		CMyDocid,		"CMyDoc",
		0,				" "
	};
	for (int i=0;classinfo[i].classid!=0;i++)
	{
		if(classinfo[i].classid==lpEntry->nID)
		{
			cout<<lpEntry->nID<<" ";
			cout<<classinfo[i].classname<<endl;
			break;
		}
	}
}
void MsgMapPrinting(AFX_MSGMAP* pMessageMap)
{
	for(;pMessageMap!=NULL;pMessageMap=pMessageMap->pBaseMessageMap)
	{
		AFX_MSGMAP_ENTRY* lpEntry=pMessageMap->lpEntries;
		printlpEntries(lpEntry);
	}
}
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
ON_COMMAND(CMyWinAppid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
ON_COMMAND(CMyFrameWndid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyDoc,CDocument)
ON_COMMAND(CMyDocid,0)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMyView,CView)
ON_COMMAND(CMyViewid,0)
END_MESSAGE_MAP()

int main(int argc,char* argv[])
{
	
	CWinApp* pApp=AfxGetApp();
	pApp->InitApplication();
	pApp->InitInstance();
	pApp->Run();

	CMyDoc* pMyDoc=new CMyDoc();
	CMyView* pMyView=new CMyView();
	CFrameWnd* pMyFrame=(CFrameWnd*)pApp->m_pMainWnd;

	AFX_MSGMAP* pMessageMap=pMyView->GetMessageMap();
	cout<<endl<<"CMyView Message Map: "<<endl;
	MsgMapPrinting(pMessageMap);
	pMessageMap=pApp->GetMessageMap();
	cout<<endl<<"CMyWinApp Message Map: "<<endl;
	MsgMapPrinting(pMessageMap);
	//PrintAllClasses();
	//CArchive ar;
	//ar<<"123";
}