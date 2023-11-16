#include "rapidxml.hpp"
#include "Shape.h"
#include "SVG.h"
#include "SVGRender.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace rapidxml;

int main() {
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

    int i = 0, j = 0;
    Renderer temp;
    vector<Renderer> print;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Sample", sf::Style::Default, settings);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error";
    }

    while (node != NULL) {
        Properties props;
        SVGReader reader;

        reader.setNodeName(node->name());
        reader.readContent();

        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {

            char* attributeName = Attr->name();
            char* attributeValue = Attr->value();
            reader.PropertiesBuilder(attributeName, attributeValue, props);
        }
        print.push_back(temp);
        print[j].printShapeInfo(reader, props, i, font);
        j++;
        node = node->next_sibling();
    }

    //int flag = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < print.size(); ++i)
        {
            if (print[i].getTypeName() == "rect")
                window.draw(print[i].getSF_rect());
            if (print[i].getTypeName() == "circle")
                window.draw(print[i].getSF_cir());
            if (print[i].getTypeName() == "ellipse")
                window.draw(print[i].getSF_ellip());
            if (print[i].getTypeName() == "line")
                window.draw(print[i].getSF_line());
            if (print[i].getTypeName() == "polygon")
                window.draw(print[i].getSF_polygon());
            if (print[i].getTypeName() == "text")
                window.draw(print[i].getSF_text());
            if (print[i].getTypeName() == "polyline")
            {
                for (const sf::ConvexShape& filPolyline : print[i].getSF_fillPolylines())
                    window.draw(filPolyline);
                if (print[i].getFlagStroke())
                {
                    for (const sf::RectangleShape& outline : print[i].getSF_outlinePolylines())
                        window.draw(outline);
                }
            }
        }

        /*
        if (flag == 1000)
        {
            cout << "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" << endl;
            for (int i = 0; i < print.size(); ++i)
                if (print[i].getTypeName() == "rect")
                {
                    cout << i << ": " << print[i].getSF_rect().getPosition().x << " " << print[i].getSF_rect().getPosition().y << endl;
                    print[i].moving();
                    // print[i].getSF_rect().setPosition(print[i].getSF_rect().getPosition().x + 1, (print[i].getSF_rect().getPosition().y));
                    cout << i << ": " << print[i].getSF_rect().getPosition().x << " " << print[i].getSF_rect().getPosition().y << endl;
                }

            flag = 0;
        }
        ++flag;
        */

        window.display();
    }

    return 0;
}
