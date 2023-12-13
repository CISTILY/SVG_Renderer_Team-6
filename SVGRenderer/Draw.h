#pragma once
#include "stdafx.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


class Draw {
public:
    Draw();
    ~Draw();
    
    void transform(Graphics&, Shape*);
    VOID DrawCircle(Graphics&, CircleSVG);
    VOID DrawRectangle(Graphics&, RectangleSVG);
    VOID DrawEllipse(Graphics&, EllipseSVG);
    VOID DrawLine(Graphics&, LineSVG);
    VOID DrawText(Graphics&, TextSVG);
    VOID DrawPolygon(Graphics&, PolygonSVG);
    VOID DrawPath(Graphics&, PathSVG); 
    VOID DrawPolyline(Graphics&, PolylineSVG);
    void drawShape(Graphics&, vector<ShapeData>);
};