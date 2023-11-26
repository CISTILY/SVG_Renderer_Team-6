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

SVGReader& SVGReader::operator+= (SVGReader& other) {
    vector<string> type = { "stroke", "stroke-width", "stroke_opacity", "fill", "file-opacity" };
    vector<bool> src = { 0, 0, 0, 0, 0 };
    vector<bool> dest = { 0, 0, 0, 0, 0 };
    for (int i = 0; i < type.size(); ++i) {
        for (int j = 0; j < other.getPropsAttrName().size(); ++j) {
            if (type[i] == other.getPropsAttrName()[j])
                dest[i] = 1;
        }
        for (int j = 0; j < this->getPropsAttrName().size(); ++j) {
            if (type[i] == this->getPropsAttrName()[j])
                src[i] = 1;
        }
    }
    for (int i = 0; i < dest.size(); ++i) {
        if (dest[i] == src[i] || dest[i] < src[i])
            continue;
        for (int j = 0; j < other.getPropsAttrName().size(); ++j) {
            if (type[i] == other.getPropsAttrName()[j]) {
                this->PropertiesBuilder(other.getPropsAttrName()[j], other.getPropsAttrValue()[j]);
            }
        }
    }
    cout << endl;
    return *this;
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

void SVGReader::ReplaceProperties(SVGReader group) {
    vector<string> type = { "stroke", "stroke-width", "stroke_opacity", "fill", "file-opacity" };
    vector<bool> shapeAttr = { 0, 0, 0, 0, 0 };
    vector<bool> groupAttr = { 0, 0, 0, 0, 0 };
    for (int i = 0; i < type.size(); ++i) {
        for (int j = 0; j < group.getPropsAttrName().size(); ++j) {
            if (type[i] == group.getPropsAttrName()[j])
                groupAttr[i] = 1;
        }
        for (int j = 0; j < this->getPropsAttrName().size(); ++j) {
            if (type[i] == this->getPropsAttrName()[j])
                shapeAttr[i] = 1;
        }
    }
    for (int i = 0; i < groupAttr.size(); ++i) {
        if (groupAttr[i] == shapeAttr[i] || groupAttr[i] < shapeAttr[i])
            continue;
        for (int j = 0; j < group.getPropsAttrName().size(); ++j) {
            if (type[i] == group.getPropsAttrName()[j]) {
                this->PropertiesBuilder(group.getPropsAttrName()[j], group.getPropsAttrValue()[j]);
            }
        }
    }
    cout << endl;
}

void SVGReader::setID(xml_node<>* node) {
    if (!ID.empty())
        return;
    while (node != NULL) {
        ID.push_back(1);
        node = node->next_sibling();
    }

}

void SVGReader::readContent() {
    if (!content.empty())
        return;

    ifstream fIn;
    fIn.open("sample1.svg");
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