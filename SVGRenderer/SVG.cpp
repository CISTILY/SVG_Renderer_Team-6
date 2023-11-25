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

    if (strstr(attrName, "fill-opacity") != NULL || strstr(attrName, "fill") != NULL || strstr(attrName, "stroke-opacity") != NULL
        || strstr(attrName, "stroke-width") != NULL || strstr(attrName, "stroke") != NULL) {
        PropsAttrName.push_back(attrName);
        PropsAttrValue.push_back(attrVal);
    }
    else {
        OtherAttrName.push_back(attrName);
        OtherAttrValue.push_back(attrVal);
    }
}

void SVGReader::readContent() {
    if (!content.empty())
        return;

    ifstream fIn;
    fIn.open("sample.svg");
    string temp, text;
    while (getline(fIn, temp, '\n')) {
        if (temp.find("text") != string::npos) {
            text = temp;
            int pos = text.find(">");
            text = text.substr(pos + 1, text.length());
            pos = text.find("<");
            text = text.substr(0, pos);
            content.push_back(text);
        }
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