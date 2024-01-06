#pragma once
#include "stdafx.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

const double PI = 3.14159265358979323846;

struct EllipticalArc
{
    float cx, cy, theta1, deltaTheta;
};

float angleBetweenVectors(float, float, float, float);
EllipticalArc createEllipticalArc(float, float, float, float, float, float, float, float, float);

class Draw {
private:
    static bool drew;
    static vector< GraphicsPath*> graphicsPaths;
    int curent_path;
public:
    Draw();
    ~Draw();
    
    void transform(Graphics&, Shape*);

    LinearGradientBrush* createLinearGradient(LinearGradientSVG);
    PathGradientBrush* createRadialGradient(RadialGradientSVG);

    void drawShape(Graphics&, vector<Shape*> shapesSVG, Def);

    VOID DrawCircle(Graphics&, CircleSVG, Def);
    VOID DrawRectangle(Graphics&, RectangleSVG, Def);
    VOID DrawEllipse(Graphics&, EllipseSVG, Def);
    VOID DrawLine(Graphics&, LineSVG);
    VOID DrawText(Graphics&, TextSVG, Def);
    VOID DrawPolygon(Graphics&, PolygonSVG, Def);
    VOID DrawPath(Graphics&, PathSVG, Def); 
    VOID DrawPolyline(Graphics&, PolylineSVG, Def);

    static void setDrew(bool);
};
