#include "stdafx.h"

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

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

VOID OnPaint(HDC hdc, float xPos, float yPos, int angle, Point2D scale, float zoom)
{
    ShapeData* data = ShapeData::getInstance();
    ScreenSVG screen = data->getScreen();

    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.RotateTransform(static_cast<REAL> (angle));
    graphics.TranslateTransform(static_cast<REAL>(xPos), static_cast<REAL>(yPos));
    //graphics.SetClip(RectF(0, 0, screen.getSize().getX() * zoom, screen.getSize().getY() * zoom));
    graphics.ScaleTransform(scale.getX() * zoom, scale.getY() * zoom);
    
    Draw pen;
    pen.drawShape(graphics, data->getVectorShape(), data->getDef());
    Draw::setDrew(1);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    ////////////////////////////////////////////////////

    string filename; 
    LPWSTR* szArglist;
    int nArgs;
    int k;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

    if (NULL == szArglist)
    {
        wprintf(L"CommandLineToArgvW failed\n");
    }
    else for (k = 0; k < nArgs; k++) {
        wcout << "line " << k << ": ";
        wcout << szArglist[k] << endl;
    }

    //filename = ConvertLPCWSTRToString(szArglist[1]);
    filename = "svg-14.svg";

    ShapeData* data = ShapeData::getInstance();
    data->readSVG(filename);

    LocalFree(szArglist);

    ////////////////////////////////////////////////////

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
        data->getScreen().getSize().getX(),            // initial x size
        data->getScreen().getSize().getY(),            // initial y size
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

    ShapeData* data = ShapeData::getInstance();
    static Point2D scale(1.0, 1.0);
    
    static float xPos = 0;
    static float yPos = 0;
    static int angle = 0;
    static float zoom = 1.0;
    const int a = 5;
    const int stepSize = 30;

    switch (message)
    {
    case WM_CREATE:
        if (data->getScreen().getFlagViewBox() == true) 
        {
            ScreenSVG screen = data->getScreen();
            RECT rect;
            GetClientRect(hWnd, &rect); // get port size

            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            float scrWidth = screen.getView().getX();
            float scrHeight = screen.getView().getY();

            scale.setX(width / scrWidth);
            scale.setY(height / scrHeight);

            if (screen.getFlagRatio())
            {
                if (screen.getAspect() == "slice")
                {
                    if (width > height)
                    {
                        scale.setY(scale.getX());
                    }
                    else if (width < height)
                    {
                        scale.setX(scale.getY());
                    }
                }
                else if (screen.getAspect() == "meet") {
                    if (scale.getX() > scale.getY())
                        scale.setX(scale.getY());
                    else scale.setY(scale.getX());
                }

                string xRatio = screen.getXRatio();
                string yRatio = screen.getYRatio();
                if (xRatio == "Mid")
                    xPos = abs(static_cast<float>(width) - screen.getView().getX() * scale.getX()) / 2;
                else if (xRatio == "Max")
                    xPos = abs(static_cast<float>(width) - screen.getView().getX() * scale.getX());
                if (yRatio == "Mid")
                    yPos = abs(static_cast<float>(height) - screen.getView().getY() * scale.getY()) / 2;
                else if (yRatio == "Max")
                    yPos = abs(static_cast<float>(height) - screen.getView().getY() * scale.getY());
            }
            else {
                if (scale.getX() > scale.getY())
                    scale.setX(scale.getY());
                else scale.setY(scale.getX());

                xPos = -data->getScreen().getViewPosition().getX() * scale.getX();
                yPos = -data->getScreen().getViewPosition().getY() * scale.getY();
            }
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc, xPos, yPos, angle, scale, zoom);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            xPos += stepSize;
            break;
        case VK_RIGHT:
            xPos -= stepSize;
            break;
        case VK_UP:
            yPos += stepSize;
            break;
        case VK_DOWN:
            yPos -= stepSize;
            break;
        case 'E': case 'e':
            angle += a;
            break;
        case 'Q': case 'q':
            angle -= a;
            break;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MOUSEWHEEL:
    {
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (delta > 0) {
            zoom *= 1.1;
        }
        else {
            zoom *= 0.9;
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}