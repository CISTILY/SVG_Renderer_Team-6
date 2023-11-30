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

    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("times-new-roman.ttf"))
    {
        cout << "Error";
    }

    temp.readFile(node, data, filename);
    temp.ReplaceProperties(data);

    for (int i = 0; i < data.size(); ++i) {
        print.push_back(tempRen);
        print[i].buildSFShape(data[i], font);
    }
    // Render shape
    pen.Render(print, data);
    return 0;
}
