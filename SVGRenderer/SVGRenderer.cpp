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
#include "Renderer.h"
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID DrawCircle(Graphics& graphics, CircleSVG circle)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < circle.getTransform().size(); ++i) {
        findOrderTransform(circle.getTransform()[i]);
        splitString(circle.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    Rect rect(circle.getCoordinateX() - circle.getRadiusX(), circle.getCoordinateY() - circle.getRadiusX(), 2 * circle.getRadiusX(), 2 * circle.getRadiusX());

    SolidBrush brush(Color(round(255 * circle.getFillOpacity()), circle.getFill().getRed(), circle.getFill().getGreen(), circle.getFill().getBlue()));
    graphics.FillEllipse(&brush, rect);

    Pen pen(Color(round(255 * circle.getStrokeOpacity()), circle.getStroke().getRed(), circle.getStroke().getGreen(), circle.getStroke().getBlue()), circle.getStrokeWidth());
    graphics.DrawEllipse(&pen, rect);
    graphics.Restore(origin);
}

VOID DrawRectangle(Graphics& graphics, RectangleSVG rect)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < rect.getTransform().size(); ++i) {
        findOrderTransform(rect.getTransform()[i]);
        splitString(rect.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    Rect rectangle(rect.getCoordinateX(), rect.getCoordinateY(), rect.getWidth(), rect.getHeight());

    SolidBrush brush(Color(round(255 * rect.getFillOpacity()), rect.getFill().getRed(), rect.getFill().getGreen(), rect.getFill().getBlue()));
    graphics.FillRectangle(&brush, rectangle);

    Pen pen(Color(round(255 * rect.getStrokeOpacity()), rect.getStroke().getRed(), rect.getStroke().getGreen(), rect.getStroke().getBlue()), rect.getStrokeWidth());
    graphics.DrawRectangle(&pen, rectangle);

    graphics.Restore(origin);
}

VOID DrawEllipse(Graphics& graphics, EllipseSVG ellip)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < ellip.getTransform().size(); ++i) {
        findOrderTransform(ellip.getTransform()[i]);
        splitString(ellip.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    Rect rect(ellip.getCoordinateX() - ellip.getRadiusX(), ellip.getCoordinateY() - ellip.getRadiusY(), 2 * ellip.getRadiusX(), 2 * ellip.getRadiusY());

    SolidBrush brush(Color(round(255 * ellip.getFillOpacity()), ellip.getFill().getRed(), ellip.getFill().getGreen(), ellip.getFill().getBlue()));
    graphics.FillEllipse(&brush, rect);

    Pen pen(Color(round(255 * ellip.getStrokeOpacity()), ellip.getStroke().getRed(), ellip.getStroke().getGreen(), ellip.getStroke().getBlue()), ellip.getStrokeWidth());
    graphics.DrawEllipse(&pen, rect);
    graphics.Restore(origin);
}

VOID DrawLine(Graphics& graphics, LineSVG line)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < line.getTransform().size(); ++i) {
        findOrderTransform(line.getTransform()[i]);
        splitString(line.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    Pen pen(Color(round(255 * line.getStrokeOpacity()), line.getStroke().getRed(), line.getStroke().getGreen(), line.getStroke().getBlue()), line.getStrokeWidth());
    graphics.DrawLine(&pen, line.getCoordinateX(), line.getCoordinateY(), line.getEnd().getX(), line.getEnd().getY());
    graphics.Restore(origin);
}

// point

VOID DrawText(Graphics& graphics, TextSVG text)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < text.getTransform().size(); ++i) {
        findOrderTransform(text.getTransform()[i]);
        splitString(text.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    GraphicsPath path;
    StringFormat strFormat;
    strFormat.SetAlignment(StringAlignmentCenter);
    SolidBrush brush(Color(round(255 * text.getFillOpacity()), text.getFill().getRed(), text.getFill().getGreen(), text.getFill().getBlue()));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, text.getFont_size(), 0, UnitPixel);
    PointF pointF(text.getCoordinateX() + text.getDx(), text.getCoordinateY() - text.getFont_size() + text.getDy());
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring content = converter.from_bytes(text.getContent());
    path.AddString(content.c_str(), -1, &fontFamily, FontStyleRegular, static_cast<REAL>(text.getFont_size()), pointF, &strFormat);
    Pen pen(Color(round(255 * text.getStrokeOpacity()), text.getStroke().getRed(), text.getStroke().getGreen(), text.getStroke().getBlue()), text.getStrokeWidth());


    graphics.DrawString(content.c_str(), -1, &font, pointF, &brush);


    if (text.getStrokeWidth() != 0)
        graphics.DrawPath(&pen, &path);

    graphics.Restore(origin);
}

// wstring

