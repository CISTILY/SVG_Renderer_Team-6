#include "SVGRender.h"

using namespace std;

Renderer::Renderer()
{
    flagStroke = 0;
    this->typeName = NULL;

    cout << "Renderer::Default Constructor" << endl;
}

Renderer::~Renderer()
{
    cout << "Renderer::Destructor" << endl;
}

void Renderer::setSF_rect()
{
    this->SF_rect = createRectangle(this->rect);
}

void Renderer::setSF_cir()
{
    this->SF_cir = createCircle(this->cir);
}

void Renderer::setSF_ellip()
{
    this->SF_ellip = createEllipse(this->ellip);
}

void Renderer::setSF_polygon()
{
    this->SF_polygon = createPolygon(this->polygon);
}

void Renderer::setSF_line()
{
    this->SF_line = createLine(this->line);
}

void Renderer::setSF_Polylines()
{
    this->SF_fillPolylines = createPolyline(this->polyline);
    this->SF_outlinePolylines = createOutlinePolyline(this->polyline);
}

void Renderer::setSF_text(const sf::Font& font)
{
    this->SF_text = createText(this->text, font);
}

sf::RectangleShape Renderer::getSF_rect()
{
    return this->SF_rect;
}

sf::CircleShape Renderer::getSF_cir()
{
    return this->SF_cir;
}

EllipseShape Renderer::getSF_ellip()
{
    return this->SF_ellip;
}

//EllipseShape Renderer::getSF_ellip()
//{
//    return this->SF_ellip;
//}

sf::ConvexShape Renderer::getSF_polygon()
{
    return this->SF_polygon;
}

sf::RectangleShape Renderer::getSF_line()
{
    return this->SF_line;
}

vector<sf::ConvexShape> Renderer::getSF_fillPolylines()
{
    return this->SF_fillPolylines;
}

vector<sf::RectangleShape> Renderer::getSF_outlinePolylines()
{
    return this->SF_outlinePolylines;
}

sf::Text Renderer::getSF_text()
{
    return this->SF_text;
}

sf::Vector2f Renderer::getCenter() {
    string temp = this->typeName;
    if (temp == "rect") {
        return this->getSF_rect().getPosition();
    }
    else if (temp == "circle") {
        return this->getSF_cir().getPosition();
    }

    else if (temp == "text") {
        return this->getSF_text().getPosition();
    }

    else if (temp == "line") {
        return this->getSF_line().getPosition();
    }

    else if (temp == "ellipse") {
        return this->getSF_ellip().getPosition();
    }

    else if (temp == "polygon") {
        return this->getSF_polygon().getPosition();
    }

    else if (temp == "polyline") {
        return this->getPolyline().getCenter();
    }
}

void Renderer::moving(float x, float y) {
    this->SF_cir.move(x, y);
    this->SF_ellip.move(x, y);
    this->SF_line.move(x, y);
    this->SF_polygon.move(x, y);
    this->SF_rect.move(x, y);
    this->SF_text.move(x, y);
    for (sf::ConvexShape& fill : (this->SF_fillPolylines)) {
        fill.move(x, y);
    }
    for (sf::RectangleShape& rect : this->SF_outlinePolylines) {
        rect.move(x, y);
    }
}

void Renderer::rotating(float angle) {
    this->SF_cir.rotate(angle);
    this->SF_ellip.rotate(angle);
    this->SF_line.rotate(angle);
    this->SF_polygon.rotate(angle);
    this->SF_rect.rotate(angle);
    this->SF_text.rotate(angle);
    for (sf::ConvexShape& fill : (this->SF_fillPolylines)) {
        fill.rotate(angle);
    }
    for (sf::RectangleShape& rect : this->SF_outlinePolylines) {
        rect.rotate(angle);
    }
}

string Renderer::getTypeName()
{
    string temp = this->typeName;
    return temp;
}

bool Renderer::getFlagStroke()
{
    return this->flagStroke;
}

RectangleSVG Renderer::getRect()
{
    return this->rect;
}

CircleSVG Renderer::getCir()
{
    return this->cir;
}

EllipseSVG Renderer::getEllip()
{
    return this->ellip;
}

PolygonSVG Renderer::getPolygon()
{
    return this->polygon;
}

LineSVG Renderer::getLine()
{
    return this->line;
}

