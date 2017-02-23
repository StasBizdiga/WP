#include <windows.h>
#define IDC_MAIN_BUTTON 101
#define IDC_MAIN_EDIT	102	// Edit box identifier
#define IDC_OUTPUT_TEXT 103
#define IDC_LAUGH_BUTTON 104

HWND hEdit;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowsProcedure (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
/*   Set the name for the application  */
     static TCHAR szAppName[] = TEXT ("Talker") ;

     HWND         hwnd ;      /* Handle for window */
     MSG          message ;   /* Store messages here */
     WNDCLASS     winclass ;  /* WindowClass data structure*/

     winclass.style         = CS_HREDRAW | CS_VREDRAW ;
     winclass.lpfnWndProc   = WindowsProcedure ;
     winclass.cbClsExtra    = 0 ;
     winclass.cbWndExtra    = 0 ;
     winclass.hInstance     = hInstance ;
     winclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     winclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     winclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     winclass.lpszMenuName  = NULL ;
     winclass.lpszClassName = szAppName ;


/*   If Registering window class fails, close app */
     if (!RegisterClass (&winclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

/*   Once class is registered, create the window*/
     hwnd = CreateWindow (szAppName,             // window class name
                          TEXT ("Talker"),        // window caption
                          WS_OVERLAPPEDWINDOW,   // window style
                          CW_USEDEFAULT,         // initial x position
                          CW_USEDEFAULT,         // initial y position
                          CW_USEDEFAULT,         // initial x size
                          CW_USEDEFAULT,         // initial y size
                          NULL,                  // parent window handle
                          NULL,                  // window menu handle
                          hInstance,             // program instance handle
                          NULL) ;                // creation parameters

/*   Make the window visible on the screen */
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

/*   Run the loop until no message is acquired */
     while (GetMessage (&message, NULL, 0, 0))
     {
          TranslateMessage (&message) ;  // Translate virtual-key to char message
          DispatchMessage (&message) ;   // Send message to windows procedure
     }
     return message.wParam ;
}


/*  The following function is called by DispatchMessage()  */
LRESULT CALLBACK WindowsProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
     HINSTANCE    hInst;
     HFONT textFont,hFontOld;

     switch (message)
     {
     case WM_CREATE:
         {
            /* Create title (output) text box */
            HWND hTitle = CreateWindowEx(
                (DWORD)NULL,
                TEXT("EDIT"),                                                   // The class name required is edit
                TEXT("Type a joke below:"),                                                       // Default text.
                WS_VISIBLE | WS_CHILD | ES_READONLY,
                50, 75,                                                         // the left and top co-ordinates
                200, 20,                                                       // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_OUTPUT_TEXT,                                         // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);

            /* Create a text edit box */
            hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"",
				WS_CHILD|WS_VISIBLE|
				ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL,
				50,     // x pos
				100,    // y pos
				200,    // x size
				100,    // y size
				hwnd,
				(HMENU)IDC_MAIN_EDIT,
				GetModuleHandle(NULL),
				NULL);
			HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
			SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
			SendMessage(hEdit,
				WM_SETTEXT,
				NULL,
				(LPARAM)"So... ");

         /* create push button1 */
         HWND hWndButton1=CreateWindowEx(NULL,
				"BUTTON",
				"Say it!",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,     //button x pos
				220,    //button y pos
				200,    //button width
				24,     // button height
				hwnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);
            SendMessage(hWndButton1,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

            /* create push button2 */
         HWND hWndButton2=CreateWindowEx(NULL,
				"BUTTON",
				"Laugh!",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,     //button x pos
				250,    //button y pos
				200,    //button width
				24,     // button height
				hwnd,
				(HMENU)IDC_LAUGH_BUTTON,
				GetModuleHandle(NULL),
				NULL);
            SendMessage(hWndButton2,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));
		}
		break;


    case WM_COMMAND:
			switch(LOWORD(wParam))
            {
				case IDC_MAIN_BUTTON:
				{
					char buffer[256];
					SendMessage(hEdit,
						WM_GETTEXT,
						sizeof(buffer)/sizeof(buffer[0]),
						reinterpret_cast<LPARAM>(buffer));
					MessageBox(NULL,
						buffer,
						"You joke:",
						MB_ICONINFORMATION);
				}
				break;

				case IDC_LAUGH_BUTTON:
				{
					MessageBox(NULL,
						TEXT ("Hahaha"),
						"You laugh:",
						MB_ICONINFORMATION);

				}
				break;
			}
			break;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          GetClientRect (hwnd, &rect) ;

          /*center text*/
          DrawText (hdc, TEXT ("Done with Pride and Prejudice by StasBizdiga!"), -1, &rect,
                    DT_SINGLELINE | DT_BOTTOM | DT_RIGHT) ;

          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}




