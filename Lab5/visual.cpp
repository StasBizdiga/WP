#include "visual.h"

/* Here is the visual part of the project, all functions regarding displaying something on screen should be here */

void DrawIntersection(HDC hdc)
{
        // Drawing the intersection
        SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
        Rectangle(hdc, 100,100,200,200) ; // top left house
        Rectangle(hdc, 100,300,200,400) ; // top right house
        Rectangle(hdc, 300,100,400,200) ; // bottom left house
        Rectangle(hdc, 300,300,400,400) ; // bottom right house
        MoveToEx(hdc, 250,100,NULL);
        LineTo(hdc,250,200);              // top vertical line
        MoveToEx(hdc, 250,300,NULL);
        LineTo(hdc,250,400);              // bottom vertical line
        MoveToEx(hdc, 100,250,NULL);
        LineTo(hdc,200,250);              // left horizontal line
        MoveToEx(hdc, 300,250,NULL);
        LineTo(hdc,400,250);              // right horizontal line
    return;
}
