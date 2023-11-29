#include "rapidxml.hpp"
#include "Shape.h"
#include "SVG.h"
#include "Renderer.h"
#include "ShapeData.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace rapidxml;

int main() {
    Renderer pen;
    string filename = "sample3.svg";

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
    xml_node<>* node = rootNode->first_node();
    int i = 0, j = 0;
    SVGReader::setID(node);
    ShapeData temp;
    SF_ShapeData tempRen;
    vector<ShapeData> data;
    vector<SF_ShapeData> print;
    SVGReader a;

    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("times-new-roman.ttf"))
    {
        cout << "Error";
    }

    temp.readFile(node, data, a, filename);

    // Parse SVG file and create shapes
    //while (node != NULL) {
    //    SVGReader reader;

    //    reader.setNodeName(node->name());
    //    reader.readContent();   // read all the text content

    //    // Read attributes and build properties
    //    for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {

    //        char* attributeName = Attr->name();
    //        char* attributeValue = Attr->value();
    //        reader.PropertiesBuilder(attributeName, attributeValue);
    //    }

    //    // Create ShapeData by build and print shape information
    //    data.push_back(temp);
    //    print.push_back(tempRen);
    //    data[j].buildAndPrintShapeInfo(reader, i);
    //    print[j].buildSFShape(data[j], font);
    //    j++;

    //    node = node->next_sibling();
    //}
    //for (int i = 0; i < data.size(); ++i) {
    //    print.push_back(tempRen);
    //    print[i].buildSFShape(data[i], font);
    //}
    //// Render shape
    //pen.Render(print, data);
    return 0;
}
