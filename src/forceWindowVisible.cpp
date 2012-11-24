/*
  forceWindowVisible  
      v1.0
                     All I changed was in the onSelChanged
                     force the window to change position and size
                     		SetWindowPos(hTargetWin,HWND_TOP,0,0,300,300,SWP_SHOWWINDOW);
		               also removed tooltip stuff to get it to compile under Dev-C++
      v1.1
       - Now uses the width of the window and height of the window instead of 300,300
       - uses the desktop dimensions if the window is too big
       - uses 300,300 if shift is pressed when toggling state
		
    forceWindowVisible based on               
    ShideWin 1.1
    Copyright (C) 2002-2005 Romain Vallet

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
    
    See the GNU General Public License details in copying.txt.
*/

#include <windows.h>
#include <commctrl.h>

#define WINDOW_TITLE "forceWindowVisible ShideWin 1.1 - %d windows - F1: Help"

HWND	    hMainWin, hListbox, hTooltip;
HINSTANCE	hThisInstance;
WNDPROC	    wpOrigListboxProc;
LPTOOLINFO  tiTooltipInfo = NULL;
UINT	    uiOldSelCount = 0;
UINT        uiLastTooltipIndex = 0;

// Set the tooltip text
VOID SetTooltipText (TCHAR *szText)
{
	RECT rect;
	TOOLINFO ti;
	
	GetClientRect (hListbox, &rect);
	
	// INITIALIZE MEMBERS OF THE TOOLINFO STRUCTURE
    ti.cbSize = sizeof(TOOLINFO);
    ti.uFlags = TTF_SUBCLASS;
    ti.hwnd = hListbox;
    ti.hinst = hThisInstance;
    ti.uId = 0;
    ti.lpszText = szText;
        // ToolTip control will cover the whole window
    ti.rect.left = rect.left;    
    ti.rect.top = rect.top;
    ti.rect.right = rect.right;
    ti.rect.bottom = rect.bottom;
	
	tiTooltipInfo = &ti;
	
    // SEND AN ADDTOOL MESSAGE TO THE TOOLTIP CONTROL WINDOW
    SendMessage(hTooltip, TTM_ADDTOOL, 0, (LPARAM) tiTooltipInfo);
}

// Create the tooltip window
VOID CreateTooltip ()
{
     /*
    INITCOMMONCONTROLSEX iccex; 
	
    // INITIALIZE COMMON CONTROLS
    iccex.dwICC = ICC_WIN95_CLASSES;
    iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    InitCommonControlsEx(&iccex);

    // CREATE A TOOLTIP WINDOW
    hTooltip = CreateWindowEx(WS_EX_TOPMOST,
        TOOLTIPS_CLASS,
        NULL,
        WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,		
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        hListbox,
        NULL,
        hThisInstance,
        NULL
        );

    SetWindowPos(hTooltip,
        HWND_TOPMOST,
        0,
        0,
        0,
        0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        */
}

// Callback procedure for the windows enumeration
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	UINT nIndex; 
	TCHAR szWindowText[256];
	
	if (!GetWindowText(hwnd, szWindowText, 256))
		wsprintf(szWindowText, "[Untitled window %d]", hwnd);
	nIndex = SendMessage(hListbox, LB_ADDSTRING, 0, LPARAM(szWindowText));
	SendMessage(hListbox, LB_SETITEMDATA, nIndex, LPARAM(hwnd));
	if (IsWindowVisible(hwnd))
		SendMessage(hListbox, LB_SETSEL, 1, nIndex);
	return TRUE;
}

// Fills the listbox with all the windows names
VOID FillList()
{
	SendMessage(hListbox, LB_RESETCONTENT, 0, 0);
	if (!EnumWindows(EnumWindowsProc, 0))
	{
		SendMessage(hListbox, LB_ADDSTRING, 0, LPARAM("Error while enumerating windows"));
		return;
	}
	uiOldSelCount = SendMessage(hListbox, LB_GETSELCOUNT, 0, 0);
	TCHAR szWindowText[1024];
	wsprintf(szWindowText, WINDOW_TITLE, SendMessage(hListbox, LB_GETCOUNT, 0, 0));
	SetWindowText(hMainWin, szWindowText);
}

