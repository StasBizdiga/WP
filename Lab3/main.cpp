#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <commctrl.h>


#define IDM_DRAW_LINE 101
#define IDM_DRAW_RECT 102
#define IDM_DRAW_CIRC 103
#define IDM_DRAW_POLYLINE 104
#define IDM_DRAW_FREE 105

#define ID_FILE_EXIT 9001
#define ID_TOOL_COLOR_WHT 9005
#define ID_TOOL_COLOR_RED 9006
#define ID_TOOL_COLOR_GRN 9007
#define ID_TOOL_COLOR_BLU 9008
#define ID_TOOL_COLOR_BLK 9009
#define ID_TOOL_FILL 9010


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("Lab-3") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW;// | CS_OWNDC ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("Program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     hwnd = CreateWindow (szAppName, TEXT ("Lab-3"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

void DrawBezier (HDC hdc, POINT pt1[])
{
     PolyBezier (hdc, pt1, 4) ;

     MoveToEx (hdc, pt1[0].x, pt1[0].y, NULL) ;
     LineTo   (hdc, pt1[1].x, pt1[1].y) ;

     MoveToEx (hdc, pt1[2].x, pt1[2].y, NULL) ;
     LineTo   (hdc, pt1[3].x, pt1[3].y) ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static POINT pt1[4],pt2[4],mousePOS[2];
     HDC          hdc ;
     int          cxClient, cyClient ;
     static PAINTSTRUCT  ps ;
     static COLORREF     crColor;
     static HPEN hPen,hPenOld;

     static bool toFill = FALSE;
     static int drawTool = 0;
     static float width = 1;
     static HMENU hMenu, hSubMenu, hSubSub;

     switch (message)
     {


     case WM_CREATE:
         {

            /*Handling menu*/

            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

            hSubMenu = CreatePopupMenu();
            hSubSub = CreatePopupMenu();
            AppendMenu(hSubMenu,  MF_STRING , ID_TOOL_FILL, "&Fill");

            hSubSub = CreatePopupMenu();
            AppendMenu(hSubSub,  MF_STRING , ID_TOOL_COLOR_BLK, "&Black");
            AppendMenu(hSubSub,  MF_STRING , ID_TOOL_COLOR_RED, "&Red");
            AppendMenu(hSubSub,  MF_STRING , ID_TOOL_COLOR_GRN, "&Green");
            AppendMenu(hSubSub,  MF_STRING , ID_TOOL_COLOR_BLU, "&Blue");
            AppendMenu(hSubSub,  MF_STRING , ID_TOOL_COLOR_WHT, "&White / Eraser");
            AppendMenu(hSubMenu, MF_STRING | MF_POPUP, (UINT)hSubSub,"&Color");

            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Painting");

            hSubMenu = CreatePopupMenu();
            hSubSub = CreatePopupMenu();
            AppendMenu(hSubMenu,  MF_STRING , IDM_DRAW_LINE, "&Line");
            AppendMenu(hSubMenu,  MF_STRING , IDM_DRAW_RECT, "&Rectangle");
            AppendMenu(hSubMenu,  MF_STRING , IDM_DRAW_CIRC, "&Ellipse");
            AppendMenu(hSubMenu,  MF_STRING , IDM_DRAW_POLYLINE, "P&oly Line");
            AppendMenu(hSubMenu,  MF_STRING , IDM_DRAW_FREE, "&Pencil");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu,"&Drawing Tools");

            SetMenu(hwnd, hMenu);
     } break;

     case WM_SIZE:

          // BEZIER LINE 1
          //////////////////////////////
          cxClient = LOWORD (lParam) ;
          cyClient = HIWORD (lParam) ;
          pt1[0].x = cxClient / 8 ;
          pt1[0].y = cyClient / 8 ;

          pt1[1].x = cxClient / 4 ;
          pt1[1].y = cyClient / 16 ;

          pt1[2].x =     cxClient / 2 ;
          pt1[2].y = 3 * cyClient / 16 ;

          pt1[3].x = 3 * cxClient / 8 ;
          pt1[3].y =     cyClient / 16 ;

          // BEZIER LINE 2
          //////////////////////////////
          pt2[0].x = cxClient / 8 ;
          pt2[0].y = cyClient / 4 ;

          pt2[1].x = cxClient / 4 ;
          pt2[1].y = cyClient / 8 ;

          pt2[2].x =     cxClient / 2 ;
          pt2[2].y =     cyClient / 4 ;

          pt2[3].x =     cxClient / 2 ;
          pt2[3].y = 3 * cyClient / 8 ;

          return 0 ;



    case WM_LBUTTONDOWN:
        {
        mousePOS[0].x = LOWORD (lParam) ;
        mousePOS[0].y = HIWORD (lParam) ;
        }break;

	case WM_LBUTTONUP:
        if (drawTool==1)
        {
        hdc = GetDC(hwnd);
        hPen = CreatePen(PS_SOLID, width, crColor);
        SelectObject(hdc, hPen);

        MoveToEx(hdc, mousePOS[0].x, mousePOS[0].y, NULL);
        LineTo(hdc, mousePOS[1].x, mousePOS[1].y);

        DeleteObject(hPen);

        ReleaseDC(hwnd, hdc);

        }break;


	case WM_MOUSEMOVE:

        if (wParam & MK_LBUTTON )
          {

               if (wParam & MK_LBUTTON)
               {
                    mousePOS[1].x = LOWORD (lParam) ;
                    mousePOS[1].y = HIWORD (lParam) ;
               }
          }

		if(GetKeyState(VK_SHIFT)<0)
          {
           if ((wParam & MK_LBUTTON || wParam & MK_RBUTTON))
          {
               hdc = GetDC(hwnd);
               SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
               DrawBezier (hdc, pt1) ;

               if (wParam & MK_LBUTTON)
               {
                    pt1[1].x = LOWORD (lParam) ;
                    pt1[1].y = HIWORD (lParam) ;
               }

               if (wParam & MK_RBUTTON)
               {
                    pt1[2].x = LOWORD (lParam) ;
                    pt1[2].y = HIWORD (lParam) ;
               }

               SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
               DrawBezier (hdc, pt1) ;

               ReleaseDC(hwnd, hdc);
               }
          }

          else if(GetKeyState(VK_CONTROL)<0)
          {
            if ((wParam & MK_LBUTTON || wParam & MK_RBUTTON))
               {
               hdc = GetDC(hwnd);
               SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
               DrawBezier (hdc, pt2) ;

               if (wParam & MK_LBUTTON)
               {
                    pt2[1].x = LOWORD (lParam) ;
                    pt2[1].y = HIWORD (lParam) ;
               }

               if (wParam & MK_RBUTTON)
               {
                    pt2[2].x = LOWORD (lParam) ;
                    pt2[2].y = HIWORD (lParam) ;
               }

               SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
               DrawBezier (hdc, pt2) ;
               ReleaseDC(hwnd, hdc);
               }
          }

        return 0 ;



     case WM_KEYDOWN:
		switch(wParam)
		{
        case VK_ADD:
            if (width < 10){width += 1;}
            break;
        case VK_SUBTRACT:
            if (width >= 1) {width -= 1;}
            break;
        case VK_DELETE:
            break;
        case VK_SPACE:
            break;
		case VK_ESCAPE:
		    drawTool=0;
			break;

		default:
			break;
		}
		break;


     case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDM_DRAW_LINE:
            drawTool = 1;
            break;
        case IDM_DRAW_RECT:
            drawTool = 2;
            break;
        case IDM_DRAW_CIRC:
            drawTool = 3;
            break;
        case IDM_DRAW_POLYLINE:
            drawTool = 4;
            break;
        case IDM_DRAW_FREE:
            drawTool = 5;
            break;

        case ID_TOOL_COLOR_BLK:
            crColor = RGB(0,0,0);
            break;
        case ID_TOOL_COLOR_RED:
            crColor = RGB(255,0,0);
            break;
        case ID_TOOL_COLOR_BLU:
            crColor = RGB(0,0,255);
            break;
        case ID_TOOL_COLOR_GRN:
            crColor = RGB(0,255,0);
            break;
        case ID_TOOL_COLOR_WHT:
            crColor = RGB(255,255,255);
            break;


        case ID_TOOL_FILL:
            if(toFill){SelectObject(hdc, GetStockObject(GRAY_BRUSH));
            toFill = FALSE;}
            else {SelectObject(hdc, GetStockObject(NULL_BRUSH));
            toFill = TRUE;}
            break;

		case ID_FILE_EXIT:
			PostQuitMessage(WM_QUIT);
			break;

        };
        return 0;

     case WM_PAINT:
          InvalidateRect (hwnd, NULL, TRUE) ;

          hdc = BeginPaint (hwnd, &ps) ;

          DrawBezier (hdc, pt1) ;
          DrawBezier (hdc, pt2) ;

        /*
          Rectangle (hdc,     200 / 8,     400 / 8,
                     7 * 200 / 8, 7 * 400 / 8) ;

          Ellipse   (hdc,     1500 / 8,     800 / 8,
                     7 * 1500 / 8, 7 * 800 / 8) ;
          RoundRect (hdc,     100,     20 ,
                     400, 400 ,
                         200,     20) ;
*/

            SelectObject(hdc, hPenOld);
            DeleteObject(hPen);
          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
