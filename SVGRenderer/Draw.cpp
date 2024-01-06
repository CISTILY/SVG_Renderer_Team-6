#include "Draw.h"

bool Draw::drew = 0;
vector< GraphicsPath*> Draw::graphicsPaths;

Draw::Draw()
{
    this->curent_path = 0;
    //cout << "Draw::Default Constructor\n";
}

Draw::~Draw()
{
    //cout << "Draw::Destructor\n";
}

float angleBetweenVectors(float ux, float uy, float vx, float vy)
{
    float angle = acos((ux * vx + uy * vy) / sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy))) * 180 / PI;
    if (ux * vy - uy * vx < 0)
        return -angle;
    return angle;
}

EllipticalArc createEllipticalArc(float x1, float y1, float rx, float ry, float phi, float fA, float fS, float x2, float y2)
{
    phi = phi * PI / 180;

    float x1_prime = cos(phi) * ((x1 - x2) / 2) + sin(phi) * ((y1 - y2) / 2);
    float y1_prime = -sin(phi) * ((x1 - x2) / 2) + cos(phi) * ((y1 - y2) / 2);

    float sign = (fA == fS) ? -1 : 1;
    float tmp = sign * sqrt((rx * rx * ry * ry - rx * rx * y1_prime * y1_prime - ry * ry * x1_prime * x1_prime) / (rx * rx * y1_prime * y1_prime + ry * ry * x1_prime * x1_prime));
    float cx_prime = tmp * (rx * y1_prime / ry);
    float cy_prime = -tmp * (ry * x1_prime / rx);

    float cx = cos(phi) * cx_prime - sin(phi) * cy_prime + (x1 + x2) / 2;
    float cy = sin(phi) * cx_prime + cos(phi) * cy_prime + (y1 + y2) / 2;

    float theta1 = angleBetweenVectors(1, 0, (x1_prime - cx_prime) / rx, (y1_prime - cy_prime) / ry);
    float deltaTheta = angleBetweenVectors((x1_prime - cx_prime) / rx, (y1_prime - cy_prime) / ry, (-x1_prime - cx_prime) / rx, (-y1_prime - cy_prime) / ry);
    
    if (fS == 0 && deltaTheta > 0)
        deltaTheta -= 360;
    else if (fS == 1 && deltaTheta < 0)
        deltaTheta += 360;

    return { cx,cy,theta1,deltaTheta };
}

void Draw::transform(Graphics& graphics, Shape* shape) {
    for (int i = shape->getTransform().size() - 1; i >= 0; --i) {
        for (int j = 0; j < 3; ++j)
        {
            if (shape->getOrderOfTransform()[i][j] == 0) {
                graphics.TranslateTransform(shape->getTranslate()[i].getX(), shape->getTranslate()[i].getY());
            }
            else if (shape->getOrderOfTransform()[i][j] == 1) {
                graphics.RotateTransform(shape->getRotateAngle()[i]);
            }
            else if (shape->getOrderOfTransform()[i][j] == 2) {
                graphics.ScaleTransform(shape->getScalePoint()[i].getX(), shape->getScalePoint()[i].getY());
            }
        }
    }
}

LinearGradientBrush* Draw::createLinearGradient(LinearGradientSVG lgSVG)
{
    int n = lgSVG.getStops().size();

    Color* colors = new Color[n];
    REAL* pos = new REAL[n];
    for (int i = 0; i < n; i++)
    {
        colors[i] = Color(255 * lgSVG.getStops()[i].getStopOpacity(), lgSVG.getStops()[i].getStopColor().getRed(), lgSVG.getStops()[i].getStopColor().getGreen(), lgSVG.getStops()[i].getStopColor().getBlue());
        pos[i] = (lgSVG.getStops()[i].getOffset() / 100);
    }

    Point point1(lgSVG.getPoint1().getX(), lgSVG.getPoint1().getY());
    Point point2(lgSVG.getPoint2().getX(), lgSVG.getPoint2().getY());

    LinearGradientBrush* brush = new LinearGradientBrush(point1, point2, colors[0], colors[n - 1]);
    brush->SetInterpolationColors(colors, pos, n);

    delete[] colors;
    delete[] pos;

    return brush;
}