// Display brief instructions in a message box
VOID DisplayHelp()
{
    TCHAR szHelpText[2048] = "forceWindowVisible v1.1\r\n"
    "Compendium Developments 2005\r\n"
    "www.compendiumdev.co.uk\r\n"
    "------------------------\r\n"
    "Enumerates all top-level windows\r\n"
    "and allows you to show or hide them.\r\n\r\n"
    "  F1:\tDisplays this dialog.\r\n"
    "  F5:\tRefreshes the list.\r\n"
    "  Esc:\tQuits the program.\r\n\r\n"
    "----------------------\r\n"
    "derived from ShideWin\r\n"
    "© 2002-2005 Romain Vallet\r\n"
    "http://wistinga.sourceforge.net/";

	MessageBox(hMainWin, szHelpText, "ShideWin Help", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
}

// Save the scrollbar and caret position and refill the listbox
VOID Refresh()
{
	UINT uiTopIndex, uiCaretIndex;
	uiTopIndex = SendMessage(hListbox, LB_GETTOPINDEX, 0, 0);
	uiCaretIndex = SendMessage(hListbox, LB_GETCARETINDEX, 0, 0);
	FillList();
	SendMessage(hListbox, LB_SETCARETINDEX, uiCaretIndex, 0);
	SendMessage(hListbox, LB_SETTOPINDEX, uiTopIndex, 0);
}

VOID Listbox_OnSelChange()
{
	UINT uiSelCount, uiItemIndex, uiSelected;
	HWND hTargetWin;
	
	// Check if the number of selected items has changed
	// (LBN_SELCHANGE also occurs when the caret position is changed)
	uiSelCount = SendMessage(hListbox, LB_GETSELCOUNT, 0, 0);
	if (uiSelCount == uiOldSelCount)
		return;
	uiOldSelCount = uiSelCount;
	
	// Check if the item is selected
	uiItemIndex = SendMessage(hListbox, LB_GETCARETINDEX, 0, 0);
	uiSelected = SendMessage(hListbox, LB_GETSEL, uiItemIndex, 0);
	if (uiSelected < 0)
		return;
	hTargetWin = (HWND)SendMessage(hListbox, LB_GETITEMDATA, uiItemIndex, 0);
	
	// Hide or show the window
	if (uiSelected){
		ShowWindow(hTargetWin, SW_SHOW);

        /* get the desktop sizes */
		RECT rDesktopWin;
		HWND hDesktopWin;
		hDesktopWin = GetDesktopWindow();
        GetWindowRect(hDesktopWin, &rDesktopWin);
        
        long lDesktopWidth=0;
        long lDesktopHeight=0;

        lDesktopWidth = rDesktopWin.right - rDesktopWin.left;
        lDesktopHeight = rDesktopWin.bottom - rDesktopWin.top; 	
                	
		/* 
           get the height and width of the window and use those 
           unless they fall off the edge of the desktop, in which case 
           use the desktop size
        */
        
        RECT r;
        long lWindowWidth = 0;
        long lWindowHeight = 0;
        
        GetWindowRect(hTargetWin, &r);	
        
        lWindowWidth = r.right-r.left;
        lWindowHeight = r.bottom-r.top;
        
        short sKeyState;
        sKeyState = GetKeyState(VK_SHIFT); /* get state of shift key */
        
        if (sKeyState & 0x80){
           /* shift was pressed, just use 300,300 */
           SetWindowPos(hTargetWin,HWND_TOP,0,0,300,300,SWP_SHOWWINDOW);
        }
        else{
                        
          if(lWindowWidth > lDesktopWidth){lWindowWidth = lDesktopWidth;}
          if(lWindowHeight > lDesktopHeight){lWindowHeight = lDesktopHeight;}
                
		  SetWindowPos(hTargetWin,HWND_TOP,0,0,lWindowWidth,lWindowHeight,SWP_SHOWWINDOW);
       }
    }
	else
		ShowWindow(hTargetWin, SW_HIDE);
	
	// Get the ShideWin window back to front
	SetForegroundWindow(hMainWin);
}

// Listbox MouseMove event handler
VOID Listbox_OnMouseMove(WPARAM wParam, LPARAM lParam)
{
     /*
	TCHAR szText[1024];
	UINT uiIndex;
	
	uiIndex = SendMessage(hListbox, LB_ITEMFROMPOINT, 0, lParam);
    
    // If the mouse hovers a different item, the tooltip is changed
    if (uiIndex != uiLastTooltipIndex)
    {
        SendMessage(hTooltip, WM_MOUSEMOVE, wParam, lParam);    // Hide the tooltip
        // Remove the tooltip info
        if (tiTooltipInfo != NULL)
            SendMessage(hTooltip, TTM_DELTOOL, 0, (LPARAM) tiTooltipInfo);
        //SendMessage(hListbox, LB_GETTEXT, uiIndex, LPARAM(szText));
        HWND hWnd = (HWND)SendMessage(hListbox, LB_GETITEMDATA, uiIndex, 0);
        RECT r;
        GetWindowRect(hWnd, &r);
        wsprintf(szText, "X:%d  Y:%d  Width:%d  Height:%d  Handle:%d",
            r.left, r.top,
            r.right-r.left, r.bottom-r.top,
            hWnd);
        SetTooltipText(szText);
    }
    
    uiLastTooltipIndex = uiIndex;
    */
}

// Main window Size event handler
VOID MainWin_OnSize()
{
	RECT rectMainWin;
	// Resize the listbox to the window client size
	GetClientRect(hMainWin, &rectMainWin);
	MoveWindow(hListbox,
		rectMainWin.top, rectMainWin.left,
		rectMainWin.right - rectMainWin.left, rectMainWin.bottom - rectMainWin.top,
		TRUE);
}

// Main window KeyDown event handler
VOID Listbox_OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case VK_ESCAPE:
			SendMessage(hMainWin, WM_DESTROY, 0, 0);
			break;
		case VK_F5:
			Refresh();
			break;
		case VK_F1:
			DisplayHelp();
			break;
	}
}
  

