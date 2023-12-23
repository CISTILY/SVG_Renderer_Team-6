#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Point2D.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class ScreenSVG
{
private:
    float width;
    float height;
    float view_box[4];
    string xRatio;
    string yRatio;
    string aspect;

    bool flagWidth;
    bool flagHeight;
    bool flagViewBox;
    bool flagRatio;

public:
    ScreenSVG();
  
    ~ScreenSVG();
    
    void buildScreen(vector<char*>, vector<char*>);
    void readScreen(xml_node<>* node);
    void printScreen();

    bool getFlagViewBox();
    bool getFlagRatio();
    Point2D getSize();
    Point2D getView();
    Point2D getViewPosition();
    string getXRatio();
    string getYRatio();
    string getAspect();
};
