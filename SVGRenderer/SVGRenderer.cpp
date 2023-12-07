#include "stdafx.h"

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include <shellapi.h>
#include <locale>
#include <codecvt>
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID DrawCircle(Graphics& graphics, CircleSVG circle)
{
    Rect rect(circle.getCoordinateY(), circle.getCoordinateY(), circle.getRadiusX(), circle.getRadiusY());

    SolidBrush brush(Color(circle.getFill().getRed(), circle.getFill().getGreen(), circle.getFill().getBlue(), circle.getFillOpacity()));
    graphics.FillEllipse(&brush, rect);

    Pen pen(Color(circle.getStroke().getRed(), circle.getStroke().getGreen(), circle.getStroke().getBlue(), circle.getStrokeOpacity()), circle.getStrokeWidth());
    graphics.DrawEllipse(&pen, rect);
}

VOID DrawRectangle(Graphics& graphics, RectangleSVG rect)
{
    Rect rectangle(rect.getCoordinateX(), rect.getCoordinateY(), rect.getHeight(), rect.getWidth());

    SolidBrush brush(Color(rect.getFill().getRed(), rect.getFill().getGreen(), rect.getFill().getBlue(), rect.getFillOpacity()));
    graphics.FillRectangle(&brush, rectangle);

    Pen pen(Color(rect.getStroke().getRed(), rect.getStroke().getGreen(), rect.getStroke().getBlue(), rect.getStrokeOpacity()), rect.getStrokeWidth());
    graphics.DrawRectangle(&pen, rectangle);
}

VOID DrawEllipse(Graphics& graphics, EllipseSVG ellip)
{
    Rect rect(ellip.getCoordinateX(), ellip.getCoordinateY(), ellip.getRadiusX(), ellip.getRadiusY());

    SolidBrush brush(Color(ellip.getFill().getRed(), ellip.getFill().getGreen(), ellip.getFill().getBlue(), ellip.getFillOpacity()));
    graphics.FillEllipse(&brush, rect);

    Pen pen(Color(ellip.getStroke().getRed(), ellip.getStroke().getGreen(), ellip.getStroke().getBlue(), ellip.getStrokeOpacity()), ellip.getStrokeWidth());
    graphics.DrawEllipse(&pen, rect);
}

VOID DrawLine(Graphics& graphics, LineSVG line)
{
    Pen pen(Color(line.getStroke().getRed(), line.getStroke().getGreen(), line.getStroke().getBlue(), line.getStrokeOpacity()), line.getStrokeWidth());
    graphics.DrawLine(&pen, line.getCoordinateX(), line.getCoordinateY(), line.getEnd().getX(), line.getEnd().getY());
}

VOID DrawText(Graphics& graphics, TextSVG text)
{
    SolidBrush brush(Color(text.getFill().getRed(), text.getFill().getGreen(), text.getFill().getBlue(), text.getFillOpacity()));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, text.getFont_size(), 0, UnitPixel);
    PointF pointF(text.getCoordinateX(), text.getCoordinateY());
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring content = converter.from_bytes(text.getContent());
    graphics.DrawString(content.c_str(), -1, &font, pointF, &brush);
}

VOID DrawPolygon(Graphics& graphics, PolygonSVG plg)
{
    int nPoint = plg.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = plg.getPoints()[i].getX();
        points[i].Y = plg.getPoints()[i].getY();
    }

    SolidBrush brush(Color(plg.getStroke().getRed(), plg.getStroke().getGreen(), plg.getStroke().getBlue(), plg.getStrokeOpacity()));
    graphics.FillPolygon(&brush, points, nPoint);
 
    Pen pen(Color(plg.getStroke().getRed(), plg.getStroke().getGreen(), plg.getStroke().getBlue(), plg.getStrokeOpacity()), plg.getStrokeWidth());
    graphics.DrawPolygon(&pen, points, nPoint);
}

VOID DrawPath(Graphics& graphics, PathSVG path)
{
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
        else if (path.getCommand()[i] == 'Z')
        {
            graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(), path.getPoints()[0].getX(), path.getPoints()[0].getY());
        }
    }

    SolidBrush brush(Color(path.getStroke().getRed(), path.getStroke().getGreen(), path.getStroke().getBlue(), path.getStrokeOpacity()));
    graphics.FillPath(&brush, graphicsPath);

    Pen pen(Color(path.getStroke().getRed(), path.getStroke().getGreen(), path.getStroke().getBlue(), path.getStrokeOpacity()), path.getStrokeWidth());
    graphics.DrawPath(&pen, graphicsPath);
}

VOID DrawPolyline(Graphics& graphics, PolylineSVG pll)
{
    int nPoint = pll.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = pll.getPoints()[i].getX();
        points[i].Y = pll.getPoints()[i].getY();
    }

    SolidBrush brush(Color(pll.getStroke().getRed(), pll.getStroke().getGreen(), pll.getStroke().getBlue(), pll.getStrokeOpacity()));
    graphics.FillPolygon(&brush, points, nPoint);

    Pen pen(Color(pll.getStroke().getRed(), pll.getStroke().getGreen(), pll.getStroke().getBlue(), pll.getStrokeOpacity()), pll.getStrokeWidth());
    graphics.DrawLines(&pen, points, nPoint);
}

VOID OnPaint(HDC hdc)
{
    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    Pen      pen(Color(255, 255, 0, 255));
    graphics.DrawLine(&pen, 0, 0, 200, 100);
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
