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

    bool flagWidth;
    bool flagHeight;
    bool flagViewBox;

public:
    ScreenSVG();
  
    ~ScreenSVG();
    
    void buildScreen(vector<char*>, vector<char*>);
    void readScreen(xml_node<>* node);
    void printScreen();

    Point2D getSize();
    Point2D getView();
};
