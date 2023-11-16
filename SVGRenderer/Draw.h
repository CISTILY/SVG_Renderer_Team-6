#ifndef SVG_H_
#define SCG_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

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

float length(float, float, float, float);
float angle(float, float, float, float);

sf::RectangleShape createRectangle(float, float, float, float, float, sf::Color, sf::Color);
sf::CircleShape createCircle(float, float, float, sf::Color, sf::Color, float);
EllipseShape createEllipse(float, float, sf::Vector2f, sf::Color, sf::Color, float);
sf::RectangleShape createLine(float, float, float, float, sf::Color, float);
sf::ConvexShape createPolygon(int, sf::Color, sf::Color, float, vector<sf::Vector2f>);

struct Line
{
    float a;
    float b;
    sf::Vector2f p1;
    sf::Vector2f p2;
};

Line createLineFrom2Points(sf::Vector2f, sf::Vector2f);
sf::Vector2f findIntersection(Line, Line);
bool isStraightLine(sf::Vector2f, sf::Vector2f, sf::Vector2f);
bool isQuadrilateral(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);
bool isTriangle(sf::Vector2f, sf::Vector2f, sf::Vector2f);
bool isAppeared(sf::Vector2f, vector<sf::Vector2f>);
void updatePoints(sf::Vector2f, vector<sf::Vector2f>&);
vector<sf::ConvexShape> createPolyline(vector<sf::Vector2f>, sf::Color);
vector<sf::RectangleShape> createOutlinePolyline(vector<sf::Vector2f>, sf::Color, float);

#endif // !SVG_H_