// Listbox procedure
LRESULT CALLBACK Listbox_WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
	{
		case WM_MOUSEMOVE:

			Listbox_OnMouseMove(wParam, lParam);
			break;
		case WM_KEYDOWN:
			Listbox_OnKeyDown(wParam, lParam);
    }
    return CallWindowProc(wpOrigListboxProc, hwnd, uiMsg, wParam, lParam); 
}

// Main window procedure
LRESULT CALLBACK ShideWin_WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
	{
		case WM_SIZE:
			MainWin_OnSize();
			break;
		case WM_KEYDOWN:
            SendMessage(hListbox, WM_SETFOCUS, 0, 0);
            SendMessage(hListbox, WM_KEYDOWN, wParam, lParam);
			//Listbox_OnKeyDown(wParam, lParam);
			break;
		case WM_COMMAND:
			if (HIWORD(wParam) == LBN_SELCHANGE)
				Listbox_OnSelChange();
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
    }

    return DefWindowProc(hwnd, uiMsg, wParam, lParam);
}


// Build the user interface
BOOL BuildUI()
{
	
	//-------------//
	// Main Window //
	//-------------//
	WNDCLASS wc;

    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = ShideWin_WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hThisInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "ShideWin";

    RegisterClass(&wc);

    hMainWin = CreateWindow(
        "ShideWin",                     // Class Name
        "ShideWin",                     // Title
        WS_OVERLAPPEDWINDOW,            // Style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Position
        300, 354,                       // Size
        NULL,                           // Parent
        NULL,                           // Use class menu
        hThisInstance,                          // Instance
        0);                             // No special parameters
	
	if (!hMainWin)
		return FALSE;

	
	//---------//
	// Listbox //
	//---------//
  	hListbox = CreateWindow(
		"LISTBOX",
		"lstHandle",
		WS_CHILD | LBS_HASSTRINGS | LBS_MULTIPLESEL | LBS_STANDARD |  LBS_NOINTEGRALHEIGHT,
		0, 0,
		150, 300,
		hMainWin,
		NULL,
		hThisInstance,
		0);
	
	if (!hListbox)
		return FALSE;
	
	wpOrigListboxProc = (WNDPROC) SetWindowLong(hListbox, GWL_WNDPROC, (LONG) Listbox_WndProc); 
/*
	HFONT hLstFont = CreateFont(13, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Tahoma");
	SendMessage(hListbox, WM_SETFONT, (UINT)hLstFont, 1);
*/	
  
	ShowWindow(hListbox, SW_NORMAL);
	ShowWindow(hMainWin, SW_NORMAL);
	
	CreateTooltip();
	
	return TRUE;
}


// Main procedure
INT WINAPI WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR pszCmdLine, INT nCmdShow)
{
	hThisInstance = hinst;
	BuildUI();
	FillList();
	SendMessage(hListbox, LB_SETCARETINDEX, 0, 0);
	SendMessage(hListbox, LB_SETTOPINDEX, 0, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
