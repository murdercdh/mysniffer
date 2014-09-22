; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMysnifferView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mysniffer.h"
ODLFile=mysniffer.odl
LastPage=0

ClassCount=9
Class1=CMysnifferApp
Class2=CMysnifferDoc
Class3=CMysnifferView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_PROPPAGE_EDIT
Resource2=CG_IDD_MYDIALOGBAR
Class5=CAboutDlg
Resource3=IDD_PROPPAGE_INTERFACE
Class6=CMyProPage1
Class7=CMyProPage2
Class8=CMyProSheet
Resource4=IDR_MAINFRAME
Resource5=IDD_ABOUTBOX
Resource6=IDD_DIALOGBAR (English (U.S.))
Class9=CDlgStat
Resource7=IDD_DIALOG1

[CLS:CMysnifferApp]
Type=0
HeaderFile=mysniffer.h
ImplementationFile=mysniffer.cpp
Filter=N

[CLS:CMysnifferDoc]
Type=0
HeaderFile=mysnifferDoc.h
ImplementationFile=mysnifferDoc.cpp
Filter=N
LastObject=CMysnifferDoc

[CLS:CMysnifferView]
Type=0
HeaderFile=mysnifferView.h
ImplementationFile=mysnifferView.cpp
Filter=C
LastObject=CMysnifferView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=mysniffer.cpp
ImplementationFile=mysniffer.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_STATUS_BAR
Command15=ID_WINDOW_SPLIT
Command16=ID_MYSET_SHEET
Command17=ID_SAVE_TO_FILE
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:CG_IDD_MYDIALOGBAR]
Type=1
Class=CMainFrame
ControlCount=5
Control1=IDC_STATIC_NAME,static,1342308352
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDC_BUTTON_SCAN,button,1342242816
Control4=IDC_BUTTON_STOP,button,1342242816
Control5=IDC_STATIC_IP,static,1342308352

[CLS:CMyProPage2]
Type=0
HeaderFile=mypropage.h
ImplementationFile=mypropage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CMyProPage2
VirtualFilter=idWC

[CLS:CMyProPage1]
Type=0
HeaderFile=mypropage.h
ImplementationFile=mypropage.cpp
BaseClass=CPropertyPage
LastObject=CMyProPage1
Filter=D
VirtualFilter=idWC

[CLS:CMyProSheet]
Type=0
HeaderFile=mypropage.h
ImplementationFile=mypropage.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CMyProSheet

[DLG:IDD_PROPPAGE_EDIT]
Type=1
Class=CMyProPage1
ControlCount=7
Control1=IDC_CHECK_ADDRESS,button,1342242819
Control2=IDC_CHECK_ASCII,button,1342242819
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DATAFORMAT1,button,1342308361
Control6=IDC_DATAFORMAT2,button,1342177289
Control7=IDC_DATAFORMAT3,button,1342177289

[DLG:IDD_PROPPAGE_INTERFACE]
Type=1
Class=CMyProPage2
ControlCount=12
Control1=IDC_EDIT_PACKETLIMIT,edit,1350633600
Control2=IDC_SPIN_PACKETLIMIT,msctls_updown32,1342242839
Control3=IDC_CHECK_INTERFACE,button,1342242819
Control4=IDC_EDIT_STOPTIME,edit,1350633600
Control5=IDC_SPIN_STOPTIME,msctls_updown32,1342242839
Control6=IDC_EDIT_THREADNUM,edit,1350631552
Control7=IDC_EDIT_PL,edit,1350633600
Control8=IDC_SPIN_PL,msctls_updown32,1342242839
Control9=IDC_STATIC,static,1342308353
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG1]
Type=1
Class=CDlgStat
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PROGRESS1,msctls_progress32,1350565888
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_EDIT2,edit,1350631552

[CLS:CDlgStat]
Type=0
HeaderFile=DlgStat.h
ImplementationFile=DlgStat.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgStat

