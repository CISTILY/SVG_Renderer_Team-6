#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "ShapeData.h"

#define ZOOMDIS 5
#define MOVEDIS 5

using namespace std;

const double infinity = INFINITY;
#define M_PI 3.14159265358979323846;

class EllipseShape : public sf::Shape {
private:
    sf::Vector2f m_radius;
public:

    // Constructor
    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0.f, 0.f)) : m_radius(radius)
    {
        update();
    }

    // Setters
    void setRadius(const sf::Vector2f&);

    // Getters
    const sf::Vector2f& getRadius() const;
    virtual size_t getPointCount() const;
    virtual sf::Vector2f getPoint(size_t) const;
};

class Line {
private:
    float a;
    float b;
    sf::Vector2f p1;
    sf::Vector2f p2;

public:
    // Getters
    sf::Vector2f getP1();
    sf::Vector2f getP2();

    float getA();
    float getB();

    // Create line from 2 points
    Line createLineFrom2Points(sf::Vector2f, sf::Vector2f);

    // Find intersection of 2 lines
    sf::Vector2f findIntersection(Line, Line);

    // Check relationship between points
    bool isStraightLine(sf::Vector2f, sf::Vector2f, sf::Vector2f);
    bool isQuadrilateral(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
    bool isTriangle(sf::Vector2f, sf::Vector2f, sf::Vector2f);
    bool isAppeared(sf::Vector2f, vector<sf::Vector2f>);

    // Update point
    void updatePoints(sf::Vector2f, vector<sf::Vector2f>&);
};

sf::Vector2f findCenterPoint(vector<sf::Vector2f>);
float findDelta(float, float, float);
sf::Vector2f findNewPoint(sf::Vector2f, sf::Vector2f, float);
vector<sf::Vector2f> resizePolygon(vector<sf::Vector2f>, float);

class SF_ShapeData {
private:
    sf::RectangleShape SF_rect;
    sf::CircleShape SF_cir;
    EllipseShape SF_ellip;
    sf::Text SF_text;
    sf::ConvexShape SF_polygon;
    sf::RectangleShape SF_line;
    vector<sf::ConvexShape> SF_fillPolylines;
    vector<sf::RectangleShape> SF_outlinePolylines;
public:
    // Constructor
    //SF_ShapeData();

    // Destructor
    //~SF_ShapeData();

    // Assign data to SF format shapes
    void buildSFShape(ShapeData, const sf::Font&);

    // Setters
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

    // Getters
    sf::RectangleShape getSF_rect();
    sf::CircleShape getSF_cir();
    EllipseShape getSF_ellip();
    sf::ConvexShape getSF_polygon();
    sf::RectangleShape getSF_line();
    vector<sf::ConvexShape> getSF_fillPolylines();
    vector<sf::RectangleShape> getSF_outlinePolylines();
    sf::Text getSF_text();
    sf::Vector2f getCenter(ShapeData);
    sf::Vector2f getCenterPolyline(PolylineSVG);

    // Mathematic operation
    void moving(float, float);
    void rotating(float);
    float length(float, float, float, float);
    float angle(float, float, float, float);
};

class Renderer {
private:
    int num;
    int type;
    float zoom;
    float zoomDis;
    bool allMove; // 0 for adjusting 1 object at once, 1 for all object of the same type
    vector<string> Type;
public:
    // Constructor
    Renderer();

    // Destructor
    ~Renderer() { }

    // Render shapes
    void Render(vector<SF_ShapeData>, vector<ShapeData>);
};