#include "Polyline.h"

using namespace std;

PolylineSVG::PolylineSVG() {
    //cout << "Polyline::Default Constructor" << endl;
}

vector<Point2D> PolylineSVG::getPoints()
{
    return this->points;
}

void PolylineSVG::buildShape(vector<char*> name, vector<char*> value) {
    string temp;
    this->points.clear();
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "points") {
            string point = value[i];;

            while (!isdigit(point[point.length() - 1]))
                point.erase(point.length() - 1, 1);

            while (true) {
                string dup;
                int flag = 0, pos = 0;

                for (int j = 0; j < point.length(); ++j)
                    if (point[j] == ' ' || point[j] == ',')
                    {
                        if(flag == 0)
                            ++flag;
                        else
                        {
                            pos = j;
                            break;
                        }
                    
                    }
                        
                if (pos == 0) {
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
}

PolylineSVG::~PolylineSVG() {
    //cout << "Polyline::Destructor" << endl;
}

void PolylineSVG::print() {
    
    for (int i = 0; i < this->points.size(); ++i) {
        this->points[i].print();
        cout << "; ";
    }
    Shape::print();
}
