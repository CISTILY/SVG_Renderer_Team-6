#include "Draw.h"

void EllipseShape::setRadius(const sf::Vector2f& radius)
{
    m_radius = radius;
    update();
}

const sf::Vector2f& EllipseShape::getRadius() const
{
    return m_radius;
}

size_t EllipseShape::getPointCount() const
{
    return 30;
}

sf::Vector2f EllipseShape::getPoint(std::size_t index) const
{
    static const float pi = 3.141592654f;

    float angle = index * 2 * pi / getPointCount() - pi / 2;
    float x = std::cos(angle) * m_radius.x;
    float y = std::sin(angle) * m_radius.y;

    return sf::Vector2f(m_radius.x + x, m_radius.y + y);
}

float length(float x1, float y1, float x2, float y2)
{
    float length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return length;
}

float angle(float x1, float y1, float x2, float y2)
{
    double angle = atan2(y2 - y1, x2 - x1) * 180 / M_PI;
    return (float)angle;
}

sf::RectangleShape createRectangle(float x, float y, float height, float width, float strokeWidth, sf::Color outlineColor, sf::Color fillColor)
{
    sf::RectangleShape rect;
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(height, width));
    rect.setOutlineThickness(strokeWidth);
    rect.setOutlineColor(outlineColor);
    rect.setFillColor(fillColor);
    return rect;
}

sf::CircleShape createCircle(float x, float y, float radius, sf::Color fillColor, sf::Color outlineColor, float strokeWidth)
{
    sf::CircleShape circle;
    circle.setPosition(x, y);
    circle.setRadius(radius);
    circle.setFillColor(fillColor);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(strokeWidth);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    return circle;
}

EllipseShape createEllipse(float x, float y, sf::Vector2f radius, sf::Color fillColor, sf::Color outlineColor, float strokeWidth)
{
    EllipseShape ellipse;
    ellipse.setPosition(x, y);
    ellipse.setRadius(radius);
    ellipse.setFillColor(fillColor);
    ellipse.setOutlineColor(outlineColor);
    ellipse.setOutlineThickness(strokeWidth);
    return ellipse;
}

sf::RectangleShape createLine(float x1, float y1, float x2, float y2, sf::Color fillColor, float strokeWidth)
{
    sf::RectangleShape line(sf::Vector2f(length(x1, y1, x2, y2), strokeWidth));
    line.setPosition(x1, y1);
    line.setRotation(angle(x1, y1, x2, y2));
    line.setFillColor(fillColor);
    return line;
}

sf::ConvexShape createPolygon(int pointCount, sf::Color fillColor, sf::Color outlineColor, float strokeWidth, vector<sf::Vector2f> points)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(pointCount);
    polygon.setFillColor(fillColor);
    polygon.setOutlineColor(outlineColor);
    polygon.setOutlineThickness(strokeWidth);
    int i = 0;
    for (const sf::Vector2f& point : points)
    {
        polygon.setPoint(i++, point);
    }
    return polygon;
}

// =======================================================================================

Line createLineFrom2Points(sf::Vector2f A, sf::Vector2f B)
{
    Line line;
    line.p1 = A;
    line.p2 = B;
    if (A.x != B.x && A.y != B.y)
    {
        line.a = (B.y - A.y) / (B.x - A.x);
        line.b = A.y - A.x * (B.y - A.y) / (B.x - A.x);
    }
    else if (A.x == B.x && A.y != B.y)
    {
        line.a = A.x;
        line.b = infinity;
    }
    else if (A.y == B.y && A.x != B.x)
    {
        line.a = infinity;
        line.b = A.y;
    }
    return line;
}

sf::Vector2f findIntersection(Line l1, Line l2)
{
    sf::Vector2f point(infinity, infinity);
    if (l1.a == l2.a && l1.b == l2.b) // trung nhau
        return point;
    if (l1.a == l2.a) // song song
        return point;
    if (l1.a != infinity && l1.b == infinity && l2.a != infinity && l2.b == infinity) // x = const
        return point;
    if (l1.a == infinity && l1.b != infinity && l2.a == infinity && l2.b != infinity) // y = const
        return point;
    if (l1.a != infinity && l1.b != infinity && l2.a != infinity && l2.b != infinity) // hai duong thang cat nhau
    {
        point.x = (l2.b - l1.b) / (l1.a - l2.a);
        point.y = l1.a * point.x + l1.b;
    }
    else if (l1.a != infinity && l1.b == infinity && l2.a == infinity && l2.b != infinity)
    {
        point.x = l1.a;
        point.y = l2.b;
    }
    else if (l1.a == infinity && l1.b != infinity && l2.a != infinity && l2.b == infinity)
    {
        point.x = l2.a;
        point.y = l1.b;
    }
    else if (l1.a != infinity && l1.b != infinity && l2.a != infinity && l2.b == infinity)
    {
        point.x = l2.a;
        point.y = l1.a * point.x + l1.b;
    }
    else if (l1.a != infinity && l1.b != infinity && l2.a == infinity && l2.b != infinity)
    {
        point.y = l2.b;
        point.x = (point.y - l1.b) / l1.a;
    }
    else if (l1.a != infinity && l1.b == infinity && l2.a != infinity && l2.b != infinity)
    {
        point.x = l1.a;
        point.y = l2.a * point.x + l2.b;
    }
    else if (l1.a != infinity && l1.b == infinity && l2.a != infinity && l2.b != infinity)
    {
        point.y = l1.b;
        point.x = (point.y - l2.b) / l2.a;
    }
    return point;
}

bool isStraightLine(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
    if (p1 == p2 || p2 == p3 || p1 == p3)
        return true;
    Line p1p2 = createLineFrom2Points(p1, p2);
    if (p1p2.a != infinity && p1p2.b != infinity)
    {
        if (p1p2.a * p3.x + p1p2.b - p3.y == 0)
            return true;
    }
    else if (p1p2.a != infinity && p1p2.b == infinity)
    {
        if (p1p2.a == p3.x)
            return true;
    }
    else if (p1p2.a == infinity && p1p2.b != infinity)
    {
        if (p1p2.b == p3.y)
            return true;
    }
    return false;
}

bool isQuadrilateral(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4)
{
    if (isStraightLine(p1, p2, p3) || isStraightLine(p1, p2, p4) || isStraightLine(p2, p3, p4) || isStraightLine(p1, p3, p4))
        return false;
    else return true;
}

bool isTriangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
    if (isStraightLine(p1, p2, p3))
        return false;
    else return true;
}

bool isAppeared(sf::Vector2f point, vector<sf::Vector2f> points)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (point.x == points[i].x && point.y == points[i].y)
            return true;
    }
    return false;
}

void updatePoints(sf::Vector2f point, vector<sf::Vector2f>& points)
{
    if (isAppeared(point, points))
    {
        return;
    }
    else points.push_back(point);
}

vector<sf::ConvexShape> createPolyline(vector<sf::Vector2f> points, sf::Color fillColor)
{
    vector<Line> lines;
    Line lineFromStart2End;
    for (int i = 0; i < points.size() - 1; i++)
    {
        lineFromStart2End = createLineFrom2Points(points[i], points[i + 1]);
        lines.push_back(lineFromStart2End);
    }

    vector<sf::Vector2f> tmpPoints;
    for (int i = 0; i < lines.size() - 1; i++)
    {
        sf::Vector2f p = findIntersection(lineFromStart2End, lines[i]);
        if (p.x != infinity && p.y != infinity)
        {
            updatePoints(lines[i].p1, tmpPoints);
            updatePoints(p, tmpPoints);
            updatePoints(lines[i].p2, tmpPoints);
        }
    }

    int i = 0;
    int countPolygon = 0;
    vector<sf::ConvexShape> polygons;
    while (i < tmpPoints.size())
    {
        if (i + 1 < tmpPoints.size() && isStraightLine(tmpPoints[i], lineFromStart2End.p1, lineFromStart2End.p2) && isStraightLine(tmpPoints[i + 1], lineFromStart2End.p1, lineFromStart2End.p2))
        {
            i++;
        }
        else if (i + 3 < tmpPoints.size() && isQuadrilateral(tmpPoints[i], tmpPoints[i + 1], tmpPoints[i + 2], tmpPoints[i + 3]))
        {
            vector<sf::Vector2f> tmpPoints1;
            tmpPoints1.push_back(tmpPoints[i]);
            tmpPoints1.push_back(tmpPoints[i + 1]);
            tmpPoints1.push_back(tmpPoints[i + 2]);
            tmpPoints1.push_back(tmpPoints[i + 3]);
            polygons.push_back(createPolygon(4, fillColor, fillColor, 0, tmpPoints1));
            i += 3;
            countPolygon++;
        }
        else if (i + 2 < tmpPoints.size() && isTriangle(tmpPoints[i], tmpPoints[i + 1], tmpPoints[i + 2]))
        {
            vector<sf::Vector2f> tmpPoints1;
            tmpPoints1.push_back(tmpPoints[i]);
            tmpPoints1.push_back(tmpPoints[i + 1]);
            tmpPoints1.push_back(tmpPoints[i + 2]);
            polygons.push_back(createPolygon(3, fillColor, fillColor, 0, tmpPoints1));
            i += 2;
            countPolygon++;
        }
        else i++;
    }
    return polygons;
}


vector<sf::RectangleShape> createOutlinePolyline(vector<sf::Vector2f> points, sf::Color outlineColor, float strokeWidth)
{
    vector<Line> lines;
    Line line;
    for (int i = 0; i < points.size() - 1; i++)
    {
        line = createLineFrom2Points(points[i], points[i + 1]);
        lines.push_back(line);
    }

    vector<sf::RectangleShape> outlinePolylines;
    sf::RectangleShape outline;
    for (int i = 0; i < lines.size(); i++)
    {
        outline = createLine(lines[i].p1.x, lines[i].p1.y, lines[i].p2.x, lines[i].p2.y, outlineColor, strokeWidth);
        outlinePolylines.push_back(outline);
    }
    return outlinePolylines;
}
