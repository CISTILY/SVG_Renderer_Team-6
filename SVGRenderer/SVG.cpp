#include "SVG.h"

using namespace std;

vector<string> SVGReader::content;
vector<int> SVGReader::ID;

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

void SVGReader::resetNode() {
    this->~SVGReader();
}

void SVGReader::PropertiesBuilder(char* attrName, char* attrVal) {

    if (strstr(attrName, "fill-opacity") != NULL || strstr(attrName, "fill") != NULL || strstr(attrName, "stroke-opacity") != NULL
        || strstr(attrName, "stroke-width") != NULL || strstr(attrName, "stroke") != NULL || strstr(attrName, "transform")!= NULL) {
        PropsAttrName.push_back(attrName);
        PropsAttrValue.push_back(attrVal);
    }
    else {
        OtherAttrName.push_back(attrName);
        OtherAttrValue.push_back(attrVal);
    }
}

void SVGReader::getTransformValue(string str, Point2D& translate, float& rotate, Point2D& scalePoint, float& scaleAngle, vector<int>& type) {
    string value;
    while (str != "") {
        if (str.find("translate") != string::npos) {
            type[0] = 1;
            int pos = str.find(')');
            value = str.substr(str.find("translate") + 10, pos - 1 - 9);
            Point2D* temp = new Point2D(value);
            translate = *temp;
            str.erase(0, pos + 1);
            delete temp;
        }
        else if (str.find("rotate") != string::npos) {
            type[1] = 1;
            int pos = str.find(')');
            value = str.substr(str.find("rotate") + 7, pos - 1 - 6);
            rotate = stof(value);
            str.erase(0, pos + 1);
        }
        else if (str.find("scale") != string::npos) {
            type[2] = 1;
            int pos = str.find(')');
            value = str.substr(str.find("scale") + 6, pos - 1 - 5);
            if (value.find(',') != string::npos) {
                Point2D* temp = new Point2D(value);
                scalePoint = *temp;
                delete temp;
            }
            else {
                scaleAngle = stof(value);
            }
            str.erase(0, pos + 1);
        }
    }
}



void SVGReader::setID(xml_node<>* node) {
    if (!ID.empty())
        return;
    while (node != NULL) {
        ID.push_back(1);
        node = node->next_sibling();
    }

}

void SVGReader::readContent(string filename) {
    if (!content.empty())
        return;

    ifstream fIn;
    fIn.open(filename);
    string temp, text;
    while (getline(fIn, temp, '\n')) {
        if (temp.find("text") != string::npos) {
            text = temp;
            int pos = text.find(">");
            text = text.substr(pos + 1, text.length());
            pos = text.find("<");
            text = text.substr(0, pos);
            while (text[0] == ' ')
                text.erase(0, 1);
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

vector<int> SVGReader::getID() {
    return ID;
}