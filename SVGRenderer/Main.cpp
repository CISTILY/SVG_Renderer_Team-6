#include "rapidxml.hpp"
#include "Shape.h"
#include "SVG.h"
#include "SVGRender.h"
#include "Draw.h"
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

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Sample", sf::Style::Default, settings);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "Error";
    }

    sf::RectangleShape rect1 = createRectangle(25, 25, 800, 400, 2, sf::Color(200, 200, 200), sf::Color(0, 0, 0, round(255 * 0.01)));

    sf::RectangleShape rect2 = createRectangle(20, 20, 800, 400, 2, sf::Color(55, 55, 55), sf::Color(200, 100, 150, round(255 * 0.2)));

    sf::Text text1;
    text1.setFont(font);
    text1.setString("SVG Demo");
    text1.setPosition(0, 0);
    text1.setFillColor(sf::Color(0, 0, 255));
    text1.setCharacterSize(40);

    sf::RectangleShape rect3 = createRectangle(0, 0, 200, 50, 2, sf::Color(250, 0, 0), sf::Color(0, 255, 0, 0));

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Nguyen Van A");
    text2.setPosition(400, 400);
    text2.setFillColor(sf::Color(255, 0, 255));
    text2.setCharacterSize(30);

    sf::CircleShape circle1 = createCircle(200, 300, 100, sf::Color(255, 255, 0, round(255 * 0.5)), sf::Color(0, 255, 255, round(255 * 0.7)), 10);

    EllipseShape ellipse1 = createEllipse(400, 100, sf::Vector2f(100, 50), sf::Color(0, 255, 0, round(255 * 0.5)), sf::Color(255, 255, 0, round(255 * 0.7)), 3);

    const vector<sf::Vector2f> points4 =
    {
        {5, 37}, {15, 37}, {15, 32}, {25, 32}, {25, 37},
        {35, 37}, {35, 25}, {45, 25}, {45, 37}, {55, 37},
        {55, 17}, {65, 17}, {65, 37}, {75, 37}, {75, 10},
        {85, 10}, {85, 37}, {95, 37}, {95, 2}, {105, 2},
        {105, 37}, {115, 37}
    };
    vector<sf::ConvexShape> fillPolylines2 = createPolyline(points4, sf::Color(0, 255, 255, round(255 * 0.5)));
    vector<sf::RectangleShape> outlinePolylines2 = createOutlinePolyline(points4, sf::Color(255, 0, 0, round(255 * 0.7)), 2);

    sf::RectangleShape line1 = createLine(10, 30, 30, 10, sf::Color(0, 0, 255, round(255 * 0.7)), 5);
    sf::RectangleShape line2 = createLine(30, 30, 50, 10, sf::Color(0, 0, 255, round(255 * 0.8)), 10);
    sf::RectangleShape line3 = createLine(50, 30, 70, 10, sf::Color(0, 0, 255, round(255 * 0.9)), 15);
    sf::RectangleShape line4 = createLine(70, 30, 90, 10, sf::Color(0, 0, 255, round(255 * 0.9)), 15);
    sf::RectangleShape line5 = createLine(90, 30, 110, 10, sf::Color(0, 0, 255, round(255 * 1.0)), 20);

    const vector<sf::Vector2f> points1 =
    {
        {850, 75}, {958, 137}, {958, 262}, {850, 325}, {742, 262},
        {742, 137}
    };
    sf::ConvexShape polygon1 = createPolygon(6, sf::Color(153, 204, 255, round(255 * 0.5)), sf::Color(255, 0, 102, round(255 * 0.7)), 10, points1);

    const vector<sf::Vector2f> points2 =
    {
        {350, 75}, {379, 161}, {469, 161}, {397, 215}, {423, 301},
        {350, 250}, {277, 301}, {303, 215}, {231, 161}, {321, 161}
    };
    sf::ConvexShape polygon2 = createPolygon(10, sf::Color(255, 255, 0, round(255 * 0.6)), sf::Color(255, 0, 0, round(255 * 0.7)), 10, points2);

    const std::vector<sf::Vector2f> points3 =
    {
        {0, 40}, {40, 40}, {40, 80}, {80, 80}, {80, 120},
        {120, 120}, {120, 140}, {0, 40}
    };
    vector<sf::ConvexShape> fillPolylines1 = createPolyline(points3, sf::Color(0, 0, 0, round(255 * 0.5)));

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

        window.draw(rect1);
        window.draw(rect2);
        window.draw(text1);
        window.draw(rect3);
        window.draw(text2);
        window.draw(circle1);
        for (const sf::ConvexShape& filPolyline : fillPolylines2)
            window.draw(filPolyline);
        for (const sf::RectangleShape& outline : outlinePolylines2)
            window.draw(outline);
        window.draw(ellipse1);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.draw(line5);
        window.draw(polygon1);
        window.draw(polygon2);
        for (const sf::ConvexShape& filPolyline : fillPolylines1)
            window.draw(filPolyline);


        window.display();
    }
    return 0;
}
