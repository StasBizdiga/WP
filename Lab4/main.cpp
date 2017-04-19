#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <commctrl.h>

#define ID_TIMER    1

LRESULT CALLBACK WndProc   (HWND, UINT, WPARAM, LPARAM) ;
VOID    CALLBACK TimerProc (HWND, UINT, UINT,   DWORD ) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static char szAppName[] = "Lab-4" ;
     HWND        hwnd ;
     MSG         msg ;
     WNDCLASS    wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
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

     hwnd = CreateWindow (szAppName, "Lab-4",
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

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static int animSpeed ;
     int init = 1;

     switch (message)
     {
     case WM_CREATE:


          if (init){
          animSpeed = 20;
          SetTimer (hwnd, ID_TIMER, animSpeed, TimerProc) ;
          init = 0;
          }
          return 0 ;


     case WM_MOUSEWHEEL:
        { if(GET_WHEEL_DELTA_WPARAM(wParam)>0 && animSpeed < 500) {animSpeed += 1; }
          if(GET_WHEEL_DELTA_WPARAM(wParam)<0 && animSpeed > 20 ) {animSpeed -= 1; }
          SetTimer (hwnd, ID_TIMER, animSpeed, TimerProc) ;
          return 0;
        }

     case WM_ERASEBKGND:
     return 1;

     case WM_DESTROY:
          KillTimer (hwnd, ID_TIMER) ;
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

VOID CALLBACK TimerProc (HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
     HDC         hdc ;
     static POINT pt[2];
     static int animState = 0;
     static int animSlidesNum = 20;
     static int step = 5;


     hdc = GetDC (hwnd) ;

                if (animState>=animSlidesNum){animState=0;
                    step = -step;}
                else if (animState==animSlidesNum/2){step = -step;}
                if (animState==0) //looping animation
                {
                   animState=0;
                    pt[0].x = 100;
                    pt[0].y = 100;
                    pt[1].x = 125;
                    pt[1].y = 125;
                }
// clear
               SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
               Rectangle(hdc, pt[0].x+600,pt[0].y,pt[1].x+600,pt[1].y) ;
               RoundRect(hdc, pt[0].x+200,pt[0].y,pt[1].x+200,pt[1].y+150,100,100) ;
               Ellipse(hdc, pt[0].x+400,pt[0].y,pt[1].x+400,pt[1].y) ;
               Pie(hdc, pt[0].x+400,pt[0].y+200,pt[1].x+400,pt[1].y+200, 0,pt[0].y*100,pt[1].x*100,pt[1].y*100) ;
               Polygon(hdc,pt,5);


               animState += 1;
                    pt[0].x -= step;
                    pt[0].y -= step;
                    pt[1].x += step;
                    pt[1].y += step;
// draw
               SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
               Rectangle(hdc, pt[0].x+600,pt[0].y,pt[1].x+600,pt[1].y) ;
               RoundRect(hdc, pt[0].x+200,pt[0].y,pt[1].x+200,pt[1].y+150,100,100) ;
               Ellipse(hdc, pt[0].x+400,pt[0].y,pt[1].x+400,pt[1].y) ;
               Pie(hdc, pt[0].x+400,pt[0].y+200,pt[1].x+400,pt[1].y+200, 0,pt[0].y*100,pt[1].x*100,pt[1].y*100) ;
               Polygon(hdc,pt,5);

     ReleaseDC (hwnd, hdc) ;
}

