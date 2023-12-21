#include "ShapeData.h"

using namespace std;

ShapeData* ShapeData::instance = NULL;
bool ShapeData::read = false;

ShapeData::ShapeData()
{
    //cout << "ShapeData::Default Constructor" << endl;
}

ShapeData* ShapeData::getInstance()
{
    if (instance == NULL)
        instance = new ShapeData;
       
    return instance;
}

ShapeData::~ShapeData()
{
    //cout << "ShapeData::Destructor" << endl;
}

vector<Shape*> ShapeData::getVectorShape() {
    return this->shapesSVG;
}

ScreenSVG ShapeData::getScreen()
{
    return this->screen;
}

void ShapeData::readSVG(string filename)
{
    if (read == false) 
    {
        // Read XML
        xml_document<> doc;
        xml_node<>* rootNode;
        // Read the xml file into a vector
        ifstream file(filename);
        vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        // Parse the buffer using the xml file parsing library into doc 
        doc.parse<0>(&buffer[0]);

        rootNode = doc.first_node("svg");
        this->screen.readScreen(rootNode);

        xml_node<>* node = rootNode->first_node();
        int text_order = 0;

        SVGReader::readContent(filename);
        this->readFile(node, this->shapesSVG, filename, text_order);

        for (int i = 0; i < this->shapesSVG.size(); ++i) 
        {
            string temp = this->shapesSVG[i]->getTypeName();
            if (temp == "g")
                this->ReplaceProperties(this->shapesSVG[i]);
        }

        read = true;
    }
}

void ShapeData::readFile(xml_node<>* node, vector<Shape*>& shapes, string filename, int& text_order)
{
    char type_name[] = "type-name";
    char* typeName = type_name;

    while (node != NULL) {

        SVGReader reader;
        xml_node<>* child = node->first_node();

        reader.setNodeName(node->name());
        reader.PropertiesBuilder(typeName, reader.getNodeName());

        // Read attributes and build properties
        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {
            char* attributeName = Attr->name();
            char* attributeValue = Attr->value();
            reader.PropertiesBuilder(attributeName, attributeValue);
        }

        string nameSVGReader = reader.getNodeName();
        if (!reader.getOtherAttrName().empty() || !reader.getPropsAttrName().empty() || nameSVGReader == "g") {
            this->buildAndPrintShapeInfo(reader, shapes, text_order);
        }

        if (child != NULL)
        {
            if (nameSVGReader == "g")
            {
                GroupSVG* g = dynamic_cast<GroupSVG*>(shapes[shapes.size() - 1]);
                this->readFile(child, *g->getVectorShapeAddress(), filename, text_order);
            }
        }
        node = node->next_sibling();
    }
    cout << endl;
}

void ShapeData::ReplaceProperties(Shape* shapeG) {
    GroupSVG* g = dynamic_cast<GroupSVG*>(shapeG);
    vector<Shape*>* groupData = g->getVectorShapeAddress();
    for (int j = 0; j < groupData->size(); ++j) {
        if ((*groupData)[j]->getFlagStroke() == 0 && g->getFlagStroke() == 1) {
            (*groupData)[j]->setStroke(g->getStroke());
        }
        if ((*groupData)[j]->getFlagStrokeWidth() == 0 && g->getFlagStrokeWidth() == 1) {
            (*groupData)[j]->setStrokeWidth(g->getStrokeWidth());
        }
        if ((*groupData)[j]->getFlagStrokeOpacity() == 0 && g->getFlagStrokeOpacity() == 1) {
            (*groupData)[j]->setStrokeOpacity(g->getStrokeOpacity());
        }
        if ((*groupData)[j]->getFlagFill() == 0 && g->getFlagFill() == 1) {
            (*groupData)[j]->setFill(g->getFill());
        }
        if ((*groupData)[j]->getFlagFillOpacity() == 0 && g->getFlagFillOpacity() == 1) {
            (*groupData)[j]->setFillOpacity(g->getFillOpacity());
        }
        if (g->getFlagTransform() == 1) {
            (*groupData)[j]->setTransform(g->getTransform(), g->getTranslate(), g->getRotateAngle(), g->getScalePoint(), g->getOrderOfTransform());
        }

        cout << "After: ";
        (*groupData)[j]->print();
        cout << endl;

        string temp = (*groupData)[j]->getTypeName();
        if (temp == "g")
            this->ReplaceProperties((*groupData)[j]);
        }
}

void ShapeData::buildAndPrintShapeInfo(SVGReader reader, vector<Shape*>& shapes, int& i) {

    string temp = reader.getNodeName();

    if (temp == "rect") {
        Shape* rect = new RectangleSVG();
        rect->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        rect->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(rect);
        shapes[shapes.size() - 1]->print();
    }
    else if (temp == "circle") {
        Shape* cir = new CircleSVG();
        cir->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        cir->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(cir);
        shapes[shapes.size() - 1]->print();
    }

    else if (temp == "text") {
        Shape* tempshape = new TextSVG();
        TextSVG* txt = dynamic_cast<TextSVG*> (tempshape);
        txt->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        txt->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        txt->setContent(reader.getContent()[i]);
        shapes.push_back(txt);
        shapes[shapes.size() - 1]->print();
        i++;
    }

    else if (temp == "line") {
        Shape* line = new LineSVG();
        line->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        line->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(line);
        shapes[shapes.size() - 1]->print();
    }

    else if (temp == "ellipse") {
        Shape* ellipse = new EllipseSVG();
        ellipse->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        ellipse->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(ellipse);
        shapes[shapes.size() - 1]->print();
    }

    else if (temp == "polygon") {
        Shape* polygon = new PolygonSVG();
        polygon->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        polygon->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(polygon);
        shapes[shapes.size() - 1]->print();
    }

    else if (temp == "polyline") {
        Shape* polyline = new PolylineSVG();
        polyline->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        polyline->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(polyline);
        shapes[shapes.size() - 1]->print();
    }

    else if (temp == "g") {
        Shape* group = new GroupSVG();
        group->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        shapes.push_back(group);
        shapes[shapes.size() - 1]->print();
    }

    else if (temp == "path") {
        Shape* path = new PathSVG();
        path->buildProperties(reader.getPropsAttrName(), reader.getPropsAttrValue());
        path->buildShape(reader.getOtherAttrName(), reader.getOtherAttrValue());
        shapes.push_back(path);
        shapes[shapes.size() - 1]->print();
    }
    cout << endl;
}
