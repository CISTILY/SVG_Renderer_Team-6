#include "Gradient.h"

using namespace std;

stop::stop() {
    this->offset = 0;
    this->stop_opacity = 0;
}
stop::~stop() { }
void stop::setOffset(float offset) {
	this->offset = offset;
}

void stop::setColor(string s) {
	this->stop_color.setColor(s);
}

float stop::getOffset() {
	return this->offset;
}

ColorSVG stop::getStopColor() {
	return this->stop_color;
}

void stop::buildStop(vector<char*> name, vector<char*> value) {
    for (int i = 0; i < name.size(); ++i) {
        string temp = name[i];
        if (temp == "offset")
            this->offset = atof(value[i]);
        else if (temp == "stop-color") {
            string a = value[i];
            this->stop_color.setColor(a);
        }
        else if (temp == "stop-opacity") {
            this->stop_opacity = atof(value[i]);
        }
    }
}

void stop::printStop() {
    cout << this->offset << " "; this->stop_color.print(); cout << " " << this->stop_opacity << endl;
}

LinearGradientSVG::LinearGradientSVG() {
    this->rotate = 0;
}
LinearGradientSVG::~LinearGradientSVG() { }

Gradient::Gradient() {
    this->rotate = 0;
}
Gradient::~Gradient() { }

string Gradient::getHref() {
    return this->href;
}

string Gradient::getID() {
    return this->id;
}

vector<stop> Gradient::getStops() {
    return this->stops;
}

void Gradient::setID(char* id) {
    string temp = id;
    this->id = temp;
}

void Gradient::setSpreadMethod(string method) {
    this->spreadMethod = method;
}

void Gradient::setGradientUnits(string unit) {
    this->gradientUnits = unit;
}

void Gradient::addStop(stop a) {
    this->stops.push_back(a);
}

void Gradient::replaceStop(vector<stop> stops) {
    this->stops = stops;
}

void Gradient::setGradientTransform(string transform) {
    string value;
    int posStart = 0, posEnd = 0;
    if (transform.find("translate") != string::npos) {
        posStart = transform.find("translate");
        posEnd = transform.find(')', posStart);
        value = transform.substr(posStart + 10, posEnd - 1 - 9);
        Point2D* temp = new Point2D(value);
        this->translate = *temp;
        delete temp;
    }
    if (transform.find("rotate") != string::npos) {
        posStart = transform.find("rotate");
        posEnd = transform.find(')', posStart);
        value = transform.substr(transform.find("rotate") + 7, posEnd - 1 - 6);
        this->rotate = stof(value);
    }
    if (transform.find("scale") != string::npos) {
        posStart = transform.find("scale");
        posEnd = transform.find(')', posStart);
        value = transform.substr(transform.find("scale") + 6, posEnd - 1 - 5);
        Point2D* temp = new Point2D(value);
        this->scale = *temp;
        delete temp;
    }
}

void LinearGradientSVG::buildGradient(vector<char*> name, vector<char*> value) {
    for (int i = 0; i < name.size(); ++i) {
        string temp = name[i];
        if (temp == "id")
            this->id = value[i];
        else if (temp == "x1")
            this->p1.setX(atof(value[i]));
        else if (temp == "x2")
            this->p2.setX(atof(value[i]));
        else if (temp == "y1")
            this->p1.setY(atof(value[i]));
        else if (temp == "y2")
            this->p2.setY(atof(value[i]));
        else if (temp == "xlink:href") {
            string a = value[i];
            this->href = a;
        }
        else if (temp == "gradientUnits") {
            string a = value[i];
            this->setGradientUnits(a);
        }
        else if (temp == "spreadMethod") {
            string a = value[i];
            this->setSpreadMethod(a);
        }
        else if (temp == "gradientTransform") {
            string a = value[i];
            this->setGradientTransform(a);
        }
    }
}

void LinearGradientSVG::print() {
    cout << "ID: " << this->id << " " << " GradientUnits: " << this->gradientUnits << " SpreadMethod: " << this->spreadMethod << " ";
    cout << "Transform: ";  this->translate.print(); cout << " " << this->rotate << " "; this->scale.print(); cout << " ";
    cout << "Points: "; this->p1.print(); cout << " ";  this->p2.print(); cout << endl;
    for (int i = 0; i < this->stops.size(); ++i) {
        cout << "stop " << i + 1 << ": ";
        this->stops[i].printStop();
    }
}

RadialGradientSVG::RadialGradientSVG() {
    this->rotate = 0;
    this->r = 0;
}

RadialGradientSVG::~RadialGradientSVG() { }

