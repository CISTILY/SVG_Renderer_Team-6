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

VOID OnPaint(HDC hdc)
{
    // Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

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

    filename = ConvertLPCWSTRToString(szArglist[1]);

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
    ScreenSVG screen;
    screen.readScreen(rootNode);
    
    xml_node<>* node = rootNode->first_node();
    ShapeData temp;
    vector<ShapeData> data;

    // Load font for text rendering
    int text_order = 0;
    temp.readFile(node, data, filename, text_order); 
    for (int i = 0; i < data.size(); ++i) {
        string temp = data[i].getTypeName();
        if (temp == "g")
            data[i].ReplaceProperties();
    }
    Draw pen;
    pen.drawShape(graphics, data);
    LocalFree(szArglist);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;


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

//int __cdecl main() {
//    string filename;
//    LPWSTR* szArglist;
//    int nArgs;
//    int k;
//
//    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
//    if (NULL == szArglist)
//    {
//        wprintf(L"CommandLineToArgvW failed\n");
//        return 0;
//    }
//    else for (k = 0; k < nArgs; k++) {
//        wcout << "line " << k << ": ";
//        wcout << szArglist[k] << endl;
//    }
//
//    if (nArgs > 1)
//        filename = ConvertLPCWSTRToString(szArglist[1]);
//    else {
//        cout << "Enter file name: ";
//        getline(cin, filename);
//        filename += ".svg";
//        cout << filename << endl;
//    }
//    LocalFree(szArglist);
//
//    // Read XML
//    xml_document<> doc;
//    xml_node<>* rootNode;
//    // Read the xml file into a vector
//    ifstream file(filename);
//    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//    buffer.push_back('\0');
//    // Parse the buffer using the xml file parsing library into doc 
//    doc.parse<0>(&buffer[0]);
//
//    rootNode = doc.first_node("svg");
//    ScreenSVG screen;
//    screen.readScreen(rootNode);
//
//    xml_node<>* node = rootNode->first_node();
//    ShapeData temp;
//    vector<ShapeData> data;
//
//    // Load font for text rendering
//    int text_order = 0;
//    temp.readFile(node, data, filename, text_order); 
//    for (int i = 0; i < data.size(); ++i) {
//        string temp = data[i].getTypeName();
//        if (temp == "g")
//            data[i].ReplaceProperties();
//    }
//    return (1);
//}
