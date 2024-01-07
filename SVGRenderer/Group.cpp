#include "Group.h"

GroupSVG::GroupSVG()
{

}

GroupSVG::~GroupSVG()
{

}

vector<Shape*> GroupSVG::getVectorShape()
{
	return this->shapes;
}

vector<Shape*>* GroupSVG::getVectorShapeAddress()
{
	return &this->shapes;
}
