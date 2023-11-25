#include "Renderer.h"

using namespace std;

//SF_ShapeData::SF_ShapeData() {
//    cout << "SF_ShapeData::Default Constructor" << endl;
//}
//
//SF_ShapeData::~SF_ShapeData() {
//    cout << "SF_ShapeData::Destructor" << endl;
//}

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
    text.setOrigin(txt.getFont_size() - 50, txt.getFont_size());

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
    rect.setOrigin(0, -3);

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
    circle.setRadius(cir.getRadiusX() - cir.getStrokeWidth() / 2);
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
    ellipse.setRadius(radius + sf::Vector2f(ellip.getStrokeWidth(), -ellip.getStrokeWidth() * 0.5f));
    ellipse.setFillColor(fillColor);
    ellipse.setOutlineColor(outlineColor);
    ellipse.setOutlineThickness(ellip.getStrokeWidth());
    ellipse.setOrigin(radius.x * 0.9f, radius.y / 0.9f);

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
    line.setOrigin(0, 4);

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
    vector<sf::Vector2f> newPoints = resizePolygon(points, plg.getStrokeWidth());
    for (const sf::Vector2f& point : newPoints)
    {
        polygon.setPoint(i++, point + sf::Vector2f(plg.getStrokeWidth() - 5, plg.getStrokeWidth() - 15));
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

float Line::getA()
{
    return a;
}

float Line::getB()
{
    return b;
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
    if (isAppeared(point, points)) {
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
        if (lines[i].getP1().x == lines[i].getP2().x && lines[i].getP1().y > lines[i].getP2().y)
        {
            outline = temp.createLine(lines[i].getP1().x - pll.getStrokeWidth() / 2, lines[i].getP1().y - pll.getStrokeWidth() / 2, lines[i].getP2().x - pll.getStrokeWidth() / 2, lines[i].getP2().y + pll.getStrokeWidth() / 2, outlineColor, pll.getStrokeWidth());
            outlinePolylines.push_back(outline);
            outline = temp.createLine(lines[i].getP2().x - pll.getStrokeWidth() / 2, lines[i].getP2().y + pll.getStrokeWidth() / 2, lines[i].getP2().x - pll.getStrokeWidth() / 2, lines[i].getP2().y - pll.getStrokeWidth() / 2, outlineColor, pll.getStrokeWidth());
            outlinePolylines.push_back(outline);
        }
        else if (lines[i].getP1().x == lines[i].getP2().x && lines[i].getP1().y < lines[i].getP2().y)
        {
            outline = temp.createLine(lines[i].getP1().x + pll.getStrokeWidth() / 2, lines[i].getP1().y + pll.getStrokeWidth() / 2, lines[i].getP2().x + pll.getStrokeWidth() / 2, lines[i].getP2().y, outlineColor, pll.getStrokeWidth());
            outlinePolylines.push_back(outline);
            outline = temp.createLine(lines[i].getP2().x + pll.getStrokeWidth() / 2, lines[i].getP2().y, lines[i].getP2().x + pll.getStrokeWidth() / 2, lines[i].getP2().y + pll.getStrokeWidth() / 2, outlineColor, pll.getStrokeWidth());
            outlinePolylines.push_back(outline);
        }
        else if (lines[i].getP1().x > lines[i].getP2().x && lines[i].getP1().y == lines[i].getP2().y)
        {
            outline = temp.createLine(lines[i].getP1().x - pll.getStrokeWidth() / 2, lines[i].getP1().y + pll.getStrokeWidth() / 2, lines[i].getP2().x - pll.getStrokeWidth() / 2, lines[i].getP2().y + pll.getStrokeWidth() / 2, outlineColor, pll.getStrokeWidth());
            outlinePolylines.push_back(outline);
        }
        else if (lines[i].getP1().x < lines[i].getP2().x && lines[i].getP1().y == lines[i].getP2().y)
        {
            outline = temp.createLine(lines[i].getP1().x + pll.getStrokeWidth() / 2, lines[i].getP1().y - pll.getStrokeWidth() / 2, lines[i].getP2().x + pll.getStrokeWidth() / 2, lines[i].getP2().y - pll.getStrokeWidth() / 2, outlineColor, pll.getStrokeWidth());
            outlinePolylines.push_back(outline);
        }
    }
    return outlinePolylines;
}

Renderer::Renderer() {
    // Set up variables
    this->num = 0;
    this->type = 0;
    this->zoom = 1.0;
    this->zoomDis = 5;
    this->allMove = 0;
    this->Type = { "rect", "circle", "ellipse" , "line", "polygon", "text", "polyline" };
}

void Renderer::Render(vector<SF_ShapeData> print, vector<ShapeData> data) {

    // Set up SFML window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1000, 500), "Sample", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 1000, 500));
    window.setView(view);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //Event handling for closing the window, resizing, and mouse wheel zooming
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
                    cout << data[num].getTypeName() << endl;
                    view.setCenter(print[num].getCenter(data[num]));
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
            if (data[i].getTypeName() == "rect")
                window.draw(print[i].getSF_rect());
            if (data[i].getTypeName() == "circle")
                window.draw(print[i].getSF_cir());
            if (data[i].getTypeName() == "ellipse")
                window.draw(print[i].getSF_ellip());
            if (data[i].getTypeName() == "line")
                window.draw(print[i].getSF_line());
            if (data[i].getTypeName() == "polygon")
                window.draw(print[i].getSF_polygon());
            if (data[i].getTypeName() == "text")
                window.draw(print[i].getSF_text());
            if (data[i].getTypeName() == "polyline")
            {
                for (const sf::ConvexShape& filPolyline : print[i].getSF_fillPolylines())
                    window.draw(filPolyline);
                if (data[i].getFlagStroke())
                {
                    for (const sf::RectangleShape& outline : print[i].getSF_outlinePolylines())
                        window.draw(outline);
                }
            }
        }

        // Handle Keyboard input for various actions (moving, zooming, rotating)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            view.reset(sf::FloatRect(0, 0, 1000, 500));
            window.setView(window.getDefaultView());
            zoomDis = 5;
        }
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
                    if (data[l].getTypeName() == Type[type])
                        print[l].moving(MOVEDIS, 0);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (allMove == 0)
                print[num].moving(-MOVEDIS, 0);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (data[l].getTypeName() == Type[type])
                        print[l].moving(-MOVEDIS, 0);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (allMove == 0)
                print[num].moving(0, -MOVEDIS);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (data[l].getTypeName() == Type[type])
                        print[l].moving(0, -MOVEDIS);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (allMove == 0)
                print[num].moving(0, MOVEDIS);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (data[l].getTypeName() == Type[type])
                        print[l].moving(0, MOVEDIS);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (allMove == 0)
                print[num].rotating(5);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (data[l].getTypeName() == Type[type])
                        print[l].rotating(5);
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (allMove == 0)
                print[num].rotating(-5);
            else {
                for (int l = 0; l < print.size(); l++) {
                    if (data[l].getTypeName() == Type[type])
                        print[l].rotating(-5);
                }
            }
        }

        window.display();
    }
}

