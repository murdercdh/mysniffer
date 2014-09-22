// mysnifferDoc.cpp : implementation of the CMysnifferDoc class
//

#include "stdafx.h"
#include "mysniffer.h"

#include "mysnifferDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysnifferDoc

IMPLEMENT_DYNCREATE(CMysnifferDoc, CDocument)

BEGIN_MESSAGE_MAP(CMysnifferDoc, CDocument)
	//{{AFX_MSG_MAP(CMysnifferDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMysnifferDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CMysnifferDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IMysniffer to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {2E84B7D2-5F3D-49D2-82AA-81A4B49B1661}
static const IID IID_IMysniffer =
{ 0x2e84b7d2, 0x5f3d, 0x49d2, { 0x82, 0xaa, 0x81, 0xa4, 0xb4, 0x9b, 0x16, 0x61 } };

BEGIN_INTERFACE_MAP(CMysnifferDoc, CDocument)
	INTERFACE_PART(CMysnifferDoc, IID_IMysniffer, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysnifferDoc construction/destruction

CMysnifferDoc::CMysnifferDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CMysnifferDoc::~CMysnifferDoc()
{
	AfxOleUnlockApp();
}

BOOL CMysnifferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMysnifferDoc serialization

void CMysnifferDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMysnifferDoc diagnostics

#ifdef _DEBUG
void CMysnifferDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMysnifferDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMysnifferDoc commands
