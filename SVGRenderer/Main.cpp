#include "rapidxml.hpp"
#include "Shape.h"
#include "SVG.h"
#include "SVGRender.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

// Constants for zoom and move distances
#define ZOOMDIS 5
#define MOVEDIS 5

using namespace std;
using namespace rapidxml;

// Vector to store different types of SVG shapes
vector<string> Type = { "rect", "circle", "ellipse" , "line", "polygon", "text", "polyline" };

int main() {
    int num = 0;
    int type = 0;
    float zoom = 1.0;
    float zoomDis = 5;
    bool allMove = 0; // 0 for adjusting 1 object at once, 1 for all object of the same type

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

    // Set up SFML window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1000, 500), "Sample", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 1000, 500));
    window.setView(view);

    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("times-new-roman.ttf"))
    {
        cout << "Error";
    }


    // Parse SVG file and create shapes
    while (node != NULL) {
        Properties props;
        SVGReader reader;

        reader.setNodeName(node->name());
        reader.readContent();   // read all the text content

        // Read attributes and build properties
        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {

            char* attributeName = Attr->name();
            char* attributeValue = Attr->value();
            reader.PropertiesBuilder(attributeName, attributeValue, props);
        }

        // Create Renderer by build and print shape information
        print.push_back(temp);
        print[j].buildAndPrintShapeInfo(reader, props, i, font);
        j++;

        node = node->next_sibling();
    }

    // Draw program loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Event handling for closing the window, resizing, and mouse wheel zooming
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized) // update the view to the new size of the window
            {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0) {
                    view.zoom(0.9f);
                    zoomDis = ZOOMDIS * (view.getSize().x / 1000);
                    window.setView(view);
                }
                else {
                    view.zoom(1.1f);
                    zoomDis = ZOOMDIS * (view.getSize().x / 1000);
                    window.setView(view);
                }
            }

            // Event handling for key presses
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::M) {
                    allMove = 0;
                    num++;
                    if (num == print.size()) {
                        num = 0;
                    }
                    cout << print[num].getTypeName() << endl;
                    view.setCenter(print[num].getCenter());
                    window.setView(view);
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::N) {
                    allMove = 1;
                    type++;
                    if (type == Type.size()) {
                        type = 0;
                    }
                    cout << Type[type] << endl;
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw shapes using SFML
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

        // Handle keyboard input for various actions (moving, zooming, rotating)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            view.reset(sf::FloatRect(0, 0, 1000, 500));
            window.setView(window.getDefaultView());
            zoomDis = 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            view.move(sf::Vector2f(-zoomDis, 0));
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            view.move(sf::Vector2f(zoomDis, 0));
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            view.move(sf::Vector2f(0, zoomDis));
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            view.move(sf::Vector2f(0, -zoomDis));
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            view.rotate(0.1f);
            window.setView(view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (allMove == 0)
                print[num].moving(MOVEDIS, 0);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (print[l].getTypeName() == Type[type])
                        print[l].moving(MOVEDIS, 0);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (allMove == 0)
                print[num].moving(-MOVEDIS, 0);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (print[l].getTypeName() == Type[type])
                        print[l].moving(-MOVEDIS, 0);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (allMove == 0)
                print[num].moving(0, -MOVEDIS);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (print[l].getTypeName() == Type[type])
                        print[l].moving(0, -MOVEDIS);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (allMove == 0)
                print[num].moving(0, MOVEDIS);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (print[l].getTypeName() == Type[type])
                        print[l].moving(0, MOVEDIS);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (allMove == 0)
                print[num].rotating(5);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (print[l].getTypeName() == Type[type])
                        print[l].rotating(5);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (allMove == 0)
                print[num].rotating(-5);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (print[l].getTypeName() == Type[type])
                        print[l].rotating(-5);
                }
            }
        }

        window.display();
    }

    return 0;
}