PathGradientBrush* Draw::createRadialGradient(RadialGradientSVG rgSVG)
{
    GraphicsPath path;

    double radius = rgSVG.getRadius();
    Point center(rgSVG.getPoint1().getX(), rgSVG.getPoint1().getY());
    int n = rgSVG.getStops().size();
    Rect rectangle(rgSVG.getPoint1().getX() - radius, rgSVG.getPoint1().getY() - radius, radius * 2, radius * 2);
    path.AddEllipse(rectangle);
    Color* colors = new Color[n];
    REAL* pos = new REAL[n];
    for (int i = 0; i < n; i++)
    {
        colors[i] = Color(255 * rgSVG.getStops()[i].getStopOpacity(), rgSVG.getStops()[i].getStopColor().getRed(), rgSVG.getStops()[i].getStopColor().getGreen(), rgSVG.getStops()[i].getStopColor().getBlue());
        pos[i] = rgSVG.getStops()[i].getOffset();
    }
    Matrix matrix(rgSVG.getMatrix()[0], rgSVG.getMatrix()[1], rgSVG.getMatrix()[2], rgSVG.getMatrix()[3], rgSVG.getMatrix()[4], rgSVG.getMatrix()[5]);

    PathGradientBrush* pthGrBrush = new PathGradientBrush(&path);
    pthGrBrush->SetCenterPoint(center);
    pthGrBrush->SetInterpolationColors(colors, pos, n);
    pthGrBrush->SetSurroundColors(colors, &n);
    pthGrBrush->SetTransform(&matrix);

    delete[] colors;
    delete[] pos;

    return pthGrBrush;
}

VOID Draw::DrawCircle(Graphics& graphics, CircleSVG circle, Def gradient)
{
    int alreadyHasBrush = 0;
    Shape* shape = dynamic_cast<Shape*>(new CircleSVG(circle));
    transform(graphics, shape);

    Rect rect(circle.getCoordinateX() - circle.getRadiusX(), circle.getCoordinateY() - circle.getRadiusX(), 2 * circle.getRadiusX(), 2 * circle.getRadiusX());

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        if (circle.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {
            gradient.getLinearGradientAddress()[i][i].setPoint1(circle.getCoordinateX() - circle.getRadiusX(), circle.getCoordinateY() - circle.getRadiusY());
            gradient.getLinearGradientAddress()[i][i].setPoint2(circle.getCoordinateX() - circle.getRadiusX() + 2 * circle.getRadiusX(), circle.getCoordinateY() - circle.getRadiusY());

            graphics.FillEllipse(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), rect);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (circle.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillEllipse(&brush, rect);
            graphics.FillEllipse(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), rect);
            alreadyHasBrush = 1;
            break;
        }
    }

    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * circle.getFillOpacity()), circle.getFill().getRed(), circle.getFill().getGreen(), circle.getFill().getBlue()));
        graphics.FillEllipse(&brush, rect);
    }

    Pen pen(Color(round(255 * circle.getStrokeOpacity()), circle.getStroke().getRed(), circle.getStroke().getGreen(), circle.getStroke().getBlue()), circle.getStrokeWidth());
    if (circle.getStrokeWidth() != 0)
        graphics.DrawEllipse(&pen, rect);
}

VOID Draw::DrawRectangle(Graphics& graphics, RectangleSVG rect, Def gradient)
{
    int alreadyHasBrush = 0;
    Shape* shape = dynamic_cast<Shape*>(new RectangleSVG(rect));
    transform(graphics, shape);

    Rect rectangle(rect.getCoordinateX(), rect.getCoordinateY(), rect.getWidth(), rect.getHeight());

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        if (rect.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {
            gradient.getLinearGradientAddress()[i][i].setPoint1(rect.getCoordinateX(), rect.getCoordinateY());
            gradient.getLinearGradientAddress()[i][i].setPoint2(rect.getCoordinateX() + rect.getWidth(), rect.getCoordinateY());

            graphics.FillRectangle(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), rectangle);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (rect.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillRectangle(&brush, rectangle);
            graphics.FillRectangle(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), rectangle);
            alreadyHasBrush = 1;
            break;
        }

    }

    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * rect.getFillOpacity()), rect.getFill().getRed(), rect.getFill().getGreen(), rect.getFill().getBlue()));
        graphics.FillRectangle(&brush, rectangle);
    }

    Pen pen(Color(round(255 * rect.getStrokeOpacity()), rect.getStroke().getRed(), rect.getStroke().getGreen(), rect.getStroke().getBlue()), rect.getStrokeWidth());
    if (rect.getStrokeWidth() != 0)
        graphics.DrawRectangle(&pen, rectangle);

}

