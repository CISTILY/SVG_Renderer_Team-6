#include "SVGRender.h"

using namespace std;

void Renderer::buildAndPrintShapeInfo(SVGReader reader, Properties props, int& i) {
    this->typeName = reader.getNodeName();
    string temp = this->typeName;
    if (temp == "rect") {
        this->rect.buildRect(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->rect.print();
    }
    else if (temp == "circle") {
        this->cir.buildCircle(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->cir.print();
    }

    else if (temp == "text") {
        this->text.buildText(reader.getOtherAttrName(), reader.getOtherAttrValue(), (reader.getContent()[i]), props);
        this->text.print();
        i++;
    }

    else if (temp == "line") {
        this->line.buildLine(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->line.print();
    }

    else if (temp == "ellipse") {
        this->ellip.buildEllipse(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->ellip.print();
    }

    else if (temp == "polygon") {
        this->polygon.buildPolygon(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->polygon.print();
    }

    else if (temp == "polyline") {
        this->polyline.buildPolyline(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->polyline.print();
    }

    cout << endl;
}