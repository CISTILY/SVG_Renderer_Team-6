#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Shape.h"
#include "SVG.h"
#include "Rect.h"
#include "Circle.h"
#include "Polygon.h"
#include "Text.h"
#include "Line.h"
#include "Ellipse.h"
#include "Polyline.h"

using namespace std;

const double infinity = INFINITY;
const double M_PI = 3.14159265358979323846;

class EllipseShape : public sf::Shape
{
private:
    sf::Vector2f m_radius;
public:
    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f)) : m_radius(radius)
    {
        update();
    }
    void setRadius(const sf::Vector2f&);
    const sf::Vector2f& getRadius() const;
    virtual std::size_t getPointCount() const;
    virtual sf::Vector2f getPoint(std::size_t) const;
};

class Line
{
private:
    float a;
    float b;
    sf::Vector2f p1;
    sf::Vector2f p2;

public:
    sf::Vector2f getP1();
    sf::Vector2f getP2();

    Line createLineFrom2Points(sf::Vector2f, sf::Vector2f);
    sf::Vector2f findIntersection(Line, Line);
    bool isStraightLine(sf::Vector2f, sf::Vector2f, sf::Vector2f);
    bool isQuadrilateral(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
    bool isTriangle(sf::Vector2f, sf::Vector2f, sf::Vector2f);
    bool isAppeared(sf::Vector2f, vector<sf::Vector2f>);
    void updatePoints(sf::Vector2f, vector<sf::Vector2f>&);
};



class Renderer {
private:
    char* typeName;
    bool flagStroke;

    RectangleSVG rect;
    CircleSVG cir;
    EllipseSVG ellip;
    PolygonSVG polygon;
    LineSVG line;
    PolylineSVG polyline;
    TextSVG text;

public:
    string getTypeName();
    bool getFlagStroke();
    RectangleSVG getRect();
    CircleSVG getCir();
    EllipseSVG getEllip();
    PolygonSVG getPolygon();
    LineSVG getLine();
    PolylineSVG getPolyline();
    TextSVG getText();

    Renderer();
    ~Renderer();

    void buildAndPrintShapeInfo(SVGReader, Properties, int&, const sf::Font&);

private:
    sf::RectangleShape SF_rect;
    sf::CircleShape SF_cir;
    EllipseShape SF_ellip;
    sf::ConvexShape SF_polygon;
    sf::RectangleShape SF_line;
    vector<sf::ConvexShape> SF_fillPolylines;
    vector<sf::RectangleShape> SF_outlinePolylines;
    sf::Text SF_text;

public:
    void setSF_rect();
    void setSF_cir();
    void setSF_ellip();
    void setSF_polygon();
    void setSF_line();
    void setSF_Polylines();
    void setSF_text(const sf::Font&);

    sf::RectangleShape getSF_rect();
    sf::CircleShape getSF_cir();
    EllipseShape getSF_ellip();
    sf::ConvexShape getSF_polygon();
    sf::RectangleShape getSF_line();
    vector<sf::ConvexShape> getSF_fillPolylines();
    vector<sf::RectangleShape> getSF_outlinePolylines();
    sf::Text getSF_text();

    sf::Vector2f getCenter();
    void moving(float, float);
    void rotating(float);

    ////////////////////////////////////////
    float length(float, float, float, float);
    float angle(float, float, float, float);

    sf::Text createText(TextSVG, const sf::Font&);
    sf::RectangleShape createRectangle(RectangleSVG);
    sf::CircleShape createCircle(CircleSVG);
    EllipseShape createEllipse(EllipseSVG);
    sf::RectangleShape createLine(LineSVG);
    sf::RectangleShape createLine(float, float, float, float, sf::Color, float);
    sf::ConvexShape createPolygon(PolygonSVG);
    sf::ConvexShape createPolygon(int, sf::Color, sf::Color, float, vector<sf::Vector2f>);


    vector<sf::ConvexShape> createPolyline(PolylineSVG);
    vector<sf::RectangleShape> createOutlinePolyline(PolylineSVG);
};