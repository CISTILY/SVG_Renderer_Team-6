#include "Renderer.h"

using namespace std;

ShapeData::ShapeData()
{
    flagStroke = 0;
    this->typeName = NULL;

    cout << "ShapeData::Default Constructor" << endl;
}

ShapeData::~ShapeData()
{
    cout << "ShapeData::Destructor" << endl;
}

string ShapeData::getTypeName()
{
    string temp = this->typeName;
    return temp;
}

bool ShapeData::getFlagStroke()
{
    return this->flagStroke;
}

RectangleSVG ShapeData::getRect()
{
    return this->rect;
}

CircleSVG ShapeData::getCir()
{
    return this->cir;
}

EllipseSVG ShapeData::getEllip()
{
    return this->ellip;
}

PolygonSVG ShapeData::getPolygon()
{
    return this->polygon;
}

LineSVG ShapeData::getLine()
{
    return this->line;
}

PolylineSVG ShapeData::getPolyline()
{
    return this->polyline;
}

TextSVG ShapeData::getText()
{
    return this->text;
}

void ShapeData::buildAndPrintShapeInfo(SVGReader reader, int& i) {
    this->typeName = reader.getNodeName();
    string temp = this->typeName;
    if (temp == "rect") {
        this->rect.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->rect.buildRect(reader.getOtherAttrName(), reader.getOtherAttrValue());

        if (this->rect.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->rect.print();
    }
    else if (temp == "circle") {
        this->cir.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->cir.buildCircle(reader.getOtherAttrName(), reader.getOtherAttrValue());

        if (this->cir.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->cir.print();
    }

    else if (temp == "text") {
        this->text.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->text.buildText(reader.getOtherAttrName(), reader.getOtherAttrValue(), (reader.getContent()[i]));

        if (this->text.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->text.print();
        i++;
    }

    else if (temp == "line") {
        this->line.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->line.buildLine(reader.getOtherAttrName(), reader.getOtherAttrValue());

        if (this->line.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->line.print();
    }

    else if (temp == "ellipse") {
        this->ellip.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->ellip.buildEllipse(reader.getOtherAttrName(), reader.getOtherAttrValue());

        if (this->ellip.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->ellip.print();
    }

    else if (temp == "polygon") {
        this->polygon.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->polygon.buildPolygon(reader.getOtherAttrName(), reader.getOtherAttrValue());

        if (this->polygon.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->polygon.print();
    }

    else if (temp == "polyline") {
        this->polyline.buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->polyline.buildPolyline(reader.getOtherAttrName(), reader.getOtherAttrValue());

        if (this->polyline.getFlagStroke() == 1)
            this->flagStroke = 1;

        this->polyline.print();
    }

    cout << endl;
}

//////////////////////////////////////////////

