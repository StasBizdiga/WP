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

void DrawTrafficLights(HDC hdc, bool is_vertical_flow_allowed)
{
    SelectObject (hdc, GetStockObject (BLACK_PEN)) ;

    if (is_vertical_flow_allowed)
    {
        SelectObject (hdc, GetStockObject (WHITE_BRUSH)); // !feature! NEED GREEN BRUSH
        Rectangle(hdc, 290,310,300,320) ;  //SE (v>)
        Rectangle(hdc, 200,180,210,190) ;  //NW (^<)
        SelectObject (hdc, GetStockObject (BLACK_BRUSH)); // !feature! NEED RED BRUSH
        Rectangle(hdc, 310,200,320,210) ;  //NE (^>)
        Rectangle(hdc, 180,290,190,300) ;  //SW (v<)
    }
    else //then horizontal flow is allowed
    {
        SelectObject (hdc, GetStockObject (BLACK_BRUSH)); // !feature! NEED GREEN BRUSH
        Rectangle(hdc, 290,310,300,320) ;  //SE (v>)
        Rectangle(hdc, 200,180,210,190) ;  //NW (^<)
        SelectObject (hdc, GetStockObject (WHITE_BRUSH)); // !feature! NEED RED BRUSH
        Rectangle(hdc, 310,200,320,210) ;  //NE (^>)
        Rectangle(hdc, 180,290,190,300) ;  //SW (v<)
    }
    SelectObject (hdc, GetStockObject (NULL_BRUSH));
    return;
}
