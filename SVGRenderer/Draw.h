#pragma once
#include "stdafx.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


class Draw {
private:
    static bool drew;
    static vector< GraphicsPath*> graphicsPaths;
    int curent_path;
public:
    Draw();
    ~Draw();
    
    void transform(Graphics&, Shape*);

    void drawShape(Graphics&, vector<Shape*> shapesSVG);

    VOID DrawCircle(Graphics&, CircleSVG);
    VOID DrawRectangle(Graphics&, RectangleSVG);
    VOID DrawEllipse(Graphics&, EllipseSVG);
    VOID DrawLine(Graphics&, LineSVG);
    VOID DrawText(Graphics&, TextSVG);
    VOID DrawPolygon(Graphics&, PolygonSVG);
    VOID DrawPath(Graphics&, PathSVG); 
    VOID DrawPolyline(Graphics&, PolylineSVG);

    static void setDrew(bool);
};
