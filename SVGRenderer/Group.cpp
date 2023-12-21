#include "Group.h"

GroupSVG::GroupSVG()
{
	//cout << "Group::Default Constructor" << endl;
}

GroupSVG::~GroupSVG()
{
	//cout << "Group::Destructor" << endl;
}

vector<Shape*> GroupSVG::getVectorShape()
{
	return this->shapes;
}

vector<Shape*>* GroupSVG::getVectorShapeAddress()
{
	return &this->shapes;
}
