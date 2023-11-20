#include "Renderer.h"

using namespace std;

SF_ShapeData::SF_ShapeData() {
    cout << "SF_ShapeData::Default Constructor" << endl;
}

SF_ShapeData::~SF_ShapeData() {
    cout << "SF_ShapeData::Destructor" << endl;
}

void SF_ShapeData::buildSFShape(ShapeData data, const sf::Font& font) {
    if (data.getTypeName() == "rect") {
        this->SF_rect = createRectangle(data.getRect());
    }

    else if (data.getTypeName() == "circle") {
        this->SF_cir = createCircle(data.getCir());
    }

    else if (data.getTypeName() == "text") {
        this->SF_text = createText(data.getText(), font);
    }

    else if (data.getTypeName() == "line") {
        this->SF_line = createLine(data.getLine());;
    }

    else if (data.getTypeName() == "ellipse") {
        this->SF_ellip = createEllipse(data.getEllip());
    }

    else if (data.getTypeName() == "polygon") {
        this->SF_polygon = createPolygon(data.getPolygon());
    }

    else if (data.getTypeName() == "polyline") {
        this->SF_fillPolylines = createPolyline(data.getPolyline());
        this->SF_outlinePolylines = createOutlinePolyline(data.getPolyline());
    }
}

sf::RectangleShape SF_ShapeData::getSF_rect()
{
    return this->SF_rect;
}

sf::CircleShape SF_ShapeData::getSF_cir()
{
    return this->SF_cir;
}

EllipseShape SF_ShapeData::getSF_ellip()
{
    return this->SF_ellip;
}

//EllipseShape SF_ShapeData::getSF_ellip()
//{
//    return this->SF_ellip;
//}

sf::ConvexShape SF_ShapeData::getSF_polygon()
{
    return this->SF_polygon;
}

sf::RectangleShape SF_ShapeData::getSF_line()
{
    return this->SF_line;
}

vector<sf::ConvexShape> SF_ShapeData::getSF_fillPolylines()
{
    return this->SF_fillPolylines;
}

vector<sf::RectangleShape> SF_ShapeData::getSF_outlinePolylines()
{
    return this->SF_outlinePolylines;
}

sf::Text SF_ShapeData::getSF_text()
{
    return this->SF_text;
}

sf::Vector2f SF_ShapeData::getCenter(ShapeData data) {
    string temp = data.getTypeName();
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

        return this->getCenterPolyline(data.getPolyline());
    }
}

sf::Vector2f SF_ShapeData::getCenterPolyline(PolylineSVG polyline) {
    sf::Vector2f p1 = sf::Vector2f(static_cast<float>(polyline.getPoints()[0].getX()), static_cast<float>(polyline.getPoints()[0].getY())),
        p2 = sf::Vector2f(static_cast<float>(polyline.getPoints()[0].getX()), static_cast<float>(polyline.getPoints()[0].getY())), p;
    for (Point2D a : polyline.getPoints()) {
        if (a.getX() < p1.x) {
            p1.x = a.getX();
        }
        if (a.getY() < p1.y) {
            p1.y = a.getY();
        }
        if (a.getX() > p2.x) {
            p2.x = a.getX();
        }
        if (a.getY() < p2.y) {
            p2.y = a.getY();
        }
    }
    return sf::Vector2f(p1.x + (p2.x - p1.x) / 2.0, p1.y + (p2.y - p1.y) / 2);
}

