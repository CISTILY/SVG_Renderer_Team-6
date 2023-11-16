#pragma once

#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Properties.h"

using namespace std;

class SVGReader {
private:
    char* nodeName;
    vector<char*> PropsAttrName;
    vector<char*> PropsAttrValue;
    vector<char*> OtherAttrName;
    vector<char*> OtherAttrValue;
    static vector<string> content;
public:
    SVGReader();
    ~SVGReader();

    void setNodeName(char*);
    char* getNodeName();

    void PropertiesBuilder(char*, char*, Properties&);
    static void readContent();
    static vector<string> getContent();
    vector<char*> getOtherAttrName();
    vector<char*> getOtherAttrValue();
};
