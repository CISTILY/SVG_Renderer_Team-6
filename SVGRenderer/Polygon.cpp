#include "Polygon.h"

using namespace std;

PolygonSVG::PolygonSVG() {
    //cout << "Polygon::Default Constructor" << endl;
}

PolygonSVG::~PolygonSVG() {
    //cout << "Polygon::Destructor" << endl;
}

void PolygonSVG::buildShape(vector<char*> name, vector<char*> value) {
    PolylineSVG::buildShape(name, value);
}
