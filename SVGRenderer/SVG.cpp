#include "SVG.h"

using namespace std;

vector<string> SVGReader::content;

SVGReader::SVGReader()
{
    this->nodeName = NULL;

    //cout << "SVGReader::Default Constructor" << endl;
}

SVGReader::~SVGReader() {
    //cout << "SVGReader::Destructor" << endl;
}

void SVGReader::setNodeName(char* name)
{
    nodeName = name;
}

char* SVGReader::getNodeName()
{
    return nodeName;
}

void SVGReader::PropertiesBuilder(char* attrName, char* attrVal) {
    string temp = attrName;

    if (temp == "type-name")
    {
        string tempValue = attrVal;
        if (tempValue == "rect" || tempValue == "circle" || tempValue == "ellipse"
            || tempValue == "text" || tempValue == "line" || tempValue == "polygon"
            || tempValue == "polyline" || tempValue == "path" || tempValue == "g") {
            PropsAttrName.push_back(attrName);
            PropsAttrValue.push_back(attrVal);
        }
    }
    else if (temp == "fill-opacity" || temp == "fill" || temp == "stroke-opacity"
        || temp == "stroke-width" || temp == "stroke" || temp == "transform") {
        PropsAttrName.push_back(attrName);
        PropsAttrValue.push_back(attrVal);
    }
    else {
        OtherAttrName.push_back(attrName);
        OtherAttrValue.push_back(attrVal);
    }
}

void SVGReader::readContent(string filename)
{
    if (!content.empty())
        return;

    ifstream fIn;
    fIn.open(filename);
    string fileSVG, text, line;
    int markContinue = 0;

    while (!fIn.eof())
    {
        getline(fIn, line, '\n');
        fileSVG += line;
    }

    while (fileSVG.find("<text", markContinue) != string::npos)
    {
        markContinue = fileSVG.find("<text", markContinue);
        int markStart = fileSVG.find(">", markContinue);
        int markEnd = fileSVG.find("<", markStart + 1);
        markContinue = markEnd;

        text = fileSVG.substr(markStart + 1, markEnd - markStart - 1);

        while (text[0] == ' ')
            text.erase(0, 1);
        while (text.find("  ") != string::npos)
            text.erase(text.find("  "), 1);

        content.push_back(text);
    }
    
    fIn.close();
}

vector<char*> SVGReader::getOtherAttrName() {
    return this->OtherAttrName;
}

vector<char*> SVGReader::getOtherAttrValue() {
    return this->OtherAttrValue;
}

vector<char*> SVGReader::getPropsAttrName() {
    return this->PropsAttrName;
}

vector<char*> SVGReader::getPropsAttrValue() {
    return this->PropsAttrValue;
}

vector<string> SVGReader::getContent() {
    return content;
}