VOID Draw::DrawEllipse(Graphics& graphics, EllipseSVG ellip, Def gradient)
{
    int alreadyHasBrush = 0;
    Shape* shape = dynamic_cast<Shape*>(new EllipseSVG(ellip));
    transform(graphics, shape);

    Rect rect(ellip.getCoordinateX() - ellip.getRadiusX(), ellip.getCoordinateY() - ellip.getRadiusY(), 2 * ellip.getRadiusX(), 2 * ellip.getRadiusY());

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        if (ellip.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {
            gradient.getLinearGradientAddress()[i][i].setPoint1(ellip.getCoordinateX() - ellip.getRadiusX(), ellip.getCoordinateY() - ellip.getRadiusY());
            gradient.getLinearGradientAddress()[i][i].setPoint2(ellip.getCoordinateX() - ellip.getRadiusX() + 2 * ellip.getRadiusX(), ellip.getCoordinateY() - ellip.getRadiusY());

            graphics.FillEllipse(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), rect);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (ellip.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillEllipse(&brush, rect);
            graphics.FillEllipse(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), rect);
            alreadyHasBrush = 1;
            break;
        }
    }

    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * ellip.getFillOpacity()), ellip.getFill().getRed(), ellip.getFill().getGreen(), ellip.getFill().getBlue()));
        graphics.FillEllipse(&brush, rect);
    }

    Pen pen(Color(round(255 * ellip.getStrokeOpacity()), ellip.getStroke().getRed(), ellip.getStroke().getGreen(), ellip.getStroke().getBlue()), ellip.getStrokeWidth());
    if (ellip.getStrokeWidth() != 0)
        graphics.DrawEllipse(&pen, rect);
}

VOID Draw::DrawLine(Graphics& graphics, LineSVG line)
{
    Shape* shape = dynamic_cast<Shape*>(new LineSVG(line));
    transform(graphics, shape);

    Pen pen(Color(round(255 * line.getStrokeOpacity()), line.getStroke().getRed(), line.getStroke().getGreen(), line.getStroke().getBlue()), line.getStrokeWidth());
    graphics.DrawLine(&pen, line.getCoordinateX(), line.getCoordinateY(), line.getEnd().getX(), line.getEnd().getY());
}

VOID Draw::DrawText(Graphics& graphics, TextSVG text, Def gradient)
{
    int alreadyHasBrush = 0;
    float delta = 0;
    Shape* shape = dynamic_cast<Shape*>(new TextSVG(text));
    transform(graphics, shape);

    GraphicsPath path;
    StringFormat strFormat;
    if (text.getAnchor() == "middle") {
        strFormat.SetAlignment(StringAlignmentCenter);
    }
    else if (text.getAnchor() == "end") {
        strFormat.SetAlignment(StringAlignmentFar);
        delta = 0.15;
    }
    else
    {
        strFormat.SetAlignment(StringAlignmentNear);
        delta = -0.15;
    }

    PointF pointF(text.getCoordinateX() + text.getDx() + delta * text.getFont_size(),
        text.getCoordinateY() + text.getDy() - 0.89 * text.getFont_size());
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

    vector<string> fonts = text.getFont_family();

    wstring wFontFamily;

    for (int i = 0; i < fonts.size(); i++) {
        wFontFamily = converter.from_bytes(fonts[i]);
        FontFamily fontFamily(wFontFamily.c_str());
        if (fontFamily.IsAvailable())
            break;
    }
    FontFamily fontFamily(wFontFamily.c_str());
    Font font(&fontFamily, text.getFont_size(), 0, UnitPixel);

    int font_style = 0;
    if (text.getFont_style() == "italic")
        font_style = 2;

    wstring content = converter.from_bytes(text.getContent());
    path.AddString(content.c_str(), -1, &fontFamily, font_style, static_cast<REAL>(text.getFont_size()), pointF, &strFormat);

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        cout << text.getFill().getURL() << " " << gradient.getLinearGradients()[i].getID() << " Result: " << (text.getFill().getURL() == gradient.getLinearGradients()[i].getID());
        if (text.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {
            gradient.getLinearGradientAddress()[i][i].setPoint1(text.getCoordinateX(), text.getCoordinateY());
            gradient.getLinearGradientAddress()[i][i].setPoint2(text.getFont_size() * 7.15, text.getCoordinateY());

            graphics.FillPath(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), &path);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (text.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillPath(&brush, &path);
            graphics.FillPath(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), &path);
            alreadyHasBrush = 1;
            break;
        }
    }
    cout << alreadyHasBrush;
    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * text.getFillOpacity()), text.getFill().getRed(), text.getFill().getGreen(), text.getFill().getBlue()));
        graphics.FillPath(&brush, &path);
    }

    Pen pen(Color(round(255 * text.getStrokeOpacity()), text.getStroke().getRed(), text.getStroke().getGreen(), text.getStroke().getBlue()), text.getStrokeWidth());

    if (text.getStrokeWidth() != 0)
        graphics.DrawPath(&pen, &path);
}

