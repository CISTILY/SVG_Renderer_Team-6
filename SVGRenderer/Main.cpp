#include "rapidxml.hpp"
#include "Shape.h"
#include "SVG.h"
#include "SVGRender.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace rapidxml;

int main() {

    int i = 0;
    // Read XML
    xml_document<> doc;
    xml_node<>* rootNode;

    // Read the xml file into a vector
    ifstream file("sample.svg");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer using the xml file parsing library into doc 
    doc.parse<0>(&buffer[0]);

    rootNode = doc.first_node("svg");
    xml_node<>* node = rootNode->first_node();

    // Parse SVG file and create shapes
    while (node != NULL) {
        Properties props;
        SVGReader reader;
        Renderer print;

        reader.setNodeName(node->name());
        reader.readContent();   // read all the text content

        // Read attributes and build properties
        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {

            char* attributeName = Attr->name();
            char* attributeValue = Attr->value();
            reader.PropertiesBuilder(attributeName, attributeValue, props);
        }
        print.buildAndPrintShapeInfo(reader, props, i);
        node = node->next_sibling();
    }

    return 0;
}
