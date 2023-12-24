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

LinearGradientBrush& Draw::createLinearGradient(LinearGradientSVG lgSVG)
{
    int n = lgSVG.getStops().size();

    Color* colors = new Color(n);
    REAL* pos = new REAL[n];
    for (int i = 0; i < n; i++)
    {
        colors[i] = Color(lgSVG.getStops()[i].getStopColor().getRed(), lgSVG.getStops()[i].getStopColor().getGreen(), lgSVG.getStops()[i].getStopColor().getBlue(), lgSVG.getStops()[i].getStopOpacity());
        pos[i] = lgSVG.getStops()[i].getOffset();
    }

    Point point1(lgSVG.getPoint1().getX(), lgSVG.getPoint1().getY());
    Point point2(lgSVG.getPoint2().getX(), lgSVG.getPoint2().getY());

    LinearGradientBrush brush(point1, point2, colors[0], colors[n - 1]);
    brush.SetInterpolationColors(colors, pos, n);

    delete[] colors;
    delete[] pos;

    return brush;
}

PathGradientBrush& Draw::createRadialGradient(RadialGradientSVG rgSVG)
{
    GraphicsPath path;

    double radius = rgSVG.getRadius();
    Point center(rgSVG.getPoint1().getX(), rgSVG.getPoint1().getY());
    int n = rgSVG.getStops().size();
    Rect rectangle(rgSVG.getPoint1().getX() - radius, rgSVG.getPoint1().getY() - radius, radius * 2, radius * 2);
    path.AddEllipse(rectangle);
    Color* colors = new Color(n);
    REAL* pos = new REAL[n];
    for (int i = 0; i < n; i++)
    {
        colors[i] = Color(rgSVG.getStops()[i].getStopColor().getRed(), rgSVG.getStops()[i].getStopColor().getGreen(), rgSVG.getStops()[i].getStopColor().getBlue(), rgSVG.getStops()[i].getStopOpacity());
        pos[i] = rgSVG.getStops()[i].getOffset();
    }
    Matrix matrix(rgSVG.getMatrix()[0], rgSVG.getMatrix()[1], rgSVG.getMatrix()[2], rgSVG.getMatrix()[3], rgSVG.getMatrix()[4], rgSVG.getMatrix()[5]);

    PathGradientBrush pthGrBrush(&path);
    pthGrBrush.SetCenterPoint(center);
    pthGrBrush.SetInterpolationColors(colors, pos, n);
    pthGrBrush.SetSurroundColors(colors, &n);
    pthGrBrush.SetTransform(&matrix);

    delete[] colors;
    delete[] pos;

    return pthGrBrush;
}

VOID Draw::DrawCircle(Graphics& graphics, CircleSVG circle)
{
    Shape* shape = dynamic_cast<Shape*>(new CircleSVG(circle));
    transform(graphics, shape);

    Rect rect(circle.getCoordinateX() - circle.getRadiusX(), circle.getCoordinateY() - circle.getRadiusX(), 2 * circle.getRadiusX(), 2 * circle.getRadiusX());

    SolidBrush brush(Color(round(255 * circle.getFillOpacity()), circle.getFill().getRed(), circle.getFill().getGreen(), circle.getFill().getBlue()));
    graphics.FillEllipse(&brush, rect);

    Pen pen(Color(round(255 * circle.getStrokeOpacity()), circle.getStroke().getRed(), circle.getStroke().getGreen(), circle.getStroke().getBlue()), circle.getStrokeWidth());
    if (circle.getStrokeWidth() != 0)
        graphics.DrawEllipse(&pen, rect);
}

VOID Draw::DrawRectangle(Graphics& graphics, RectangleSVG rect)
{
    Shape* shape = dynamic_cast<Shape*>(new RectangleSVG(rect));
    transform(graphics, shape);

    Rect rectangle(rect.getCoordinateX(), rect.getCoordinateY(), rect.getWidth(), rect.getHeight());

    SolidBrush brush(Color(round(255 * rect.getFillOpacity()), rect.getFill().getRed(), rect.getFill().getGreen(), rect.getFill().getBlue()));
    graphics.FillRectangle(&brush, rectangle);

    Pen pen(Color(round(255 * rect.getStrokeOpacity()), rect.getStroke().getRed(), rect.getStroke().getGreen(), rect.getStroke().getBlue()), rect.getStrokeWidth());
    if (rect.getStrokeWidth() != 0)
        graphics.DrawRectangle(&pen, rectangle);

}

