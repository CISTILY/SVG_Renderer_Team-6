#include "Polygon.h"

using namespace std;

PolygonSVG::PolygonSVG() 
{

}

PolygonSVG::~PolygonSVG() 
{

}

void PolygonSVG::buildShape(vector<char*> name, vector<char*> value) 
{
    PolylineSVG::buildShape(name, value);
}