VOID Draw::DrawPolygon(Graphics& graphics, PolygonSVG plg, Def gradient)
{
    int alreadyHasBrush = 0;
    Shape* shape = dynamic_cast<Shape*>(new PolygonSVG(plg));
    transform(graphics, shape);

    int nPoint = plg.getPoints().size();
    Point* points = new Point[nPoint];
    double xMin = 0;
    double xMax = 0;
    for (int i = 0; i < nPoint; i++)
    {
        if (plg.getPoints()[i].getX() < xMin)
        {
            xMin = plg.getPoints()[i].getX();
        }
        if (plg.getPoints()[i].getX() > xMax)
        {
            xMax = plg.getPoints()[i].getX();
        }
        points[i].X = plg.getPoints()[i].getX();
        points[i].Y = plg.getPoints()[i].getY();
    }

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        if (plg.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {

            gradient.getLinearGradientAddress()[i][i].setPoint1(xMin, 0);
            gradient.getLinearGradientAddress()[i][i].setPoint2(xMax, 0);

            graphics.FillPolygon(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), points, nPoint);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (plg.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillPolygon(&brush, points, nPoint);
            graphics.FillPolygon(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), points, nPoint);
            alreadyHasBrush = 1;
            break;
        }
    }

    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * plg.getStrokeOpacity()), plg.getFill().getRed(), plg.getFill().getGreen(), plg.getFill().getBlue()));
        graphics.FillPolygon(&brush, points, nPoint, FillModeWinding);
    }

    Pen pen(Color(round(255 * plg.getStrokeOpacity()), plg.getStroke().getRed(), plg.getStroke().getGreen(), plg.getStroke().getBlue()), plg.getStrokeWidth());
    if (plg.getStrokeWidth() != 0)
        graphics.DrawPolygon(&pen, points, nPoint);
}