VOID DrawPolygon(Graphics& graphics, PolygonSVG plg)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < plg.getTransform().size(); ++i) {
        findOrderTransform(plg.getTransform()[i]);
        splitString(plg.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    int nPoint = plg.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = plg.getPoints()[i].getX();
        points[i].Y = plg.getPoints()[i].getY();
    }

    SolidBrush brush(Color(round(255 * plg.getStrokeOpacity()), plg.getFill().getRed(), plg.getFill().getGreen(), plg.getFill().getBlue()));
    graphics.FillPolygon(&brush, points, nPoint);
 
    Pen pen(Color(round(255 * plg.getStrokeOpacity()), plg.getStroke().getRed(), plg.getStroke().getGreen(), plg.getStroke().getBlue()), plg.getStrokeWidth());
    if (plg.getStrokeWidth() != 0)
        graphics.DrawPolygon(&pen, points, nPoint);
    graphics.Restore(origin);
}

// Point* + nPoint

VOID DrawPath(Graphics& graphics, PathSVG path)
{

    GraphicsState origin = graphics.Save();
    for (int i = 0; i < path.getTransform().size(); ++i) {
        findOrderTransform(path.getTransform()[i]);
        splitString(path.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    int nPath = path.getCommand().size();
    GraphicsPath* graphicsPath = new GraphicsPath[nPath];

    int j = 0;
    for (int i = 0; i < nPath; i++)
    {
        if (path.getCommand()[i] == 'M')
        {
            j++;
        }
        else if (path.getCommand()[i] == 'L' || path.getCommand()[i] == 'H' || path.getCommand()[i] == 'V')
        {
            graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(), path.getPoints()[j].getX(), path.getPoints()[j].getY());
            j++;
        }
        else if (path.getCommand()[i] == 'C')
        {
            graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(), path.getPoints()[j].getX(), path.getPoints()[j].getY(), path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY(), path.getPoints()[j + 2].getX(), path.getPoints()[j + 2].getY());
            j += 3;
        }
        else if (path.getCommand()[i] == 'Z' || path.getCommand()[i] == 'z')
        {
            graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(), path.getPoints()[0].getX(), path.getPoints()[0].getY());
        }
        if (path.getCommand()[i] == 'm')
        {
            j++;
        }
        else if (path.getCommand()[i] == 'l' || path.getCommand()[i] == 'h' || path.getCommand()[i] == 'v')
        {
            graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(), path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j + 1].getY() + path.getPoints()[j].getY());
            j++;
        }
        else if (path.getCommand()[i] == 'c')
        {
            graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(), path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY(), path.getPoints()[j - 1].getX() + path.getPoints()[j + 1].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 1].getY(), path.getPoints()[j - 1].getX() + path.getPoints()[j + 2].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 2].getY());
            j += 3;
        }
    }

    SolidBrush brush(Color(round(255 * path.getFillOpacity()), path.getFill().getRed(), path.getFill().getGreen(), path.getFill().getBlue()));
    graphics.FillPath(&brush, graphicsPath);

    Pen pen(Color(round(255 * path.getStrokeOpacity()), path.getStroke().getRed(), path.getStroke().getGreen(), path.getStroke().getBlue()), path.getStrokeWidth());
    graphics.DrawPath(&pen, graphicsPath);
    graphics.Restore(origin);
}

// graphicsPath*

