#include "Group.h"

GroupSVG::GroupSVG()
{
	this->g = new vector<ShapeData>;
	//cout << "Group::Default Constructor" << endl;
}

GroupSVG::~GroupSVG()
{
	//cout << "Group::Destructor" << endl;
}

vector<ShapeData>* GroupSVG::getG()
{
	return this->g;
}

void GroupSVG::print()
{
	Shape::print();
}