void RadialGradientSVG::buildGradient(vector<char*> name, vector<char*> value) {
    for (int i = 0; i < name.size(); ++i) {
        string temp = name[i];
        if (temp == "id")
            this->id = value[i];
        else if (temp == "cx")
            this->p1.setX(atof(value[i]));
        else if (temp == "fx")
            this->p2.setX(atof(value[i]));
        else if (temp == "cy")
            this->p1.setY(atof(value[i]));
        else if (temp == "fy")
            this->p2.setY(atof(value[i]));
        else if (temp == "r")
            this->r = atof(value[i]);
        else if (temp == "xlink:href") {
            string a = value[i];
            this->href = a;
        }   
        else if (temp == "gradientUnits") {
            string a = value[i];
            this->setGradientUnits(a);
        }
        else if (temp == "spreadMethod") {
            string a = value[i];
            this->setSpreadMethod(a);
        }
        else if (temp == "gradientTransform") {
            string a = value[i];
            this->setGradientTransform(a);
        }
    }
}

void RadialGradientSVG::print() {
    cout << "ID: " << this->id << " " << " GradientUnits: " << this->gradientUnits << " SpreadMethod: " << this->spreadMethod << " ";
    cout << "Transform: ";  this->translate.print(); cout << " " << this->rotate << " "; this->scale.print(); cout << " ";
    cout << "Points: "; this->p1.print(); cout << " ";  this->p2.print(); cout << " " << this->r << endl;
    for (int i = 0; i < this->stops.size(); ++i) {
        cout << "stop " << i + 1 << ": ";
        this->stops[i].printStop();
    }
}

void def::readGradient(xml_node<>* node) {
    LinearGradientSVG temp;
    vector<char*> attrName;
    vector<char*> attrValue;

    while (node != NULL) {
        int id = 0;
        string nameSVGReader = node->name();
        if (nameSVGReader != "linearGradient" && nameSVGReader != "stop" && nameSVGReader != "defs" && nameSVGReader != "radialGradient")
            break;

        xml_node<>* child = node->first_node();

        // Read attributes and build properties
        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {
            attrName.push_back(Attr->name());
            attrValue.push_back(Attr->value());
        }
        buildDef(nameSVGReader, attrName, attrValue);
            
        if (child != NULL)
        {
            if (nameSVGReader == "defs" || nameSVGReader == "linearGradient" || nameSVGReader == "radialGradient")
            {
                this->readGradient(child);
            }
        }
        node = node->next_sibling();
    }
}

void def::buildDef(string id, vector<char*> name, vector<char*> value) {
    if (id == "linearGradient") {
        LinearGradientSVG temp;
        temp.buildGradient(name, value);
        this->LinearGradients.push_back(temp);
        this->previous = 1;
    }
    else if (id == "radialGradient") {
        RadialGradientSVG temp;
        temp.buildGradient(name, value);
        this->RadialGradients.push_back(temp);
        this->previous = 2;
    }
    else if (id == "stop") {
        stop temp;
        temp.buildStop(name, value);
        if (this->previous == 1)
            this->LinearGradients[this->LinearGradients.size() - 1].addStop(temp);
        else if (this->previous == 2)
            this->RadialGradients[this->RadialGradients.size() - 1].addStop(temp);
    }
    
}

void def::printGradient() {
    for (int i = 0; i < this->LinearGradients.size(); ++i) {
        cout << "LinearGradient " << i + 1 << ": ";
        this->LinearGradients[i].print();
        cout << endl;
    }

    for (int i = 0; i < this->RadialGradients.size(); ++i) {
        cout << "RadialGradient " << i + 1 << ": ";
        this->RadialGradients[i].print();
        cout << endl;
    }
}

void def::performHref() {
    for (int i = 0; i < this->LinearGradients.size(); ++i) {
        string temp = this->LinearGradients[i].getHref();
        temp.erase(0, 1);
        for (int j = 0; j < this->LinearGradients.size(); ++j) {
            if (temp == this->LinearGradients[j].getID()) {
                this->LinearGradients[i].replaceStop(this->LinearGradients[j].getStops());
                break;
            }
        }

        for (int j = 0; j < this->RadialGradients.size(); ++j) {
            if (temp == this->RadialGradients[j].getID()) {
                this->LinearGradients[i].replaceStop(this->RadialGradients[j].getStops());
                break;
            }
        }
    }

    for (int i = 0; i < this->RadialGradients.size(); ++i) {
        string temp = this->RadialGradients[i].getHref();
        temp.erase(0, 1);
        for (int j = 0; j < this->LinearGradients.size(); ++j) {
            if (temp == this->LinearGradients[j].getID()) {
                this->RadialGradients[i].replaceStop(this->LinearGradients[j].getStops());
                break;
            }
        }

        for (int j = 0; j < this->RadialGradients.size(); ++j) {
            if (temp == this->RadialGradients[j].getID()) {
                this->RadialGradients[i].replaceStop(this->RadialGradients[j].getStops());
                break;
            }
        }
    }
}