VOID DrawPolyline(Graphics& graphics, PolylineSVG pll)
{
    GraphicsState origin = graphics.Save();
    for (int i = 0; i < pll.getTransform().size(); ++i) {
        findOrderTransform(pll.getTransform()[i]);
        splitString(pll.getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
    int nPoint = pll.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = pll.getPoints()[i].getX();
        points[i].Y = pll.getPoints()[i].getY();
    }

    SolidBrush brush(Color(round(255 * pll.getFillOpacity()), pll.getFill().getRed(), pll.getFill().getGreen(), pll.getFill().getBlue()));
    graphics.FillPolygon(&brush, points, nPoint);
    Pen pen(Color(round(255 * pll.getStrokeOpacity()), pll.getStroke().getRed(), pll.getStroke().getGreen(), pll.getStroke().getBlue()), pll.getStrokeWidth());
    if (pll.getStrokeWidth() != 0)
        graphics.DrawLines(&pen, points, nPoint);

    graphics.Restore(origin);
}

void drawShape(Graphics& graphics, vector<ShapeData> data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        if (data[i].getTypeName() == "rect") {
            RectangleSVG* rect = dynamic_cast<RectangleSVG*> (data[i].getShape());
            DrawRectangle(graphics, *rect);
        }

        else if (data[i].getTypeName() == "circle") {
            CircleSVG* cir = dynamic_cast<CircleSVG*> (data[i].getShape());
            DrawCircle(graphics, *cir);
        }

        else if (data[i].getTypeName() == "text") {
            TextSVG* txt = dynamic_cast<TextSVG*> (data[i].getShape());
            DrawText(graphics, *txt);
        }

        else if (data[i].getTypeName() == "line") {
            LineSVG* line = dynamic_cast<LineSVG*> (data[i].getShape());
            DrawLine(graphics, *line);
        }

        else if (data[i].getTypeName() == "ellipse") {
            EllipseSVG* ellip = dynamic_cast<EllipseSVG*> (data[i].getShape());
            DrawEllipse(graphics, *ellip);
        }

        else if (data[i].getTypeName() == "polygon") {
            PolygonSVG* polygon = dynamic_cast<PolygonSVG*> (data[i].getShape());
            DrawPolygon(graphics, *polygon);
        }
        else if (data[i].getTypeName() == "polyline") {
            PolylineSVG* polyline = dynamic_cast<PolylineSVG*> (data[i].getShape());
            DrawPolyline(graphics, *polyline);
        }
        else if (data[i].getTypeName() == "path") {
            PathSVG* path = dynamic_cast<PathSVG*> (data[i].getShape());
            DrawPath(graphics, *path);
        }
        else if (data[i].getTypeName() == "g") {
            GroupSVG* g = dynamic_cast<GroupSVG*> (data[i].getShape());
            drawShape(graphics, *g->getG());
        }
    }
}
VOID OnPaint(HDC hdc)
{
    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    // Read XML
    xml_document<> doc;
    xml_node<>* rootNode;
    string filename = "svg-07.svg";
    // Read the xml file into a vector
    ifstream file(filename);
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc 
    doc.parse<0>(&buffer[0]);

    rootNode = doc.first_node("svg");
    xml_node<>* node = rootNode->first_node();
    SVGReader::setID(node);
    ShapeData temp;
    vector<ShapeData> data;

    // Load font for text rendering
    temp.readFile(node, data, filename);
    temp.ReplaceProperties(data);
    
    drawShape(graphics, data);

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

string ConvertLPCWSTRToString(LPCWSTR lpcwszStr)
{
    // Determine the length of the converted string 
    int strLength
        = WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1,
            nullptr, 0, nullptr, nullptr);

    // Create a std::string with the determined length 
    string str(strLength, 0);

    // Perform the conversion from LPCWSTR to std::string 
    WideCharToMultiByte(CP_UTF8, 0, lpcwszStr, -1, &str[0],
        strLength, nullptr, nullptr);

    // Return the converted std::string 
    return str;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    


    //// Read XML
    //xml_document<> doc;
    //xml_node<>* rootNode;
    //// Read the xml file into a vector
    //ifstream file("sample.svg");
    //vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    //buffer.push_back('\0');
    //// Parse the buffer using the xml file parsing library into doc 
    //doc.parse<0>(&buffer[0]);

    //rootNode = doc.first_node();
    //xml_node<>* node = rootNode->first_node();

    //while (node != NULL) {
    //    char* nodeName = node->name();
    //    xml_attribute<>* firstAttribute = node->first_attribute();
    //    char* attributeName = firstAttribute->name();
    //    char* attributeValue = firstAttribute->value();
    //    xml_attribute<>* secondAttribute = firstAttribute->next_attribute();
    //    // Set breakpoint here to view value
    //    // Ref: http://rapidxml.sourceforge.net/manual.html
    //    node = node->next_sibling();
    //}



    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("SVG Renderer"),     // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc

int __cdecl main()
{
    string filename;
    LPWSTR* szArglist;
    int nArgs;
    int k;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (NULL == szArglist)
    {
        wprintf(L"CommandLineToArgvW failed\n");
        return 0;
    }
    else for (k = 0; k < nArgs; k++) printf("%d: %ws\n", k, szArglist[k]);

    // Free memory allocated for CommandLineToArgvW arguments.
    if (nArgs > 1)
        filename = ConvertLPCWSTRToString(szArglist[1]);
    else {
        cout << "Enter file name: ";
        getline(cin, filename);
        filename += ".svg";
        cout << filename << endl;
    }
    LocalFree(szArglist);

    // Read XML
    xml_document<> doc;
    xml_node<>* rootNode;
    
    // Read the xml file into a vector
    ifstream file(filename);
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    // Parse the buffer using the xml file parsing library into doc 
    doc.parse<0>(&buffer[0]);
    
    rootNode = doc.first_node("svg");
    xml_node<>* node = rootNode->first_node();
    int i = 0, j = 0;
    SVGReader::setID(node);
    ShapeData temp;
    vector<ShapeData> data;
    
    // Load font for text rendering
    
    temp.readFile(node, data, filename);
    temp.ReplaceProperties(data);

    return(1);
}
