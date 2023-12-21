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
public:
    // Constructor
    SVGReader();

    // Destructor
    ~SVGReader();

    // Setters
    void setNodeName(char*);
    void PropertiesBuilder(char*, char*);
    static void readContent(string);
    
    // Getters
    char* getNodeName();
    vector<char*> getOtherAttrName();
    vector<char*> getOtherAttrValue();
    vector<char*> getPropsAttrName();
    vector<char*> getPropsAttrValue();

    static vector<string> getContent();
};
