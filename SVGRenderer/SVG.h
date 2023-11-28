#pragma once

#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "rapidxml.hpp"
#include "Shape.h"

using namespace std;
using namespace rapidxml;

class SVGReader {
private:
    char* nodeName;
    vector<char*> PropsAttrName;
    vector<char*> PropsAttrValue;
    vector<char*> OtherAttrName;
    vector<char*> OtherAttrValue;
    static vector<string> content;
    static vector<int> ID;
public:
    // Constructor
    SVGReader();

    // Destructor
    ~SVGReader();

    // Setters
    void setNodeName(char*);
    void PropertiesBuilder(char*, char*);
    static void readContent();
    static void setID(xml_node<>*);
    void ReplaceProperties(SVGReader);

    
    // Getters
    char* getNodeName();
    vector<char*> getOtherAttrName();
    vector<char*> getOtherAttrValue();
    vector<char*> getPropsAttrName();
    vector<char*> getPropsAttrValue();
    static vector<string> getContent();
    static vector<int> getID();

    void resetNode();
    void getTransformValue(string, Point2D&, float&, Point2D&, float&, vector<int>&);
};
