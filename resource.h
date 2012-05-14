/*
 * these definitions are normally included in visual studio's precompiled
 * headers, dialog boxes were barfing until I figured out they have to be 
 * defined manually
 */
#ifndef IDC_STATIC
#define IDC_STATIC -1
#endif

#ifndef IDOK
#define IDOK 1
#endif

#ifndef IDCANCEL
#define IDCANCEL 2
#endif

//icons and graphical resource IDs
#define IDI_PROGICON 10

//modal dialog IDs
#define IDD_ABOUT 4001

//modeless dialogs
#define IDMD_STATUS 5001
#define IDC_PRESS 5002
#define IDC_OTHER 5003

//menu IDs
#define IDR_MYMENU 9000
#define ID_FILE_EXIT 9001
#define ID_STUFF_GO 9101
#define ID_HELP_ABOUT 9201
#define ID_DIALOG_SHOW 9301
#define ID_DIALOG_HIDE 9302