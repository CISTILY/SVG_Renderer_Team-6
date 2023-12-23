#include "Gradient.h"

using namespace std;

Stop::Stop() {
    this->offset = 0;
    this->stop_opacity = 1;
}
Stop::~Stop() { }
void Stop::setOffset(float offset) {
	this->offset = offset;
}

void Stop::setColor(string s) {
	this->stop_color.setColor(s);
}

float Stop::getOffset() {
	return this->offset;
}

ColorSVG Stop::getStopColor() {
	return this->stop_color;
}

void Stop::buildStop(vector<char*> name, vector<char*> value) {
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

void Stop::printStop() {
    cout << "offset: " << this->offset 
        << "  stop color: "; 
    this->stop_color.print(); 
    cout << "  stop opacity: " << this->stop_opacity << endl;
}

LinearGradientSVG::LinearGradientSVG() {
    //cout << "LinearGradientSVG::Default Constructor" << endl;
}
LinearGradientSVG::~LinearGradientSVG() { }

Gradient::Gradient() {
    this->rotate = 0;
    for (int i = 0; i < 6; ++i)
        matrix[i] = 0;

    //cout << "Gradient::Default Constructor" << endl;
}
Gradient::~Gradient() { }

string Gradient::getHref() {
    return this->href;
}

string Gradient::getID() {
    return this->id;
}

vector<Stop> Gradient::getStops() {
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

void Gradient::addStop(Stop a) {
    this->stops.push_back(a);
}

void Gradient::replaceStop(vector<Stop> stops) {
    this->stops = stops;
}

void Gradient::setGradientTransform(string transform) {
    string value;
    int posStart = 0, posEnd = 0;
    if (transform.find("translate") != string::npos) {
        posStart = transform.find("translate");
        posEnd = transform.find(')', posStart);
        value = transform.substr(posStart + 10, posEnd - 10);
        Point2D* temp = new Point2D(value);
        this->translate = *temp;
        delete temp;
    }
    if (transform.find("rotate") != string::npos) {
        posStart = transform.find("rotate");
        posEnd = transform.find(')', posStart);
        value = transform.substr(posStart + 7, posEnd - 7);
        this->rotate = stof(value);
    }
    if (transform.find("scale") != string::npos) {
        posStart = transform.find("scale");
        posEnd = transform.find(')', posStart);
        value = transform.substr(posStart + 6, posEnd - 6);
        Point2D* temp = new Point2D(value);
        this->scale = *temp;
        delete temp;
    }
    if (transform.find("matrix") != string::npos) {
        posStart = transform.find("matrix");
        posEnd = transform.find(')', posStart);
        value = transform.substr(posStart + 7, posEnd - 7);
        
        string dup;

        for (int j = 0; j < 6; ++j)
        {
            int pos = value.find(' ');

            if (pos == string::npos)
                pos = value.find(',');

            dup = value.substr(0, pos);
            value.erase(0, pos + 1);
            this->matrix[j] = stof(dup);
        }
    }
}

void Gradient::setHref(string href)
{
    this->href = href.substr(1, href.length());
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
        else if (temp == "xlink:href")
        {
            string Href = value[i];
            this->setHref(Href);
        }
        else if (temp == "gradientUnits")
            this->gradientUnits = value[i];
        else if (temp == "spreadMethod")
            this->spreadMethod = value[i];
        else if (temp == "gradientTransform") {
            string transform = value[i];
            this->setGradientTransform(transform);
        }
    }
}

void LinearGradientSVG::print() {
    cout << "ID: " << this->id << "  GradientUnits: " << this->gradientUnits << "  SpreadMethod: " << this->spreadMethod << "  Href: " << this->href << "  ";
    cout << "Transform: ";  this->translate.print(); cout << " " << this->rotate << " "; this->scale.print(); cout << "  ";
    for (int i = 0; i < 6; ++i)
        cout << this->matrix[i] << " ";
    cout << endl;
    cout << "x1,y1: "; this->p1.print(); cout << "  x2,y2: ";  this->p2.print(); cout << endl;
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
        else if (temp == "xlink:href")
        {
            string Href = value[i];
            this->setHref(Href);
        }
        else if (temp == "gradientUnits")
            this->gradientUnits = value[i];
        else if (temp == "spreadMethod")
            this->spreadMethod = value[i];
        else if (temp == "gradientTransform") {
            string transform = value[i];
            this->setGradientTransform(transform);
        }
    }
}

void RadialGradientSVG::print() {
    cout << "ID: " << this->id << "  GradientUnits: " << this->gradientUnits << "  SpreadMethod: " << this->spreadMethod << "  Href: " << this->href << "  ";
    cout << "Transform: ";  this->translate.print(); cout << " " << this->rotate << " "; this->scale.print(); cout << "  ";
    for (int i = 0; i < 6; ++i)
        cout << this->matrix[i] << " ";
    cout << endl;
    cout << "cx,cy: "; this->p1.print(); cout << "  fx,fy: ";  this->p2.print(); cout << "  r: " << this->r << endl;
    for (int i = 0; i < this->stops.size(); ++i) {
        cout << "stop " << i + 1 << ": ";
        this->stops[i].printStop();
    }
}

void Def::readGradient(xml_node<>* node) {
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

void Def::buildDef(string typeName, vector<char*> name, vector<char*> value) {
    if (typeName == "linearGradient") {
        LinearGradientSVG linear;
        linear.buildGradient(name, value);
        this->LinearGradients.push_back(linear);
        this->previous = 1;
    }
    else if (typeName == "radialGradient") {
        RadialGradientSVG radial;
        radial.buildGradient(name, value);
        this->RadialGradients.push_back(radial);
        this->previous = 2;
    }
    else if (typeName == "stop") {
        Stop stop;
        stop.buildStop(name, value);
        if (this->previous == 1)
            this->LinearGradients[this->LinearGradients.size() - 1].addStop(stop);
        else if (this->previous == 2)
            this->RadialGradients[this->RadialGradients.size() - 1].addStop(stop);
    }
    
}

void Def::printGradient() {
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

void Def::performHref() {
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
