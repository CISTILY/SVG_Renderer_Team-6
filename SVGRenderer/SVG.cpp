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

void SVGReader::ReplaceProperties(SVGReader group) {
    vector<string> type = { "stroke", "stroke-width", "stroke_opacity", "fill", "file-opacity", "transform" };
    vector<bool> shapeAttr = { 0, 0, 0, 0, 0, 0 };
    vector<bool> groupAttr = { 0, 0, 0, 0, 0, 0 };
    bool merge = false;
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

    for (int i = 0; i < shapeAttr.size(); ++i) {
        if (shapeAttr[i] != groupAttr[i]) {
            merge = true;
        }
    }

    if (merge == true) {
        if (shapeAttr[5] == groupAttr[5]) {
            string temp1 = "", temp2 = "";
            Point2D translate1, scalePoint1("1, 1"), translate2, scalePoint2("1, 1"), scalePoint;
            float angle1 = 0, angle2 = 0, scaleAngle1 = 1, scaleAngle2 = 1;
            vector<int> type1 = { 0, 0, 0 }, type2 = { 0, 0, 0 };
            bool isPoint = false;
            string scale;

            for (int i = 0; i < group.getPropsAttrName().size(); ++i)
                if (type[5] == group.getPropsAttrName()[i])
                    temp1 = group.getPropsAttrValue()[i];

            for (int i = 0; i < this->getPropsAttrName().size(); ++i)
                if (type[5] == this->getPropsAttrName()[i])
                    temp2 = this->getPropsAttrValue()[i];

            this->getTransformValue(temp2, translate2, angle2, scalePoint2, scaleAngle2, type2);
            this->getTransformValue(temp1, translate1, angle1, scalePoint1, scaleAngle1, type1);
            if (type1[0] == type2[0]) {
                translate1.setX(translate1.getX() + translate2.getX());
                translate1.setY(translate1.getY() + translate2.getY());
            }
            if (type1[1] == type2[1]) {
                angle1 += angle2;
            }
            if (type1[2] == type2[2]) {

                if (scaleAngle1 != 1 || scaleAngle2 != 1) {
                    scaleAngle1 += scaleAngle2;
                    isPoint = true;
                    scalePoint.setX(scaleAngle1);
                    scalePoint.setY(scaleAngle1);
                }

                else if (scalePoint1.getX() != 1 || scalePoint1.getY() != 1 || scalePoint2.getX() != 1 || scalePoint2.getY() != 1) {
                    scalePoint1.setX(scalePoint1.getX() + scalePoint2.getX());
                    scalePoint1.setY(scalePoint1.getY() + scalePoint2.getY());
                }

                
                cout << "================" << scale;
            }
            if (isPoint == true) {
                scale = scalePoint.ToString();
            }
            else {
                scale = scalePoint1.ToString();
            }
            string transform = "translate(" + translate1.ToString() + ") rotate(" + to_string(angle1) + ") scale(" + scale + ")";
            const char* temp = transform.c_str();

            for (int i = 0; i < group.getPropsAttrName().size(); ++i) {
                if (strstr(group.getPropsAttrName()[i], "transform") != NULL) {
                    strcpy_s(group.getPropsAttrValue()[i], strlen(group.getPropsAttrValue()[i]) + (strlen(temp) - strlen(group.getPropsAttrValue()[i])) + 1, temp);
                }
            }
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
    fIn.open("test.svg");
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