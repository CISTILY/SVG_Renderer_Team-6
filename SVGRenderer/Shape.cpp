#include "Shape.h"

using namespace std;

Shape::Shape() {
    this->flagStroke = 0;
    this->flagStrokeWidth = 0;
    this->flagStrokeOpacity = 0;
    this->flagFill = 0;
    this->flagFillOpacity = 0;
    this->flagTransform = 0;

    this->stroke_width = 0;
    this->stroke_opacity = 1;
    this->fill_opacity = 1;
    //cout << "Shape::Constructor" << endl;
}

Shape::~Shape() {
    //cout << "Shape::Destructor" << endl;
}

void Shape::buildProperties(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "stroke") {
            string stroke = value[i];
            if (stroke == "none") {
                this->flagStroke = 1;
                this->stroke.setColor("-1, -1, -1");
                
                this->flagStrokeOpacity = 1;
                this->stroke_opacity = 0;
                continue;
            }
            
            else {
                this->flagStroke = 1;
                this->stroke.setColor(stroke);
                
                if (this->flagStrokeWidth == 0)
                    this->stroke_width = 1;
            }
            
        }
        else if (temp == "stroke-width")
        {
            this->flagStrokeWidth = 1;
            this->stroke_width = stof(value[i]);
        }
        else if (temp == "stroke-opacity")
        {
            this->flagStrokeOpacity = 1;
            this->stroke_opacity = stof(value[i]);
        }
        else if (temp == "fill") {
            string fill = value[i];
            if (fill == "none") {
                this->flagFill = 1;
                this->fill.setColor("-1, -1, -1");

                this->flagFillOpacity = 1;
                this->fill_opacity = 0;
                continue;
            }

            else {
                this->flagFill = 1;
                this->fill.setColor(fill);
            }
        }
        else if (temp == "fill-opacity") {
            this->flagFillOpacity = 1;
            this->fill_opacity = stof(value[i]);
        }
            

        else if (temp == "transform") {
            this->flagTransform = 1;
            this->transform.push_back(value[i]);

            this->convertTransform(value[i]);
            this->findOrderTransform(value[i]);
        }
    }
}

void Shape::findOrderTransform(string transform)
{
    int* TranslateRotateScale = new int[3];

    int posTranslate = transform.find("translate");
    int posRotate = transform.find("rotate");
    int posScale = transform.find("scale");

    if (posTranslate == string::npos)
        posTranslate = transform.length();
    if (posRotate == string::npos)
        posRotate = transform.length();
    if (posScale == string::npos)
        posScale = transform.length();

    if (posTranslate <= posRotate && posTranslate <= posScale)
    {
        TranslateRotateScale[0] = 0;
        if (posRotate <= posScale)
        {
            TranslateRotateScale[1] = 1;
            TranslateRotateScale[2] = 2;
        }
        else
        {
            TranslateRotateScale[1] = 2;
            TranslateRotateScale[2] = 1;
        }
    }
    else if (posRotate <= posTranslate && posRotate <= posScale)
    {
        TranslateRotateScale[0] = 1;
        if (posTranslate <= posScale)
        {
            TranslateRotateScale[1] = 0;
            TranslateRotateScale[2] = 2;
        }
        else
        {
            TranslateRotateScale[1] = 2;
            TranslateRotateScale[2] = 0;
        }
    }
    else
    {
        TranslateRotateScale[0] = 2;
        if (posTranslate <= posRotate)
        {
            TranslateRotateScale[1] = 0;
            TranslateRotateScale[2] = 1;
        }
        else
        {
            TranslateRotateScale[1] = 1;
            TranslateRotateScale[2] = 0;
        }
    }

    this->order_of_TranslateRotateScale.push_back(TranslateRotateScale);
}