VOID Draw::DrawPath(Graphics& graphics, PathSVG path, Def gradient)
{
    int alreadyHasBrush = 0;
    Shape* shape = dynamic_cast<Shape*>(new PathSVG(path));
    transform(graphics, shape);


    GraphicsPath* graphicsPath;

    if (drew == 0)
    {
        int nPath = path.getCommand().size();
        graphicsPath = new GraphicsPath[nPath];

        Point2D startPoint;
        int j = 0; // index

        for (int i = 0; i < nPath; i++)
        {
            if (path.getCommand()[i] == 'M')
            {
                startPoint = path.getPoints()[j];
                graphicsPath->StartFigure();

                j++;

            }
            else if (path.getCommand()[i] == 'L')
            {
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY());

                j++;
            }
            else if (path.getCommand()[i] == 'H')
            {
                Point2D temp(path.getPoints()[j].getX(), path.getPoints()[j - 1].getY());
                path.replaceOnePoint(temp, j);
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY());

                j++;
            }
            else if (path.getCommand()[i] == 'V')
            {
                Point2D temp(path.getPoints()[j - 1].getX(), path.getPoints()[j].getY());
                path.replaceOnePoint(temp, j);
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY());

                j++;
            }
            else if (path.getCommand()[i] == 'C')
            {
                graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                    path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY(),
                    path.getPoints()[j + 2].getX(), path.getPoints()[j + 2].getY());

                j += 3;
            }
            else if (path.getCommand()[i] == 'S')
            {
                if (path.getCommand()[i - 1] == 'S' || path.getCommand()[i - 1] == 's' || path.getCommand()[i - 1] == 'C' || path.getCommand()[i - 1] == 'c')
                {
                    Point2D point(path.getPoints()[j - 1].getX() * 2 - path.getPoints()[j - 2].getX(), path.getPoints()[j - 1].getY() * 2 - path.getPoints()[j - 2].getY());
                    graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                        point.getX(), point.getY(),
                        path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                        path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY());
                }
                else
                {
                    graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                        path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                        path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                        path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY());
                }

                j += 2;
            }
            else if (path.getCommand()[i] == 'A')
            {
                EllipticalArc arc = createEllipticalArc(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                    path.getPoints()[j + 1].getX(),
                    path.getPoints()[j + 2].getX(), path.getPoints()[j + 2].getY(),
                    path.getPoints()[j + 3].getX(), path.getPoints()[j + 3].getY());
                graphicsPath->AddArc(arc.cx - path.getPoints()[j].getX(), arc.cy - path.getPoints()[j].getY(), 2 * path.getPoints()[j].getX(), 2 * path.getPoints()[j].getY(), fmod((long double)arc.theta1, 360), fmod((long double)arc.deltaTheta, 360));
                j += 4;
            }
            else if (path.getCommand()[i] == 'Q')
            {
                Point* point = new Point[11];
                int i = 0;
                for (double t = 0; t <= 1; t += 0.1)
                {
                    double x = (1 - t) * (1 - t) * path.getPoints()[j - 1].getX() + 2 * (1 - t) * t * path.getPoints()[j].getX() + t * t * path.getPoints()[j + 1].getX();
                    double y = (1 - t) * (1 - t) * path.getPoints()[j - 1].getY() + 2 * (1 - t) * t * path.getPoints()[j].getY() + t * t * path.getPoints()[j + 1].getY();
                    point[i] = Point(x, y);
                    i++;
                }

                graphicsPath->AddCurve(point, 11);

                j += 2;
            }
            else if (path.getCommand()[i] == 'Z' || path.getCommand()[i] == 'z')
            {
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    startPoint.getX(), startPoint.getY());
                graphicsPath->CloseFigure();
            }
            else if (path.getCommand()[i] == 'm')
            {
                if (j == 0)
                {
                    startPoint = path.getPoints()[j];
                }
                else
                {
                    Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                    path.replaceOnePoint(temp, j);
                    startPoint = temp;
                }

                j++;
            }
            else if (path.getCommand()[i] == 'l')
            {
                Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                path.replaceOnePoint(temp, j);
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY());

                j++;
            }
            else if (path.getCommand()[i] == 'h')
            {
                Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY());
                path.replaceOnePoint(temp, j);
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY());

                j++;
            }
            else if (path.getCommand()[i] == 'v')
            {
                Point2D temp(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                path.replaceOnePoint(temp, j);
                graphicsPath->AddLine(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY());

                j++;
            }
            else if (path.getCommand()[i] == 'c')
            {
                Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                path.replaceOnePoint(temp, j);
                Point2D temp2(path.getPoints()[j - 1].getX() + path.getPoints()[j + 1].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 1].getY());
                path.replaceOnePoint(temp2, j + 1);
                Point2D temp3(path.getPoints()[j - 1].getX() + path.getPoints()[j + 2].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 2].getY());
                path.replaceOnePoint(temp3, j + 2);
                graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                    path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY(),
                    path.getPoints()[j + 2].getX(), path.getPoints()[j + 2].getY());

                j += 3;
            }
            else if (path.getCommand()[i] == 's')
            {
                if (path.getCommand()[i - 1] == 'S' || path.getCommand()[i - 1] == 's' || path.getCommand()[i - 1] == 'C' || path.getCommand()[i - 1] == 'c')
                {
                    Point2D point(path.getPoints()[j - 1].getX() * 2 - path.getPoints()[j - 2].getX(), path.getPoints()[j - 1].getY() * 2 - path.getPoints()[j - 2].getY());
                    Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                    path.replaceOnePoint(temp, j);
                    Point2D temp2(path.getPoints()[j - 1].getX() + path.getPoints()[j + 1].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 1].getY());
                    path.replaceOnePoint(temp2, j + 1);
                    graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                        point.getX(), point.getY(),
                        path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                        path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY());
                }
                else
                {
                    Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                    path.replaceOnePoint(temp, j);
                    Point2D temp2(path.getPoints()[j - 1].getX() + path.getPoints()[j + 1].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 1].getY());
                    path.replaceOnePoint(temp2, j + 1);
                    graphicsPath->AddBezier(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                        path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                        path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                        path.getPoints()[j + 1].getX(), path.getPoints()[j + 1].getY());
                }

                j += 2;
            }
            else if (path.getCommand()[i] == 'a')
            {
                Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j + 3].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 3].getY());
                path.replaceOnePoint(temp, j + 3);

                EllipticalArc arc = createEllipticalArc(path.getPoints()[j - 1].getX(), path.getPoints()[j - 1].getY(),
                    path.getPoints()[j].getX(), path.getPoints()[j].getY(),
                    path.getPoints()[j + 1].getX(),
                    path.getPoints()[j + 2].getX(), path.getPoints()[j + 2].getY(),
                    path.getPoints()[j + 3].getX(), path.getPoints()[j + 3].getY());
                graphicsPath->AddArc(arc.cx - path.getPoints()[j].getX(), arc.cy - path.getPoints()[j].getY(), 2 * path.getPoints()[j].getX(), 2 * path.getPoints()[j].getY(), fmod((long double)arc.theta1, 360), fmod((long double)arc.deltaTheta, 360));
                j += 4;
            }
            else if (path.getCommand()[i] == 'q')
            {
                Point2D temp(path.getPoints()[j - 1].getX() + path.getPoints()[j].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j].getY());
                path.replaceOnePoint(temp, j);
                Point2D temp2(path.getPoints()[j - 1].getX() + path.getPoints()[j + 1].getX(), path.getPoints()[j - 1].getY() + path.getPoints()[j + 1].getY());
                path.replaceOnePoint(temp2, j + 1);

                Point* point = new Point[11];
                int i = 0;
                for (double t = 0; t <= 1; t += 0.1)
                {
                    double x = (1 - t) * (1 - t) * path.getPoints()[j - 1].getX() + 2 * (1 - t) * t * path.getPoints()[j].getX() + t * t * path.getPoints()[j + 1].getX();
                    double y = (1 - t) * (1 - t) * path.getPoints()[j - 1].getY() + 2 * (1 - t) * t * path.getPoints()[j].getY() + t * t * path.getPoints()[j + 1].getY();
                    point[i] = Point(x, y);
                    i++;
                }

                graphicsPath->AddCurve(point, 11);

                j += 2;
            }
        }

        this->graphicsPaths.push_back(graphicsPath);
    }
    else
    {
        graphicsPath = this->graphicsPaths[this->curent_path];
        ++this->curent_path;
    }

    double xMin = 0, xMax = 0;
    for (int i = 0; i < path.getPoints().size(); i++)
    {
        if (path.getPoints()[i].getX() < xMin)
        {
            xMin = path.getPoints()[i].getX();
        }
        if (path.getPoints()[i].getX() > xMax)
        {
            xMax = path.getPoints()[i].getX();
        }
    }

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        if (path.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {
            gradient.getLinearGradientAddress()[i][i].setPoint1(xMin, 0);
            gradient.getLinearGradientAddress()[i][i].setPoint2(xMax, 0);

            graphics.FillPath(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), graphicsPath);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (path.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillPath(&brush, graphicsPath);
            graphics.FillPath(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), graphicsPath);
            alreadyHasBrush = 1;
            break;
        }
    }
    cout << alreadyHasBrush;
    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * path.getFillOpacity()), path.getFill().getRed(), path.getFill().getGreen(), path.getFill().getBlue()));
        graphics.FillPath(&brush, graphicsPath);
    }

    Pen pen(Color(round(255 * path.getStrokeOpacity()), path.getStroke().getRed(), path.getStroke().getGreen(), path.getStroke().getBlue()), path.getStrokeWidth());
    if (path.getStrokeWidth() != 0)
        graphics.DrawPath(&pen, graphicsPath);
}

