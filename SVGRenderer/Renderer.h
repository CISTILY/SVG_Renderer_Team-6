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

int TranslateRotateScale[3];

void findOrderTransform(string transform)
{
    int posTranslate = transform.find("translate");
    int posRotate = transform.find("rotate");
    int posScale = transform.find("scale");

    if (posTranslate == string::npos)
        posTranslate = transform.length();
    if (posRotate == string::npos)
        posRotate = transform.length();
    if (posScale == string::npos)
        posScale = transform.length();

    if (posTranslate <= posRotate && posTranslate <= posScale)
    {
        TranslateRotateScale[0] = 0;
        if (posRotate <= posScale)
        {
            TranslateRotateScale[1] = 1;
            TranslateRotateScale[2] = 2;
        }
        else
        {
            TranslateRotateScale[1] = 2;
            TranslateRotateScale[2] = 1;
        }
    }
    else if (posRotate <= posTranslate && posRotate <= posScale)
    {
        TranslateRotateScale[0] = 1;
        if (posTranslate <= posScale)
        {
            TranslateRotateScale[1] = 0;
            TranslateRotateScale[2] = 2;
        }
        else
        {
            TranslateRotateScale[1] = 2;
            TranslateRotateScale[2] = 0;
        }
    }
    else
    {
        TranslateRotateScale[0] = 2;
        if (posTranslate <= posRotate)
        {
            TranslateRotateScale[1] = 0;
            TranslateRotateScale[2] = 1;
        }
        else
        {
            TranslateRotateScale[1] = 1;
            TranslateRotateScale[2] = 0;
        }
    }
}

Point2D translate, scalePoint;
float rotateAngle;

void splitString(string str) {
    string value;
    while (str != "") {
        if (str.find("translate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("translate") + 10, pos - 1 - 9);
            Point2D* temp = new Point2D(value);
            translate = *temp;
            str.erase(0, pos + 1);
            delete temp;
        }
        else if (str.find("rotate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("rotate") + 7, pos - 1 - 6);
            rotateAngle = stof(value);
            str.erase(0, pos + 1);
        }
        else if (str.find("scale") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("scale") + 6, pos - 1 - 5);
            Point2D* temp = new Point2D(value);
            scalePoint = *temp;
            delete temp;
            str.erase(0, pos + 1);
        }
    }
}