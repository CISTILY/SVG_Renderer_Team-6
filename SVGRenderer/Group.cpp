#include "Group.h"

GroupSVG::GroupSVG()
{
	this->g = new vector<ShapeData>;
	//(* g).clear(); not work
	cout << "Group::Default Constructor" << endl;
}

GroupSVG::~GroupSVG()
{
	//(*this->g).clear(); //not work
	//delete g; not work
	cout << "Group::Destructor" << endl;
}

FinalSVG GroupSVG::getG()
{
	return this->g;
}

void GroupSVG::print()
{
	Shape::print();
}