VOID Draw::DrawPolyline(Graphics& graphics, PolylineSVG pll, Def gradient)
{
    int alreadyHasBrush = 0;
    Shape* shape = dynamic_cast<Shape*>(new PolylineSVG(pll));
    transform(graphics, shape);

    int nPoint = pll.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = pll.getPoints()[i].getX();
        points[i].Y = pll.getPoints()[i].getY();
    }

    double xMin = 0, xMax = 0;
    for (int i = 0; i < pll.getPoints().size(); i++)
    {
        if (pll.getPoints()[i].getX() < xMin)
        {
            xMin = pll.getPoints()[i].getX();
        }
        if (pll.getPoints()[i].getX() > xMax)
        {
            xMax = pll.getPoints()[i].getX();
        }
    }

    for (int i = 0; i < gradient.getLinearGradients().size(); ++i) {
        if (pll.getFill().getURL() == gradient.getLinearGradients()[i].getID() && alreadyHasBrush == 0) {
            gradient.getLinearGradientAddress()[i][i].setPoint1(xMin, 0);
            gradient.getLinearGradientAddress()[i][i].setPoint2(xMax, 0);

            graphics.FillPolygon(&*Draw::createLinearGradient(gradient.getLinearGradients()[i]), points, nPoint);
            alreadyHasBrush = 1;
            break;
        }
    }

    for (int i = 0; i < gradient.getRadialGradient().size(); ++i) {
        if (pll.getFill().getURL() == gradient.getRadialGradient()[i].getID() && alreadyHasBrush == 0) {
            int nColor = gradient.getRadialGradient()[i].getStops().size();
            SolidBrush brush(Color(round(255 * gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopOpacity()),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getRed(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getGreen(),
                gradient.getRadialGradient()[i].getStops()[nColor - 1].getStopColor().getBlue()));
            graphics.FillPolygon(&brush, points, nPoint);
            graphics.FillPolygon(&*Draw::createRadialGradient(gradient.getRadialGradient()[i]), points, nPoint);
            alreadyHasBrush = 1;
            break;
        }
    }

    if (alreadyHasBrush == 0) {
        SolidBrush brush(Color(round(255 * pll.getFillOpacity()), pll.getFill().getRed(), pll.getFill().getGreen(), pll.getFill().getBlue()));
        graphics.FillPolygon(&brush, points, nPoint);
    }

    Pen pen(Color(round(255 * pll.getStrokeOpacity()), pll.getStroke().getRed(), pll.getStroke().getGreen(), pll.getStroke().getBlue()), pll.getStrokeWidth());
    if (pll.getStrokeWidth() != 0)
        graphics.DrawLines(&pen, points, nPoint);
}