void SF_ShapeData::moving(float x, float y) {
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

void SF_ShapeData::rotating(float angle) {
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

float SF_ShapeData::length(float x1, float y1, float x2, float y2)
{
    float length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return length;
}

float SF_ShapeData::angle(float x1, float y1, float x2, float y2)
{
    double angle = atan2(y2 - y1, x2 - x1) * 180 / M_PI;
    return (float)angle;
}

sf::Text SF_ShapeData::createText(TextSVG txt, const sf::Font& font)
{
    sf::Color fillColor(txt.getFill().getRed(),
        txt.getFill().getGreen(),
        txt.getFill().getBlue());

    sf::Text text;
    text.setFont(font);
    text.setString((const string&)txt.getContent());
    text.setPosition(txt.getCoordinateX(), txt.getCoordinateY());
    text.setFillColor(fillColor);
    text.setCharacterSize(txt.getFont_size());
    text.setOrigin(txt.getFont_size() * 0.1, txt.getFont_size());

    return text;
}

sf::RectangleShape SF_ShapeData::createRectangle(RectangleSVG rectangle)
{
    sf::Color outlineColor(rectangle.getStroke().getRed(),
        rectangle.getStroke().getGreen(),
        rectangle.getStroke().getBlue(),
        round(255 * rectangle.getStrokeOpacity()));
    sf::Color fillColor(rectangle.getFill().getRed(),
        rectangle.getFill().getGreen(),
        rectangle.getFill().getBlue(),
        round(255 * rectangle.getFillOpacity()));

    sf::RectangleShape rect;
    rect.setPosition(rectangle.getCoordinateX(), rectangle.getCoordinateY());
    rect.setSize(sf::Vector2f(rectangle.getWidth(), rectangle.getHeight()));
    rect.setOutlineThickness(rectangle.getStrokeWidth());
    rect.setOutlineColor(outlineColor);
    rect.setFillColor(fillColor);

    return rect;
}

sf::CircleShape SF_ShapeData::createCircle(CircleSVG cir)
{
    sf::Color outlineColor(cir.getStroke().getRed(),
        cir.getStroke().getGreen(),
        cir.getStroke().getBlue(),
        round(255 * cir.getStrokeOpacity()));
    sf::Color fillColor(cir.getFill().getRed(),
        cir.getFill().getGreen(),
        cir.getFill().getBlue(),
        round(255 * cir.getFillOpacity()));

    sf::CircleShape circle;
    circle.setPosition(cir.getCoordinateX(), cir.getCoordinateY());
    circle.setRadius(cir.getRadiusX());
    circle.setFillColor(fillColor);
    circle.setOutlineColor(outlineColor);
    circle.setOutlineThickness(cir.getStrokeWidth());
    circle.setOrigin(circle.getRadius(), circle.getRadius());

    return circle;
}

EllipseShape SF_ShapeData::createEllipse(EllipseSVG ellip)
{
    sf::Vector2f radius(ellip.getRadiusX(), ellip.getRadiusY());

    sf::Color outlineColor(ellip.getStroke().getRed(),
        ellip.getStroke().getGreen(),
        ellip.getStroke().getBlue(),
        round(255 * ellip.getStrokeOpacity()));
    sf::Color fillColor(ellip.getFill().getRed(),
        ellip.getFill().getGreen(),
        ellip.getFill().getBlue(),
        round(255 * ellip.getFillOpacity()));

    EllipseShape ellipse;
    ellipse.setPosition(ellip.getCoordinateX(), ellip.getCoordinateY());
    ellipse.setRadius(radius + sf::Vector2f(ellip.getStrokeWidth(), -ellip.getStrokeWidth()));
    ellipse.setFillColor(fillColor);
    ellipse.setOutlineColor(outlineColor);
    ellipse.setOutlineThickness(ellip.getStrokeWidth());
    ellipse.setOrigin(radius.x * 0.8f, radius.y / 0.8f);

    return ellipse;
}

sf::RectangleShape SF_ShapeData::createLine(LineSVG l)
{
    sf::Color fillColor(l.getStroke().getRed(),
        l.getStroke().getGreen(),
        l.getStroke().getBlue(),
        round(255 * l.getFillOpacity()));

    sf::RectangleShape line(sf::Vector2f(length(l.getCoordinateX(), l.getCoordinateY(), l.getEnd().getX(), l.getEnd().getY()), l.getStrokeWidth()));

    line.setPosition(l.getCoordinateX(), l.getCoordinateY());
    line.setRotation(angle(l.getCoordinateX(), l.getCoordinateY(), l.getEnd().getX(), l.getEnd().getY()));
    line.setFillColor(fillColor);

    return line;
}

sf::RectangleShape SF_ShapeData::createLine(float x1, float y1, float x2, float y2, sf::Color fillColor, float strokeWidth)
{
    sf::RectangleShape line(sf::Vector2f(length(x1, y1, x2, y2), strokeWidth));
    line.setPosition(x1, y1);
    line.setRotation(angle(x1, y1, x2, y2));
    line.setFillColor(fillColor);
    return line;
}

sf::ConvexShape SF_ShapeData::createPolygon(PolygonSVG plg)
{
    sf::Color outlineColor(plg.getStroke().getRed(),
        plg.getStroke().getGreen(),
        plg.getStroke().getBlue(),
        round(255 * plg.getStrokeOpacity()));
    sf::Color fillColor(plg.getFill().getRed(),
        plg.getFill().getGreen(),
        plg.getFill().getBlue(),
        round(255 * plg.getFillOpacity()));

    vector<sf::Vector2f> points;
    for (auto& point : plg.getPoints()) {
        points.push_back(sf::Vector2f(static_cast<float>(point.getX()), static_cast<float>(point.getY())));
    }

    sf::ConvexShape polygon;
    polygon.setPointCount(plg.getPoints().size());
    polygon.setFillColor(fillColor);
    polygon.setOutlineColor(outlineColor);
    polygon.setOutlineThickness(plg.getStrokeWidth());
    int i = 0;
    for (const sf::Vector2f& point : points)
    {
        polygon.setPoint(i++, point + sf::Vector2f(plg.getStrokeWidth() * 1.5f, -plg.getStrokeWidth()));
    }
    return polygon;
}

sf::ConvexShape SF_ShapeData::createPolygon(int pointCount, sf::Color fillColor, sf::Color outlineColor, float strokeWidth, vector<sf::Vector2f> points)
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


vector<sf::ConvexShape> SF_ShapeData::createPolyline(PolylineSVG pll)
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

    sf::Color fillColor(pll.getFill().getRed(),
        pll.getFill().getGreen(),
        pll.getFill().getBlue(), round(255 * pll.getFillOpacity()));

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

vector<sf::RectangleShape> SF_ShapeData::createOutlinePolyline(PolylineSVG pll)
{
    sf::Color outlineColor(pll.getStroke().getRed(),
        pll.getStroke().getGreen(),
        pll.getStroke().getBlue(),
        round(255 * pll.getStrokeOpacity()));

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
    SF_ShapeData temp;
    ////////////

    vector<sf::RectangleShape> outlinePolylines;
    sf::RectangleShape outline;
    for (int i = 0; i < lines.size(); i++)
    {
        outline = temp.createLine(lines[i].getP1().x, lines[i].getP1().y, lines[i].getP2().x, lines[i].getP2().y, outlineColor, pll.getStrokeWidth());
        outlinePolylines.push_back(outline);
    }
    return outlinePolylines;
}