void Shape::convertTransform(string str) {
    this->translate.push_back(Point2D(0, 0));
    this->rotateAngle.push_back(0);
    this->scalePoint.push_back(Point2D(1, 1));

    string value;
    int posStart = 0, posEnd = 0;
    if (str.find("translate") != string::npos) {
        posStart = str.find("translate");
        posEnd = str.find(')', posStart);
        value = str.substr(posStart + 10, posEnd - 1 - 9);
        Point2D* temp = new Point2D(value);
        this->translate[this->translate.size() - 1] = *temp;
        delete temp;
    }
    if (str.find("rotate") != string::npos) {
        posStart = str.find("rotate");
        posEnd = str.find(')', posStart);
        value = str.substr(str.find("rotate") + 7, posEnd - 1 - 6);
        this->rotateAngle[this->rotateAngle.size() - 1] = stof(value);
    }
    if (str.find("scale") != string::npos) {
        posStart = str.find("scale");
        posEnd = str.find(')', posStart);
        value = str.substr(str.find("scale") + 6, posEnd - 1 - 5);
        Point2D* temp = new Point2D(value);
        this->scalePoint[this->scalePoint.size() - 1] = *temp;
        delete temp;
    }
}

void Shape::print() {
    cout << "Properties flag: ";
    cout << this->flagStroke << " " << this->flagStrokeWidth << " " << this->flagStrokeOpacity << " " << this->flagFill << " " << this->flagFillOpacity << " " << this->flagTransform;
    cout << "(fill-opacity: " << this->fill_opacity << "), (fill: ";
    this->fill.print();
    cout << "), (stroke: ";
    this->stroke.print();
    cout << "), (stroke-width: " << this->stroke_width << "), (stroke-opacity: " << this->stroke_opacity << ")" << endl;
    cout << "transform: ";
    for (int i = 0; i < this->transform.size(); ++i)
        cout << "No. " << i << this->transform[i] << " ";
}

void Shape::setStroke(ColorSVG stroke) {
    this->flagStroke = 1;
    this->stroke = stroke;
    
    if (this->flagStrokeWidth == 0 && stroke.getRed() != -1 && stroke.getGreen() != -1 && stroke.getBlue() != -1)
        this->stroke_width = 1;
}

void Shape::setStrokeWidth(float strokeWidth) {
    this->flagStrokeWidth = 1;
    this->stroke_width = strokeWidth;
}

void Shape::setStrokeOpacity(double strokeOpacity) {
    this->flagStrokeOpacity = 1;
    this->stroke_opacity = strokeOpacity;
}

void Shape::setFill(ColorSVG fill) {
    this->flagFill = 1;
    this->fill = fill;
}

void Shape::setFillOpacity(double fillOpacity) {
    this->flagFillOpacity = 1;
    this->fill_opacity = fillOpacity;
}

void Shape::setTransform(string transform, Point2D translate, float rotateAngle, Point2D scalePoint, int* order_of_TranslateRotateScale) {
    this->flagTransform = 1;
    this->transform.push_back(transform);
    this->translate.push_back(translate);
    this->rotateAngle.push_back(rotateAngle);
    this->scalePoint.push_back(scalePoint);
    this->order_of_TranslateRotateScale.push_back(order_of_TranslateRotateScale);
}

float Shape::getCoordinateX() {
    return this->coordinate.getX();
}

float Shape::getCoordinateY() {
    return this->coordinate.getY();
}

ColorSVG Shape::getStroke() {
    return this->stroke;
}

ColorSVG Shape::getFill() {
    return this->fill;
}

bool Shape::getFlagStroke()
{
    return this->flagStroke;
}

bool Shape::getFlagStrokeWidth() {
    return this->flagStrokeWidth;
}

bool Shape::getFlagStrokeOpacity() {
    return this->flagStrokeOpacity;
}

bool Shape::getFlagFill() {
    return this->flagFill;
}

bool Shape::getFlagFillOpacity() {
    return this->flagFillOpacity;
}

bool Shape::getFlagTransform() {
    return this->flagTransform;
}


float Shape::getStrokeWidth() {
    return this->stroke_width;
}

double Shape::getFillOpacity() {
    return this->fill_opacity;
}

double Shape::getStrokeOpacity() {
    return this->stroke_opacity;
}

vector<string> Shape::getTransform() {
    return this->transform;
}

vector<Point2D> Shape::getTranslate()
{
    return this->translate;
}

vector<float> Shape::getRotateAngle()
{
    return this->rotateAngle;
}

vector<Point2D> Shape::getScalePoint()
{
    return this->scalePoint;
}

vector<int*> Shape::getOrderOfTransform()
{
    return this->order_of_TranslateRotateScale;
}