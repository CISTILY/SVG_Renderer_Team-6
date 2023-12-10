#include "Draw.h"

Draw::Draw()
{
	this->translate.setX(0);
	this->translate.setY(0);
	this->scalePoint.setX(1);
	this->scalePoint.setY(1);
	this->rotateAngle = 0;
	for (int i = 0; i < 3; i++) {
		this->TranslateRotateScale[i] = i;
	}
	//cout << "Draw::Default Constructor\n";
}

Draw::~Draw()
{
	//cout << "Draw::Destructor\n";
}

void Draw::findOrderTransform(string transform)
{
    int posTranslate = transform.find("translate");
    int posRotate = transform.find("rotate");
    int posScale = transform.find("scale");

    if (posTranslate == string::npos)
        posTranslate = transform.length();
    if (posRotate == string::npos)
        posRotate = transform.length();
    if (posScale == string::npos)
        posScale = transform.length();

    if (posTranslate <= posRotate && posTranslate <= posScale)
    {
        TranslateRotateScale[0] = 0;
        if (posRotate <= posScale)
        {
            TranslateRotateScale[1] = 1;
            TranslateRotateScale[2] = 2;
        }
        else
        {
            TranslateRotateScale[1] = 2;
            TranslateRotateScale[2] = 1;
        }
    }
    else if (posRotate <= posTranslate && posRotate <= posScale)
    {
        TranslateRotateScale[0] = 1;
        if (posTranslate <= posScale)
        {
            TranslateRotateScale[1] = 0;
            TranslateRotateScale[2] = 2;
        }
        else
        {
            TranslateRotateScale[1] = 2;
            TranslateRotateScale[2] = 0;
        }
    }
    else
    {
        TranslateRotateScale[0] = 2;
        if (posTranslate <= posRotate)
        {
            TranslateRotateScale[1] = 0;
            TranslateRotateScale[2] = 1;
        }
        else
        {
            TranslateRotateScale[1] = 1;
            TranslateRotateScale[2] = 0;
        }
    }
}


void Draw::splitString(string str) {
    string value;
    while (str != "") {
        if (str.find("translate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("translate") + 10, pos - 1 - 9);
            Point2D* temp = new Point2D(value);
            translate = *temp;
            str.erase(0, pos + 1);
            delete temp;
        }
        else if (str.find("rotate") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("rotate") + 7, pos - 1 - 6);
            rotateAngle = stof(value);
            str.erase(0, pos + 1);
        }
        else if (str.find("scale") != string::npos) {
            int pos = str.find(')');
            value = str.substr(str.find("scale") + 6, pos - 1 - 5);
            Point2D* temp = new Point2D(value);
            scalePoint = *temp;
            delete temp;
            str.erase(0, pos + 1);
        }
    }
}

void Draw::transform(Graphics& graphics, Shape* shape) {
    for (int i = 0; i < shape->getTransform().size(); ++i) {
        findOrderTransform(shape->getTransform()[i]);
        splitString(shape->getTransform()[i]);

        for (int j = 0; j < 3; ++j)
        {
            if (TranslateRotateScale[0] == j) {
                graphics.TranslateTransform(translate.getX(), translate.getY());
                translate.setX(0);
                translate.setY(0);
            }
            if (TranslateRotateScale[1] == j) {
                graphics.RotateTransform(rotateAngle);
                rotateAngle = 0;
            }
            if (TranslateRotateScale[2] == j) {
                graphics.ScaleTransform(scalePoint.getX(), scalePoint.getY());
                scalePoint.setX(1);
                scalePoint.setY(1);
            }
        }
    }
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
    Shape* shape = dynamic_cast<Shape*>(new TextSVG(text));
    transform(graphics, shape);

    GraphicsPath path;
    StringFormat strFormat;
    strFormat.SetAlignment(StringAlignmentNear);
    SolidBrush brush(Color(round(255 * text.getFillOpacity()), text.getFill().getRed(), text.getFill().getGreen(), text.getFill().getBlue()));
    FontFamily fontFamily(L"Times New Roman");
    Font font(&fontFamily, text.getFont_size(), 0, UnitPixel);
    PointF pointF(text.getCoordinateX() + text.getDx(), text.getCoordinateY() - text.getFont_size() + text.getDy());
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    wstring content = converter.from_bytes(text.getContent());
    path.AddString(content.c_str(), -1, &fontFamily, FontStyleRegular, static_cast<REAL>(text.getFont_size()), pointF, &strFormat);
    Pen pen(Color(round(255 * text.getStrokeOpacity()), text.getStroke().getRed(), text.getStroke().getGreen(), text.getStroke().getBlue()), text.getStrokeWidth());


    graphics.DrawString(content.c_str(), -1, &font, pointF, &brush);


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
    graphics.FillPolygon(&brush, points, nPoint);

    Pen pen(Color(round(255 * plg.getStrokeOpacity()), plg.getStroke().getRed(), plg.getStroke().getGreen(), plg.getStroke().getBlue()), plg.getStrokeWidth());
    if (plg.getStrokeWidth() != 0)
        graphics.DrawPolygon(&pen, points, nPoint);
}

VOID Draw::DrawPath(Graphics& graphics, PathSVG path)
{
    Shape* shape = dynamic_cast<Shape*>(new PathSVG(path));
    transform(graphics, shape);

    int nPath = path.getCommand().size();
    GraphicsPath* graphicsPath = new GraphicsPath[nPath];

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

void Draw::drawShape(Graphics& graphics, vector<ShapeData> data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        GraphicsState origin = graphics.Save();
        if (data[i].getTypeName() == "rect") {
            RectangleSVG* rect = dynamic_cast<RectangleSVG*> (data[i].getShape());
            DrawRectangle(graphics, *rect);
        }

        else if (data[i].getTypeName() == "circle") {
            CircleSVG* cir = dynamic_cast<CircleSVG*> (data[i].getShape());
            DrawCircle(graphics, *cir);
        }

        else if (data[i].getTypeName() == "text") {
            TextSVG* txt = dynamic_cast<TextSVG*> (data[i].getShape());
            DrawText(graphics, *txt);
        }

        else if (data[i].getTypeName() == "line") {
            LineSVG* line = dynamic_cast<LineSVG*> (data[i].getShape());
            DrawLine(graphics, *line);
        }

        else if (data[i].getTypeName() == "ellipse") {
            EllipseSVG* ellip = dynamic_cast<EllipseSVG*> (data[i].getShape());
            DrawEllipse(graphics, *ellip);
        }

        else if (data[i].getTypeName() == "polygon") {
            PolygonSVG* polygon = dynamic_cast<PolygonSVG*> (data[i].getShape());
            DrawPolygon(graphics, *polygon);
        }
        else if (data[i].getTypeName() == "polyline") {
            PolylineSVG* polyline = dynamic_cast<PolylineSVG*> (data[i].getShape());
            DrawPolyline(graphics, *polyline);
        }
        else if (data[i].getTypeName() == "path") {
            PathSVG* path = dynamic_cast<PathSVG*> (data[i].getShape());
            DrawPath(graphics, *path);
        }
        else if (data[i].getTypeName() == "g") {
            GroupSVG* g = dynamic_cast<GroupSVG*> (data[i].getShape());
            drawShape(graphics, *g->getG());
        }
        graphics.Restore(origin);
    }
}
