#pragma once
#include "stdafx.h"

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")

const double PI = 3.14159265358979323846;

struct EllipticalArc
{
    float cx;
    float cy;
    float theta1;
    float deltaTheta;
};

float angleBetweenVectors(float, float, float, float);
EllipticalArc createEllipticalArc(float, float, float, float, float, float, float, float, float);

class Draw 
{
private:
    static bool drew;
    static vector<GraphicsPath*> graphicsPaths;
    int curent_path;

public:
    // Constructor
    Draw();
    
    // Destructor
    ~Draw();
    
    // Transform the screen to draw shape at the exact position, scale and angle (rotate)
    void transform(Graphics&, Shape*);

    // Create Brush for filling gradient color
    LinearGradientBrush* createLinearGradient(LinearGradientSVG);
    PathGradientBrush* createRadialGradient(RadialGradientSVG);

    // Draw specific shape
    VOID DrawCircle(Graphics&, CircleSVG, Def);
    VOID DrawRectangle(Graphics&, RectangleSVG, Def);
    VOID DrawEllipse(Graphics&, EllipseSVG, Def);
    VOID DrawLine(Graphics&, LineSVG);
    VOID DrawText(Graphics&, TextSVG, Def);
    VOID DrawPolygon(Graphics&, PolygonSVG, Def);
    VOID DrawPath(Graphics&, PathSVG, Def);
    VOID DrawPolyline(Graphics&, PolylineSVG, Def);

    // Draw the shape read from SVG file
    void drawShape(Graphics&, vector<Shape*> shapesSVG, Def);

    // Set drew to avoid building paths' properties so many times
    static void setDrew(bool);
};
