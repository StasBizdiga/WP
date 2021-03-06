#include <windows.h>

#define IDC_MAIN_EDIT	  102	// Edit box identifier
#define IDC_OUTPUT_TEXT   103
#define IDC_OUTPUT_MOOD   104
#define IDC_LAUGH_BUTTON  105
#define IDC_MAIN_BUTTON   106
#define IDC_CENTER_BUTTON 107
#define IDC_MICRO_BUTTON  108

HWND hEdit,hMood;
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
                          TEXT ("Talker"),       // window caption
                          WS_OVERLAPPEDWINDOW,   // window style
                          CW_USEDEFAULT,         // initial x position
                          CW_USEDEFAULT,         // initial y position
                          800,                   // initial x size
                          400,                   // initial y size
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
     HINSTANCE   hInst;
     HGDIOBJ hfDefault=GetStockObject(DEFAULT_GUI_FONT);
     HFONT       textFont,hFontOld;
	 int         screenX;                                                                                                                 //characters ave width of string
     int         screenY;


     switch (message)
     {

     case WM_CREATE:
         {
            /*Get height and width of screen*/
            screenX = GetSystemMetrics(SM_CXSCREEN);
            screenY = GetSystemMetrics(SM_CYSCREEN);

            /*Center window based on height and width of screen*/
            GetClientRect(hwnd, &rect);
            SetWindowPos(
                    hwnd, 0,
                    (screenX - rect.right)/2,
                    (screenY - rect.bottom)/2,
                    0, 0,
					SWP_NOZORDER|SWP_NOSIZE);



                /* Create title text box */
                HWND hTitle = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("EDIT"),                                                   // The class name required is edit
                TEXT("Type a joke below:"),                                                       // Default text.
                WS_VISIBLE | WS_CHILD | ES_READONLY,
                50, 75,                                                         // the left and top co-ordinates
                200, 20,                                                       // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_OUTPUT_TEXT,                                         // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);

                /* Create another title text box */
                HWND hTitleMood = CreateWindowEx(
                (DWORD)WS_EX_DLGMODALFRAME,
                TEXT("EDIT"),                                                   // The class name required is edit
                TEXT("C o m p u t e r   r e a c t i o n"),                                                       // Default text.
                WS_VISIBLE | WS_CHILD | ES_READONLY,
                300, 75,                                                         // the left and top co-ordinates
                200, 20,                                                       // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_OUTPUT_TEXT,                                         // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);

                /* Create reaction text box */
                hMood = CreateWindowEx(
                (DWORD)NULL,
                TEXT("EDIT"),                                                   // The class name required is edit
                "",                                                       // Default text.
                WS_VISIBLE | WS_CHILD | ES_READONLY | WS_BORDER,
                300, 100,                                                         // the left and top co-ordinates
                200, 100,                                                       // width and height
                hwnd,                                                           // parent window handle
                (HMENU)IDC_OUTPUT_MOOD,                                         // the ID of your editbox
                hInst,                                                          // the instance of your application
                NULL);

				/* Create a text edit box */
                hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,
				"EDIT",
				"So...",
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
                hfDefault;
                SendMessage(hEdit,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));



                /* create push button 1 */
                HWND sayButton = CreateWindowEx(NULL,
				"BUTTON",
				"Say it!",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,     //button x pos
				220,    //button y pos
				200,    //button width
				25,     // button height
				hwnd,
				(HMENU)IDC_MAIN_BUTTON,
				GetModuleHandle(NULL),
				NULL);
                SendMessage(sayButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

                /* create push button 2 */
                HWND laughButton = CreateWindowEx(NULL,
				"BUTTON",
				"Laugh!",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				50,     //button x pos
				250,    //button y pos
				200,    //button width
				25,     // button height
				hwnd,
				(HMENU)IDC_LAUGH_BUTTON,
				GetModuleHandle(NULL),
				NULL);
                SendMessage(laughButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

				/* create centering button 3 */
                HWND centeringButton = CreateWindowEx(NULL,
				"BUTTON",
				"CENTER",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				300,     //button x pos
				220,     //button y pos
				200,     //button width
				25,     // button height
				hwnd,
				(HMENU)IDC_CENTER_BUTTON,
				GetModuleHandle(NULL),
				NULL);
                SendMessage(centeringButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

				/* create coloring button 4 */
                HWND microButton = CreateWindowEx(NULL,
				"BUTTON",
				"MICRO",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				300,     //button x pos
				250,     //button y pos
				200,     //button width
				25,     // button height
				hwnd,
				(HMENU)IDC_MICRO_BUTTON,
				GetModuleHandle(NULL),
				NULL);
                SendMessage(microButton,
				WM_SETFONT,
				(WPARAM)hfDefault,
				MAKELPARAM(FALSE,0));

		}
		break;

    case WM_GETMINMAXINFO:

                /* setting min/max window size */
                ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 550;
                ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 375;
                ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 825;
                ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 550;

            break;


    case WM_COMMAND:
			switch(LOWORD(wParam))
            {
                case IDC_CENTER_BUTTON:
                    {
                        screenX = GetSystemMetrics(SM_CXSCREEN);
                        screenY = GetSystemMetrics(SM_CYSCREEN);

                        GetClientRect(hwnd, &rect);
                        SetWindowPos(
                        hwnd, 0,
                        (screenX/2 - rect.right/2),
                        (screenY/2 - rect.bottom/2),
                        0, 0,
                        SWP_NOZORDER|SWP_NOSIZE);

                        /* cpu reaction */
                        SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)" (^_^)  Perfect.");


				        MessageBox(NULL,
						TEXT ("Centered"),
						"Did you notice?",
						MB_ICONQUESTION);
				    }
                break;

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

                    int i = rand()%5; //randomize
                    switch(i){
                    /* cpu reaction */
                    case 0: {SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)"  (O_o)  Wut..");}break;
                    case 1: {SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)"  :] Got one more?");}break;
                    case 2: {SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)"  :0 Whoa really?..");}break;
                    case 3: {SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)"  :3 Fancy !");}break;
                    case 4: {SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)"  :( Aargh! No, more..");}break;
                    }
				}
				break;

				case IDC_LAUGH_BUTTON:
				{
					MessageBox(NULL,
						TEXT ("Hahaha"),
						"You laugh:",
						MB_ICONWARNING);

                    /* cpu reaction */
                    SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)"  :D !!!  Funny!");


				}
				break;

				case IDC_MICRO_BUTTON:
				{
					MessageBox(NULL,
						TEXT ("You'll love it"),
						"It's mini",
						MB_ICONWARNING);

                        GetClientRect(hwnd, &rect);

                    SetWindowPos(
                        hwnd, 0,
                        0,
                        0,
                        550, 375,
                        SWP_NOMOVE | SWP_NOZORDER );

                    /* cpu reaction */
                    SendMessage(hMood, WM_SETTEXT, 0, (LPARAM)" :O !!  wow !!");}break;


			}
			break;

     case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;

            GetClientRect (hwnd, &rect) ;

            /*center text*/
            DrawText (hdc, TEXT ("Done with Pride and Prejudice by StasBizdiga!"), -1, &rect,
                    DT_SINGLELINE | DT_BOTTOM | DT_RIGHT) ;


            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent
            SetTextColor(hdc, RGB(0,200,0));                                                                   // Setting the text color

            DrawText(hdc, "\nLet's Have Some Fun", -1, &rect, DT_CENTER | DT_TOP);                             // Drawing the text on top aligning it to center

            textFont  = CreateFont(0, 0, 0, 0, FW_SEMIBOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Calibri");             // Creating the text font to semibold, italic, choosing Calibri font
            hFontOld  = (HFONT)SelectObject(hdc,textFont);                                                     // Setting the text font
            SetTextColor(hdc,RGB(200,10,10));                                                                  // Setting the text color
            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent

            DrawText(hdc, "\n\nTesting your joking skills", -1, &rect, DT_CENTER | DT_TOP);                    // Drawing the text on top aligning it to center

            SetTextColor(hdc, RGB(0, 100, 0));                                                                 // Resetting the color to black


            EndPaint (hwnd, &ps) ;
            return 0 ;


    case WM_DESTROY:
            PostQuitMessage (0) ;
            return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}




