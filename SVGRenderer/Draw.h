#pragma once
#include "stdafx.h"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <shellapi.h>
#include <locale>
#include <cmath>
#include <codecvt>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")




class Draw {
private:
    Point2D translate, scalePoint;
    float rotateAngle;
    int TranslateRotateScale[3];
public:
    Draw();
    ~Draw();
    void findOrderTransform(string);
    void splitString(string);
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