sf::Vector2f findCenterPoint(vector<sf::Vector2f> points)
{
    sf::Vector2f center(0, 0);
    for (sf::Vector2f point : points)
    {
        center.x += point.x;
        center.y += point.y;
    }
    center.x /= points.size();
    center.y /= points.size();
    return center;
}
vector<sf::Vector2f> resizePolygon(vector<sf::Vector2f> points, float strokeWidth)
{
    vector<sf::Vector2f> newPoints;
    sf::Vector2f newPoint;
    sf::Vector2f center = findCenterPoint(points);

    for (sf::Vector2f point : points)
    {
        if (point.x == center.x && point.y > center.y)
        {
            newPoint.x = point.x;
            newPoint.y = point.y - strokeWidth / 2;
        }
        else if (point.x == center.x && point.y < center.y)
        {
            newPoint.x = point.x;
            newPoint.y = point.y + strokeWidth / 2;
        }
        else if (point.x < center.x && point.y == center.y)
        {
            newPoint.x = point.x + strokeWidth / 2;
            newPoint.y = point.y;
        }
        else if (point.x > center.x && point.y == center.y)
        {
            newPoint.x = point.x - strokeWidth / 2;
            newPoint.y = point.y;
        }
        else
        {
            newPoint = findNewPoint(point, center, strokeWidth);
        }
        newPoints.push_back(newPoint);
    }
    return newPoints;
}

float findDelta(float a, float b, float c)
{
    return b * b - 4 * a * c;
}

sf::Vector2f findNewPoint(sf::Vector2f A, sf::Vector2f B, float strokeWidth)
{
    float a, b, c;
    Line AB = AB.createLineFrom2Points(A, B);
    a = AB.getA() * AB.getA() + 1;
    b = -2 * (A.x - AB.getA() * (AB.getB() - A.y));
    c = A.x * A.x + (AB.getB() - A.y) * (AB.getB() - A.y) - strokeWidth * strokeWidth / 4;

    sf::Vector2f newPoint;
    float delta = findDelta(a, b, c);
    if (delta > 0)
    {
        if (A.x > B.x)
        {
            newPoint.x = (-b - sqrt(delta)) / (2 * a);
            newPoint.y = AB.getA() * newPoint.x + AB.getB();
        }
        else
        {
            newPoint.x = (-b + sqrt(delta)) / (2 * a);
            newPoint.y = AB.getA() * newPoint.x + AB.getB();
        }
    }
    else if (delta == 0)
    {
        newPoint.x = -b / (2 * a);
        newPoint.y = AB.getA() * newPoint.x + AB.getB();
    }
    return newPoint;
}
