#include "Polyline.h"

using namespace std;

PolylineSVG::PolylineSVG() {
    cout << "Polyline::Default Constructor" << endl;
}

vector<Point2D> PolylineSVG::getPoints()
{
    return this->points;
}

void PolylineSVG::buildPolyline(vector<char*> name, vector<char*> value, Properties polyline) {
    string temp;
    this->points.clear();
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "points") {
            string point = value[i];
            while (true) {
                string dup;
                int pos = point.find(' ');
                if (pos == string::npos) {
                    Point2D a(point);
                    this->points.push_back(a);
                    break;
                }

                dup = point.substr(0, pos);
                point.erase(0, pos + 1);
                Point2D a(dup);
                this->points.push_back(a);
            }
            break;
        }
    }
    this->shapeProps = polyline;
}

PolylineSVG::~PolylineSVG() {
    cout << "Polyline::Destructor" << endl;
}

void PolylineSVG::print() {
    for (int i = 0; i < this->points.size(); ++i) {
        this->points[i].print();
        cout << " ";
    }
    this->shapeProps.print();
}

sf::Vector2f PolylineSVG::getCenter() {
    sf::Vector2f p1 = sf::Vector2f(static_cast<float>(points[0].getX()), static_cast<float>(points[0].getY())),
        p2 = sf::Vector2f(static_cast<float>(points[0].getX()), static_cast<float>(points[0].getY())), p;
    for (Point2D a : points) {
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