VOID Draw::DrawEllipse(Graphics& graphics, EllipseSVG ellip)
{
    Shape* shape = dynamic_cast<Shape*>(new EllipseSVG(ellip));
    transform(graphics, shape);

    Rect rect(ellip.getCoordinateX() - ellip.getRadiusX(), ellip.getCoordinateY() - ellip.getRadiusY(), 2 * ellip.getRadiusX(), 2 * ellip.getRadiusY());

    SolidBrush brush(Color(round(255 * ellip.getFillOpacity()), ellip.getFill().getRed(), ellip.getFill().getGreen(), ellip.getFill().getBlue()));
    graphics.FillEllipse(&brush, rect);

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

VOID Draw::DrawText(Graphics& graphics, TextSVG text)
{
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
    SolidBrush brush(Color(round(255 * text.getFillOpacity()), text.getFill().getRed(), text.getFill().getGreen(), text.getFill().getBlue()));

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
    Pen pen(Color(round(255 * text.getStrokeOpacity()), text.getStroke().getRed(), text.getStroke().getGreen(), text.getStroke().getBlue()), text.getStrokeWidth());

    graphics.FillPath(&brush, &path);

    if (text.getStrokeWidth() != 0)
        graphics.DrawPath(&pen, &path);
}

VOID Draw::DrawPolygon(Graphics& graphics, PolygonSVG plg)
{
    Shape* shape = dynamic_cast<Shape*>(new PolygonSVG(plg));
    transform(graphics, shape);

    int nPoint = plg.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = plg.getPoints()[i].getX();
        points[i].Y = plg.getPoints()[i].getY();
    }

    SolidBrush brush(Color(round(255 * plg.getStrokeOpacity()), plg.getFill().getRed(), plg.getFill().getGreen(), plg.getFill().getBlue()));
    graphics.FillPolygon(&brush, points, nPoint, FillModeWinding);

    Pen pen(Color(round(255 * plg.getStrokeOpacity()), plg.getStroke().getRed(), plg.getStroke().getGreen(), plg.getStroke().getBlue()), plg.getStrokeWidth());
    if (plg.getStrokeWidth() != 0)
        graphics.DrawPolygon(&pen, points, nPoint);
}

VOID Draw::DrawPath(Graphics& graphics, PathSVG path)
{
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
        }

        this->graphicsPaths.push_back(graphicsPath);
    }
    else
    {   
        graphicsPath = this->graphicsPaths[this->curent_path];
        ++this->curent_path;
    }
    
    SolidBrush brush(Color(round(255 * path.getFillOpacity()), path.getFill().getRed(), path.getFill().getGreen(), path.getFill().getBlue()));
    graphics.FillPath(&brush, graphicsPath);

    Pen pen(Color(round(255 * path.getStrokeOpacity()), path.getStroke().getRed(), path.getStroke().getGreen(), path.getStroke().getBlue()), path.getStrokeWidth());
    if (path.getStrokeWidth() != 0)
        graphics.DrawPath(&pen, graphicsPath);
}


// graphicsPath*

VOID Draw::DrawPolyline(Graphics& graphics, PolylineSVG pll)
{
    Shape* shape = dynamic_cast<Shape*>(new PolylineSVG(pll));
    transform(graphics, shape);

    int nPoint = pll.getPoints().size();
    Point* points = new Point[nPoint];
    for (int i = 0; i < nPoint; i++)
    {
        points[i].X = pll.getPoints()[i].getX();
        points[i].Y = pll.getPoints()[i].getY();
    }

    SolidBrush brush(Color(round(255 * pll.getFillOpacity()), pll.getFill().getRed(), pll.getFill().getGreen(), pll.getFill().getBlue()));
    graphics.FillPolygon(&brush, points, nPoint);
    Pen pen(Color(round(255 * pll.getStrokeOpacity()), pll.getStroke().getRed(), pll.getStroke().getGreen(), pll.getStroke().getBlue()), pll.getStrokeWidth());

    if (pll.getStrokeWidth() != 0)
        graphics.DrawLines(&pen, points, nPoint);

}

void Draw::drawShape(Graphics& graphics, vector<Shape*> shapesSVG)
{
    for (int i = 0; i < shapesSVG.size(); ++i)
    {
        GraphicsState origin = graphics.Save();
        if (shapesSVG[i]->getTypeName() == "rect") {
            RectangleSVG* rect = dynamic_cast<RectangleSVG*> (shapesSVG[i]);
            DrawRectangle(graphics, *rect);
        }

        else if (shapesSVG[i]->getTypeName() == "circle") {
            CircleSVG* cir = dynamic_cast<CircleSVG*> (shapesSVG[i]);
            DrawCircle(graphics, *cir);
        }

        else if (shapesSVG[i]->getTypeName() == "text") {
            TextSVG* txt = dynamic_cast<TextSVG*> (shapesSVG[i]);
            DrawText(graphics, *txt);
        }

        else if (shapesSVG[i]->getTypeName() == "line") {
            LineSVG* line = dynamic_cast<LineSVG*> (shapesSVG[i]);
            DrawLine(graphics, *line);
        }

        else if (shapesSVG[i]->getTypeName() == "ellipse") {
            EllipseSVG* ellip = dynamic_cast<EllipseSVG*> (shapesSVG[i]);
            DrawEllipse(graphics, *ellip);
        }

        else if (shapesSVG[i]->getTypeName() == "polygon") {
            PolygonSVG* polygon = dynamic_cast<PolygonSVG*> (shapesSVG[i]);
            DrawPolygon(graphics, *polygon);
        }
        else if (shapesSVG[i]->getTypeName() == "polyline") {
            PolylineSVG* polyline = dynamic_cast<PolylineSVG*> (shapesSVG[i]);
            DrawPolyline(graphics, *polyline);
        }
        else if (shapesSVG[i]->getTypeName() == "path") {
            PathSVG* path = dynamic_cast<PathSVG*> (shapesSVG[i]);
            DrawPath(graphics, *path);
        }
        else if (shapesSVG[i]->getTypeName() == "g") {
            GroupSVG* g = dynamic_cast<GroupSVG*> (shapesSVG[i]);
            drawShape(graphics, g->getVectorShape());
        }
        graphics.Restore(origin);
    }
}

void Draw::setDrew(bool x) {
    drew = x;
}
