#include "Renderer.h"

using namespace std;

ShapeData::ShapeData()
{

    //cout << "ShapeData::Default Constructor" << endl;
}

ShapeData::~ShapeData()
{
    //cout << "ShapeData::Destructor" << endl;
}

string ShapeData::getTypeName() {
    string temp = this->typeName;
    return temp;
}

Shape* ShapeData::getShape() {
    return this->shapeSVG;
}

void ShapeData::readFile(xml_node<>* node, vector<ShapeData>& data, string filename)
{
    ShapeData temp;
    static int j = 0, i = 0;
    while (node != NULL) {

        SVGReader reader;
        xml_node<>* child = node->first_node();
        reader.setNodeName(node->name());
        reader.readContent(filename); // read all the text content

        // Read attributes and build properties
        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {
            char* attributeName = Attr->name();
            char* attributeValue = Attr->value();
            reader.PropertiesBuilder(attributeName, attributeValue);
        }
        
        /*cout << reader.getNodeName() << " ";
        for (int j = 0; j < reader.getPropsAttrName().size(); ++j)
            cout << reader.getPropsAttrName()[j] << " " << reader.getPropsAttrValue()[j] << " ";

        for (int j = 0; j < reader.getOtherAttrName().size(); ++j)
            cout << reader.getOtherAttrName()[j] << " " << reader.getOtherAttrValue()[j] << " ";

        cout << endl;*/

        if (!reader.getOtherAttrName().empty() || !reader.getPropsAttrName().empty()) {
            data.push_back(temp);
            data[j].buildAndPrintShapeInfo(reader, i);
            j++;
        }
        
        if (child != NULL)
        {
            this->readFile(child, data, filename);
        }
        node = node->next_sibling();
    }
}

void ShapeData::ReplaceProperties(vector<ShapeData>& data) {
    vector<int> group;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].getTypeName() == "g")
            group.push_back(i);
    }
    group.push_back(data.size()-1);

    cout << data.size() << endl;
    for (int i = 0; i < group.size()-1; ++i) {
        for (int j = group[i]+1; j <= group[i + 1]; ++j) {
            cout << j << " ";
            if (data[group[i]].getShape()->getFlagStroke() != data[j].getShape()->getFlagStroke() && data[group[i]].getShape()->getFlagStroke() != 0) {
                data[j].setStroke(data[group[i]].getShape()->getStroke());
            }
            if (data[group[i]].getShape()->getFlagStrokeWidth() != data[j].getShape()->getFlagStrokeWidth() && data[group[i]].getShape()->getFlagStrokeWidth() != 0) {
                data[j].setStrokeWidth(data[group[i]].getShape()->getStrokeWidth());
            }
            if (data[group[i]].getShape()->getFlagStrokeOpacity() != data[j].getShape()->getFlagStrokeOpacity() && data[group[i]].getShape()->getFlagStrokeOpacity() != 0) {
                data[j].setStrokeOpacity(data[group[i]].getShape()->getStrokeOpacity()); 
            }
            if (data[group[i]].getShape()->getFlagFill() != data[j].getShape()->getFlagFill() && data[group[i]].getShape()->getFlagFill() != 0) {
                data[j].setFill(data[group[i]].getShape()->getFill());
            }
            if (data[group[i]].getShape()->getFlagFillOpacity() != data[j].getShape()->getFlagFillOpacity() && data[group[i]].getShape()->getFlagFillOpacity() != 0) {
                data[j].setFillOpacity(data[group[i]].getShape()->getFillOpacity());
            }
            if (data[group[i]].getShape()->getFlagTransform() == 1 && data[j].getShape()->getFlagTransform() == 0 || data[j].getShape()->getFlagTransform() == 1) {
                Point2D translate;
                translate.setX(data[group[i]].getShape()->getTranslateX());
                translate.setY(data[group[i]].getShape()->getTranslateY());
                data[j].setTransform(translate, rotate, scalePoint);
            }
            cout << "After: ";
            data[j].getShape()->print();
            cout << endl;
        }
    }
}

void ShapeData::setStroke(Color stroke) {
    this->shapeSVG->setStroke(stroke);
}

void ShapeData::setStrokeWidth(float strokeWidth) {
    this->shapeSVG->setStrokeWidth(strokeWidth);
}

void ShapeData::setStrokeOpacity(double strokeOpacity) {
    this->shapeSVG->setStrokeOpacity(strokeOpacity);
}

void ShapeData::setFill(Color fill) {
    this->shapeSVG->setFill(fill);
}

void ShapeData::setFillOpacity(double fillOpacity) {
    this->shapeSVG->setFillOpacity(fillOpacity);
}

void ShapeData::setTransform(Point2D translate, float rotate, Point2D scalepoint) {
    this->shapeSVG->setTransform(translate, rotate, scalepoint);
}

void ShapeData::buildAndPrintShapeInfo(SVGReader reader, int& i) {

    string temp = reader.getNodeName();
    this->typeName = reader.getNodeName();
    if (temp == "rect") {
        Shape* rect = new RectangleSVG();
        rect->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        rect->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = rect;
        this->shapeSVG->print();
    }
    else if (temp == "circle") {
        Shape* cir = new CircleSVG();
        cir->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        cir->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = cir;
        this->shapeSVG->print();
    }

    else if (temp == "text") {
        Shape* tempshape = new TextSVG();
        TextSVG* txt = dynamic_cast<TextSVG*> (tempshape);
        txt->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        txt->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        txt->setContent(reader.getContent()[i]);
        this->shapeSVG = txt;
        this->shapeSVG->print();
        i++;
    }

    else if (temp == "line") {
        Shape* line = new LineSVG();
        line->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        line->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = line;
        this->shapeSVG->print();
    }

    else if (temp == "ellipse") {
        Shape* ellipse = new EllipseSVG();
        ellipse->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        ellipse->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = ellipse;
        this->shapeSVG->print();
    }

    else if (temp == "polygon") {
        Shape* polygon = new PolygonSVG();
        polygon->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        polygon->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = polygon;
        this->shapeSVG->print();
    }

    else if (temp == "polyline") {
        Shape* polyline = new PolylineSVG();
        polyline->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        polyline->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = polyline;
        this->shapeSVG->print();
    }

    else if (temp == "g") {
        Shape* group = new RectangleSVG();
        group->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->shapeSVG = group;
        this->shapeSVG->print();
    }

    else if (temp == "path") {
        Shape* path = new Path();
        path->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        path->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = path;
        this->shapeSVG->print();
    }
    cout << endl;
}

//////////////////////////////////////////////

