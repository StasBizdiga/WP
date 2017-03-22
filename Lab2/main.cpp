#include <windows.h>

#define IDC_CENTER_BUTTON 101
#define IDC_MICRO_BUTTON  102

#define ID_FILE_EXIT 9001
#define ID_HELP 9002
#define ID_ABOUT 9003


HWND hEdit,hMood;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowsProcedure (HWND, UINT, WPARAM, LPARAM) ;

     HINSTANCE hInst;
     TCHAR szAppName[] = TEXT ("Lab-2") ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
/*   Set the name for the application  */

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

     hInst = hInstance;

/*   Once class is registered, create the window*/
     hwnd = CreateWindow (szAppName,             // window class name
                          TEXT ("Lab-2"),       // window caption
                          WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
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
     static HWND microButton,centeringButton;
     static HMENU hMenu;
     POINT point;

     switch (message)
     {

     case WM_CREATE:
         {

            /*Handling menu*/
            HMENU hMenu, hSubMenu;

            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, IDC_CENTER_BUTTON, "&Center");
            AppendMenu(hSubMenu, MF_STRING, IDC_MICRO_BUTTON, "&Micro");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Functions");

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_ABOUT, "&About");
            AppendMenu(hSubMenu, MF_STRING, ID_HELP, "&Help");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Info");

            SetMenu(hwnd, hMenu);

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


				/* create centering button 3 */
                centeringButton = CreateWindowEx(NULL,
				"BUTTON",
				"CENTER",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				(screenX - rect.right)/2,     //button x pos
				(screenY - rect.bottom)/2 - 50,     //button y pos
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

				/* create micro button 4 */
                microButton = CreateWindowEx(NULL,
				"BUTTON",
				"MICRO",
				WS_TABSTOP|WS_VISIBLE|
				WS_CHILD|BS_DEFPUSHBUTTON,
				(screenX - rect.right)/2,     //button x pos
				(screenY - rect.bottom)/2,     //button y pos
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
            {
                /* setting min/max window size */
                ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
                ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 150;
                //((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 800;
                //((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
            }
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
                        }
                        break;

				case IDC_MICRO_BUTTON:
				{
                        GetClientRect(hwnd, &rect);

                    SetWindowPos(
                        hwnd, 0,
                        0,
                        0,
                        200, 150,
                        SWP_NOMOVE | SWP_NOZORDER );

                        MessageBox(NULL,
						TEXT ("Do you like it?"),
						"Mini",
						MB_ICONQUESTION);
                        }
                        break;

                case ID_ABOUT:
                    {
                        MessageBox(NULL,
						TEXT ("About me or the program?"),
						"Tell me",
						MB_ICONQUESTION);
                    }
                        break;

                case ID_HELP:
                    {
                        MessageBox(NULL,
						TEXT ("Help me please."),
						"Help me",
						MB_ICONWARNING);
                    }
                        break;
                case ID_FILE_EXIT:
                        DestroyWindow(hwnd);
                        break;

                default:
                        return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;


     case WM_PAINT:
            hdc = BeginPaint (hwnd, &ps) ;

            GetClientRect (hwnd, &rect) ;

            /*center text*/
            DrawText (hdc, TEXT ("StasBizdiga 2017 (c)"), -1, &rect,
                    DT_SINGLELINE | DT_BOTTOM | DT_RIGHT) ;


            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent
            SetTextColor(hdc, RGB(0,0,200));                                                                   // Setting the text color

            DrawText(hdc, "\nLaboratory work #2", -1, &rect, DT_CENTER | DT_TOP);                              // Drawing the text on top aligning it to center

            textFont  = CreateFont(0, 0, 0, 0, FW_SEMIBOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, "Calibri");             // Creating the text font to semibold, italic, choosing Calibri font
            hFontOld  = (HFONT)SelectObject(hdc,textFont);                                                     // Setting the text font
            SetTextColor(hdc,RGB(50,255,50));                                                                  // Setting the text color
            SetBkMode(hdc, TRANSPARENT);                                                                       // Set the background to be transparent

            DrawText(hdc, "\n\n* * *", -1, &rect, DT_CENTER | DT_TOP);                                         // Drawing the text on top aligning it to center

            SetTextColor(hdc, RGB(0, 100, 0));                                                                 // Resetting the color to black


            EndPaint (hwnd, &ps) ;
            return 0 ;

    case WM_SIZE:

            break;

    case WM_VSCROLL:
            // LOWORD(wParam) determines the desired scrolling action.
            // CustomHandleVScroll(hwnd, LOWORD(wParam));
            break;

    case WM_DESTROY:
            PostQuitMessage (0) ;
            return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}




