#pragma once
#include "stdafx.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

const double PI = 3.14159265359;

struct EllipticalArc
{
	double x1, y1, rx, ry, phi, fA, fS, x2, y2;
};

struct CenterParameterization
{
	double cx, cy, theta1, deltaTheta;
};

double angleBetweenVectors(double, double, double, double);
CenterParameterization convertEndpoint2Center(EllipticalArc&);
Point* creatPoint(EllipticalArc&);

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
    VOID DrawPolygon(Graphics&, PolygonSVG);
    VOID DrawPath(Graphics&, PathSVG, Def); 
    VOID DrawPolyline(Graphics&, PolylineSVG);

    static void setDrew(bool);
};
