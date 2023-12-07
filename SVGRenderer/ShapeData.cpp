#include "ShapeData.h"

using namespace std;

ShapeData::ShapeData()
{
    this->typeName = NULL;
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

void ShapeData::readFile(xml_node<>* node, vector<ShapeData>& data, string filename)
{
    ShapeData temp;
    int j = 0;
    static int i = 0;
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

        string nameSVGReader = reader.getNodeName();
        if (!reader.getOtherAttrName().empty() || !reader.getPropsAttrName().empty() || nameSVGReader == "g") {
            data.push_back(temp);
            data[j].buildAndPrintShapeInfo(reader, i);
            j++;
        }
        
        if (child != NULL)
        {
            if (nameSVGReader == "g")
            {
                //vector<ShapeData> *childData = &(data[j - 1].getShape()->getG());
                //this->readFile(child, *childData, filename);
                
                //Khong hieu tai sao class group bien g phai la pointer chu khong dc bien thuong 
                this->readFile(child, *(data[j - 1].getShape()->getG()), filename);
            }
        }
        node = node->next_sibling();
    }
    cout << endl;
}

/*
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
                data[j].setTransform(data[group[i]].getShape()->getTransform());
            }
            cout << "After: ";
            data[j].getShape()->print();
            cout << endl;
        }
    }
}
*/


void ShapeData::ReplaceProperties() {
    
    //for (int i = 0; i < data.size(); ++i) {
    //    if (data[i].getTypeName() == "g")
    //        ReplaceProperties(*data[i].getShape()->getG());
    //}
    
    vector<ShapeData>* groupData = this->getShape()->getG();
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
            (*groupData)[j].setTransform(this->getShape()->getTransform());
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

void ShapeData::setTransform(vector<string> transform) {
    for (int i = 0; i < transform.size(); ++i)
        this->shapeSVG->setTransform(transform[i]);
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

//////////////////////////////////////////////

