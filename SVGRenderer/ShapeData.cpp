#include "ShapeData.h"

using namespace std;

ShapeData::ShapeData()
{
    //this->typeName = NULL;
    this->shapeSVG = NULL;
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

void ShapeData::readFile(xml_node<>* node, vector<ShapeData>& data, string filename, int& text_order)
{
    ShapeData temp;
    int j = 0;
  
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

        string nameSVGReader = reader.getNodeName();
        if (!reader.getOtherAttrName().empty() || !reader.getPropsAttrName().empty() || nameSVGReader == "g") {
            data.push_back(temp);
            data[j].buildAndPrintShapeInfo(reader, text_order);
            j++;
        }
        
        if (child != NULL)
        {
            if (nameSVGReader == "g")
            {
                GroupSVG* g = dynamic_cast<GroupSVG*>(data[j - 1].getShape());
                this->readFile(child, *(g->getG()), filename, text_order);
            }
        }
        node = node->next_sibling();
    }
    cout << endl;
}

void ShapeData::ReplaceProperties() {
    GroupSVG* g = dynamic_cast<GroupSVG*>(this->getShape());
    vector<ShapeData>* groupData = g->getG();
    for (int j = 0; j < (*groupData).size(); ++j) {
        if ((*groupData)[j].getShape()->getFlagStroke() == 0 && this->getShape()->getFlagStroke() == 1) {
            (*groupData)[j].setStroke(this->getShape()->getStroke());
        }
        if ((*groupData)[j].getShape()->getFlagStrokeWidth() == 0 && this->getShape()->getFlagStrokeWidth() == 1) {
            (*groupData)[j].setStrokeWidth(this->getShape()->getStrokeWidth());
        }
        if ((*groupData)[j].getShape()->getFlagStrokeOpacity() == 0 && this->getShape()->getFlagStrokeOpacity() == 1) {
            (*groupData)[j].setStrokeOpacity(this->getShape()->getStrokeOpacity());
        }
        if ((*groupData)[j].getShape()->getFlagFill() == 0 && this->getShape()->getFlagFill() == 1) {
            (*groupData)[j].setFill(this->getShape()->getFill());
        }
        if ((*groupData)[j].getShape()->getFlagFillOpacity() == 0 && this->getShape()->getFlagFillOpacity() == 1) {
            (*groupData)[j].setFillOpacity(this->getShape()->getFillOpacity());
        }
        if (this->getShape()->getFlagTransform() == 1) {
            (*groupData)[j].setTransform(this->getShape()->getTransform(), this->getShape()->getTranslate(), this->getShape()->getRotateAngle(), this->getShape()->getScalePoint(), this->getShape()->getOrderOfTransform());
        }

        cout << "After: ";
        (*groupData)[j].getShape()->print();
        cout << endl;

        string temp = (*groupData)[j].getTypeName();
        if (temp == "g")
            (*groupData)[j].ReplaceProperties();
        }
}

void ShapeData::setStroke(ColorSVG stroke) {
    this->shapeSVG->setStroke(stroke);
}

void ShapeData::setStrokeWidth(float strokeWidth) {
    this->shapeSVG->setStrokeWidth(strokeWidth);
}

void ShapeData::setStrokeOpacity(double strokeOpacity) {
    this->shapeSVG->setStrokeOpacity(strokeOpacity);
}

void ShapeData::setFill(ColorSVG fill) {
    this->shapeSVG->setFill(fill);
}

void ShapeData::setFillOpacity(double fillOpacity) {
    this->shapeSVG->setFillOpacity(fillOpacity);
}

void ShapeData::setTransform(vector<string> transform, vector<Point2D> translate, vector<float> rotateAngle, vector<Point2D> scalePoint, vector<int*> order_of_TranslateRotateScale) {
    for (int i = 0; i < transform.size(); ++i)
        this->shapeSVG->setTransform(transform[i], translate[i], rotateAngle[i], scalePoint[i], order_of_TranslateRotateScale[i]);
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
        Shape* group = new GroupSVG();
        group->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        this->shapeSVG = group;
        this->shapeSVG->print();
    }

    else if (temp == "path") {
        Shape* path = new PathSVG();
        path->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        path->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        this->shapeSVG = path;
        this->shapeSVG->print();
    }
    cout << endl;
}