PolylineSVG Renderer::getPolyline()
{
    return this->polyline;
}

TextSVG Renderer::getText()
{
    return this->text;
}



void Renderer::buildAndPrintShapeInfo(SVGReader reader, Properties props, int& i, const sf::Font& font) {
    this->typeName = reader.getNodeName();
    string temp = this->typeName;
    if (temp == "rect") {
        this->rect.buildRect(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->rect.print();
        this->setSF_rect();
    }
    else if (temp == "circle") {
        this->cir.buildCircle(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->cir.print();
        this->setSF_cir();
    }

    else if (temp == "text") {
        this->text.buildText(reader.getOtherAttrName(), reader.getOtherAttrValue(), (reader.getContent()[i]), props);
        this->text.print();
        this->setSF_text(font);
        i++;
    }

    else if (temp == "line") {
        this->line.buildLine(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->line.print();
        this->setSF_line();
    }

    else if (temp == "ellipse") {
        this->ellip.buildEllipse(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->ellip.print();
        this->setSF_ellip();
    }

    else if (temp == "polygon") {
        this->polygon.buildPolygon(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->polygon.print();
        this->setSF_polygon();
    }

    else if (temp == "polyline") {
        this->polyline.buildPolyline(reader.getOtherAttrName(), reader.getOtherAttrValue(), props);
        this->polyline.print();
        this->setSF_Polylines();
    }

    if (props.getFlagStroke() == 1)
        this->flagStroke = 1;

    cout << endl;
}


//////////////////////////////////////////////

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

float Renderer::length(float x1, float y1, float x2, float y2)
{
    float length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return length;
}

float Renderer::angle(float x1, float y1, float x2, float y2)
{
    double angle = atan2(y2 - y1, x2 - x1) * 180 / M_PI;
    return (float)angle;
}

sf::Text Renderer::createText(TextSVG txt, const sf::Font& font)
{
    sf::Color fillColor(txt.getProperties().getFill().getRed(),
        txt.getProperties().getFill().getGreen(),
        txt.getProperties().getFill().getBlue());

    sf::Text text;
    text.setFont(font);
    text.setString((const string&)txt.getContent());
    text.setPosition(txt.getCoordinateX(), txt.getCoordinateY());
    text.setFillColor(fillColor);
    text.setCharacterSize(txt.getFont_size());
    text.setOrigin(txt.getFont_size() * 0.1, txt.getFont_size());

    return text;
}

sf::RectangleShape Renderer::createRectangle(RectangleSVG rectangle)
{
    sf::Color outlineColor(rectangle.getProperties().getStroke().getRed(),
        rectangle.getProperties().getStroke().getGreen(),
        rectangle.getProperties().getStroke().getBlue(),
        round(255 * rectangle.getProperties().getStrokeOpacity()));
    sf::Color fillColor(rectangle.getProperties().getFill().getRed(),
        rectangle.getProperties().getFill().getGreen(),
        rectangle.getProperties().getFill().getBlue(),
        round(255 * rectangle.getProperties().getFillOpacity()));

    sf::RectangleShape rect;
    rect.setPosition(rectangle.getCoordinateX(), rectangle.getCoordinateY());
    rect.setSize(sf::Vector2f(rectangle.getWidth(), rectangle.getHeight()));
    rect.setOutlineThickness(rectangle.getProperties().getStrokeWidth());
    rect.setOutlineColor(outlineColor);
    rect.setFillColor(fillColor);

    return rect;
}

sf::CircleShape Renderer::createCircle(CircleSVG cir)
{
    sf::Color outlineColor(cir.getProperties().getStroke().getRed(),
        cir.getProperties().getStroke().getGreen(),
        cir.getProperties().getStroke().getBlue(),
        round(255 * cir.getProperties().getStrokeOpacity()));
    sf::Color fillColor(cir.getProperties().getFill().getRed(),
        cir.getProperties().getFill().getGreen(),
        cir.getProperties().getFill().getBlue(),
        round(255 * cir.getProperties().getFillOpacity()));

    sf::CircleShape circle;
    circle.setPosition(cir.getCoordinateX(), cir.getCoordinateY());
    circle.setRadius(cir.getRadiusX());
    circle.setFillColor(fillColor);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(cir.getProperties().getStrokeWidth());
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    return circle;
}

EllipseShape Renderer::createEllipse(EllipseSVG ellip)
{
    sf::Vector2f radius(ellip.getRadiusX(), ellip.getRadiusY());

    sf::Color outlineColor(ellip.getProperties().getStroke().getRed(),
        ellip.getProperties().getStroke().getGreen(),
        ellip.getProperties().getStroke().getBlue(),
        round(255 * ellip.getProperties().getStrokeOpacity()));
    sf::Color fillColor(ellip.getProperties().getFill().getRed(),
        ellip.getProperties().getFill().getGreen(),
        ellip.getProperties().getFill().getBlue(),
        round(255 * ellip.getProperties().getFillOpacity()));

    EllipseShape ellipse;
    ellipse.setPosition(ellip.getCoordinateX(), ellip.getCoordinateY());
    ellipse.setRadius(radius + sf::Vector2f(ellip.getProperties().getStrokeWidth(), -ellip.getProperties().getStrokeWidth()));
    ellipse.setFillColor(fillColor);
    ellipse.setOutlineColor(outlineColor);
    ellipse.setOutlineThickness(ellip.getProperties().getStrokeWidth());
    ellipse.setOrigin(radius.x * 0.8f, radius.y / 0.8f);

    return ellipse;
}

sf::RectangleShape Renderer::createLine(LineSVG l)
{
    sf::Color fillColor(l.getProperties().getStroke().getRed(),
        l.getProperties().getStroke().getGreen(),
        l.getProperties().getStroke().getBlue(),
        round(255 * l.getProperties().getFillOpacity()));

    sf::RectangleShape line(sf::Vector2f(length(l.getCoordinateX(), l.getCoordinateY(), l.getEnd().getX(), l.getEnd().getY()), l.getProperties().getStrokeWidth()));

    line.setPosition(l.getCoordinateX(), l.getCoordinateY());
    line.setRotation(angle(l.getCoordinateX(), l.getCoordinateY(), l.getEnd().getX(), l.getEnd().getY()));
    line.setFillColor(fillColor);

    return line;
}

sf::RectangleShape Renderer::createLine(float x1, float y1, float x2, float y2, sf::Color fillColor, float strokeWidth)
{
    sf::RectangleShape line(sf::Vector2f(length(x1, y1, x2, y2), strokeWidth));
    line.setPosition(x1, y1);
    line.setRotation(angle(x1, y1, x2, y2));
    line.setFillColor(fillColor);
    return line;
}

sf::ConvexShape Renderer::createPolygon(PolygonSVG plg)
{
    sf::Color outlineColor(plg.getProperties().getStroke().getRed(),
        plg.getProperties().getStroke().getGreen(),
        plg.getProperties().getStroke().getBlue(),
        round(255 * plg.getProperties().getStrokeOpacity()));
    sf::Color fillColor(plg.getProperties().getFill().getRed(),
        plg.getProperties().getFill().getGreen(),
        plg.getProperties().getFill().getBlue(),
        round(255 * plg.getProperties().getFillOpacity()));

    vector<sf::Vector2f> points;
    for (auto& point : plg.getPoints()) {
        points.push_back(sf::Vector2f(static_cast<float>(point.getX()), static_cast<float>(point.getY())));
    }

    sf::ConvexShape polygon;
    polygon.setPointCount(plg.getPoints().size());
    polygon.setFillColor(fillColor);
    polygon.setOutlineColor(outlineColor);
    polygon.setOutlineThickness(plg.getProperties().getStrokeWidth());
    int i = 0;
    for (const sf::Vector2f& point : points)
    {
        polygon.setPoint(i++, point + sf::Vector2f(plg.getProperties().getStrokeWidth() * 1.5f, -plg.getProperties().getStrokeWidth()));
    }
    return polygon;
}

sf::ConvexShape Renderer::createPolygon(int pointCount, sf::Color fillColor, sf::Color outlineColor, float strokeWidth, vector<sf::Vector2f> points)
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

sf::Vector2f Line::getP1()
{
    return this->p1;
}

sf::Vector2f Line::getP2()
{
    return this->p2;
}

Line Line::createLineFrom2Points(sf::Vector2f A, sf::Vector2f B)
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

sf::Vector2f Line::findIntersection(Line l1, Line l2)
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

bool Line::isStraightLine(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
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

bool Line::isQuadrilateral(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4)
{
    if (isStraightLine(p1, p2, p3) || isStraightLine(p1, p2, p4) || isStraightLine(p2, p3, p4) || isStraightLine(p1, p3, p4))
        return false;
    else return true;
}

bool Line::isTriangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
    if (isStraightLine(p1, p2, p3))
        return false;
    else return true;
}

bool Line::isAppeared(sf::Vector2f point, vector<sf::Vector2f> points)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (point.x == points[i].x && point.y == points[i].y)
            return true;
    }
    return false;
}

void Line::updatePoints(sf::Vector2f point, vector<sf::Vector2f>& points)
{
    if (isAppeared(point, points))
    {
        return;
    }
    else points.push_back(point);
}


vector<sf::ConvexShape> Renderer::createPolyline(PolylineSVG pll)
{
    vector<sf::Vector2f> points;
    for (auto& point : pll.getPoints()) {
        points.push_back(sf::Vector2f(static_cast<float>(point.getX()), static_cast<float>(point.getY())));
    }
    points.push_back(points[0]);

    vector<Line> lines;
    Line lineFromStartToEnd;
    for (int i = 0; i < points.size() - 1; i++)
    {
        lineFromStartToEnd = lineFromStartToEnd.createLineFrom2Points(points[i], points[i + 1]);
        lines.push_back(lineFromStartToEnd);
    }

    vector<sf::Vector2f> tmpPoints;
    for (int i = 0; i < lines.size() - 1; i++)
    {
        sf::Vector2f p = lines[i].findIntersection(lineFromStartToEnd, lines[i]);
        if (p.x != infinity && p.y != infinity)
        {
            lines[i].updatePoints(lines[i].getP1(), tmpPoints);
            lines[i].updatePoints(p, tmpPoints);
            lines[i].updatePoints(lines[i].getP2(), tmpPoints);
        }
    }

    sf::Color fillColor(pll.getProperties().getFill().getRed(),
        pll.getProperties().getFill().getGreen(),
        pll.getProperties().getFill().getBlue(), round(255 * pll.getProperties().getFillOpacity()));

    int i = 0;
    int countPolygon = 0;
    vector<sf::ConvexShape> polygons;
    while (i < tmpPoints.size())
    {
        if (i + 1 < tmpPoints.size() && lineFromStartToEnd.isStraightLine(tmpPoints[i], lineFromStartToEnd.getP1(), lineFromStartToEnd.getP2()) && lineFromStartToEnd.isStraightLine(tmpPoints[i + 1], lineFromStartToEnd.getP1(), lineFromStartToEnd.getP2()))
        {
            i++;
        }
        else if (i + 3 < tmpPoints.size() && lineFromStartToEnd.isQuadrilateral(tmpPoints[i], tmpPoints[i + 1], tmpPoints[i + 2], tmpPoints[i + 3]))
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
        else if (i + 2 < tmpPoints.size() && lineFromStartToEnd.isTriangle(tmpPoints[i], tmpPoints[i + 1], tmpPoints[i + 2]))
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

vector<sf::RectangleShape> Renderer::createOutlinePolyline(PolylineSVG pll)
{
    sf::Color outlineColor(pll.getProperties().getStroke().getRed(),
        pll.getProperties().getStroke().getGreen(),
        pll.getProperties().getStroke().getBlue(),
        round(255 * pll.getProperties().getStrokeOpacity()));

    vector<sf::Vector2f> points;
    for (auto& point : pll.getPoints()) {
        points.push_back(sf::Vector2f(static_cast<float>(point.getX()), static_cast<float>(point.getY())));
    }
    points.push_back(points[0]);

    vector<Line> lines;
    Line line;
    for (int i = 0; i < points.size() - 1; i++)
    {
        line = line.createLineFrom2Points(points[i], points[i + 1]);
        lines.push_back(line);
    }

    ////////////
    Renderer temp;
    ////////////

    vector<sf::RectangleShape> outlinePolylines;
    sf::RectangleShape outline;
    for (int i = 0; i < lines.size(); i++)
    {
        outline = temp.createLine(lines[i].getP1().x, lines[i].getP1().y, lines[i].getP2().x, lines[i].getP2().y, outlineColor, pll.getProperties().getStrokeWidth());
        outlinePolylines.push_back(outline);
    }
    return outlinePolylines;
}
