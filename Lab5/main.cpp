#define _WIN32_WINNT 0x0500 // this helps with some weird ref bugs
#include <windows.h>
#include <commctrl.h>
#include <cmath>
#include "visual.h"
#include "object.h"
#define ID_TIMER  1

LRESULT CALLBACK WndProc   (HWND, UINT, WPARAM, LPARAM) ;
VOID    CALLBACK TimerProc (HWND, UINT, UINT,   DWORD ) ;
HINSTANCE hInst;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static char szAppName[] = "Lab-5" ;
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

     hwnd = CreateWindow (szAppName, "Lab-5",
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

///////////////////////////////////////////////////////////////////////////////
// global vars
///////////////////////////////////////////////////////////////////////////////

static int semaphorePeriod = 100; // period of time for a semaphore to stay green or red [this period is adjustable]

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    static int simulationSpeed ;
    int init = 1;

    switch (message)
    {

    case WM_CREATE:
        if (init){
            simulationSpeed = 20;
            SetTimer (hwnd, ID_TIMER, simulationSpeed, TimerProc) ;
            init = 0;
        }
        break;

    case WM_MOUSEWHEEL: // mouse handler for semaphore light switching speed

        if(GET_WHEEL_DELTA_WPARAM(wParam)>0 && semaphorePeriod < 200) {semaphorePeriod += 1; }
        if(GET_WHEEL_DELTA_WPARAM(wParam)<0 && semaphorePeriod > 10 ) {semaphorePeriod -= 1; }

        break;

    case WM_PAINT:
        hdc = GetDC (hwnd) ;

        DrawIntersection(hdc); // draws the streets and the city

        ReleaseDC (hwnd, hdc) ;
        break;


    case WM_DESTROY:
        KillTimer (hwnd, ID_TIMER) ;
        PostQuitMessage (0) ;
        break;
    }
    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

VOID CALLBACK TimerProc (HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{
    static bool is_vertical_flow_allowed = true;
    static int time = 0;
    HDC hdc = GetDC(hwnd);

    if (time >= semaphorePeriod) // flipping semaphore red/green when its period ends [this period is adjustable]
    {
        time=0;
        is_vertical_flow_allowed = !is_vertical_flow_allowed;
    }

    DrawTrafficLights(hdc,is_vertical_flow_allowed); // draws traffic interchangeable lights, for vertical/horizontal flow


    time += 1;
    ReleaseDC (hwnd, hdc);
}