void Draw::drawShape(Graphics& graphics, vector<Shape*> shapesSVG, Def gradient)
{
    for (int i = 0; i < shapesSVG.size(); ++i)
    {
        GraphicsState origin = graphics.Save();
        if (shapesSVG[i]->getTypeName() == "rect") {
            RectangleSVG* rect = dynamic_cast<RectangleSVG*> (shapesSVG[i]);
            DrawRectangle(graphics, *rect, gradient);
        }

        else if (shapesSVG[i]->getTypeName() == "circle") {
            CircleSVG* cir = dynamic_cast<CircleSVG*> (shapesSVG[i]);
            DrawCircle(graphics, *cir, gradient);
        }

        else if (shapesSVG[i]->getTypeName() == "text") {
            TextSVG* txt = dynamic_cast<TextSVG*> (shapesSVG[i]);
            DrawText(graphics, *txt, gradient);
        }

        else if (shapesSVG[i]->getTypeName() == "line") {
            LineSVG* line = dynamic_cast<LineSVG*> (shapesSVG[i]);
            DrawLine(graphics, *line);
        }

        else if (shapesSVG[i]->getTypeName() == "ellipse") {
            EllipseSVG* ellip = dynamic_cast<EllipseSVG*> (shapesSVG[i]);
            DrawEllipse(graphics, *ellip, gradient);
        }

        else if (shapesSVG[i]->getTypeName() == "polygon") {
            PolygonSVG* polygon = dynamic_cast<PolygonSVG*> (shapesSVG[i]);
            DrawPolygon(graphics, *polygon, gradient);
        }
        else if (shapesSVG[i]->getTypeName() == "polyline") {
            PolylineSVG* polyline = dynamic_cast<PolylineSVG*> (shapesSVG[i]);
            DrawPolyline(graphics, *polyline, gradient);
        }
        else if (shapesSVG[i]->getTypeName() == "path") {
            PathSVG* path = dynamic_cast<PathSVG*> (shapesSVG[i]);
            DrawPath(graphics, *path, gradient);
        }
        else if (shapesSVG[i]->getTypeName() == "g") {
            GroupSVG* g = dynamic_cast<GroupSVG*> (shapesSVG[i]);
            drawShape(graphics, g->getVectorShape(), gradient);
        }
        graphics.Restore(origin);
    }
}

void Draw::setDrew(bool x) {
    drew = x;
}
