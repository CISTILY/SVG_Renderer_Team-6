#include "Path.h"

using namespace std;

Path::Path() {
	cout << "Path::Constructor" << endl;
}

Path::~Path() {
	cout << "Path::Destructor" << endl;
}

void Path::setCommand(vector<char> command) {
	this->command = command;
}

void Path::setPoints(vector<Point2D> point) {
	this->Points = point;
}

vector<char> Path::getCommand() {
	return this->command;
}

vector<Point2D> Path::getPoints() {
	return this->Points;
}

void Path::buildShape(vector<char*> name, vector<char*> value) {
	vector<char> CommandType = { 'M', 'L', 'H', 'V', 'C', 'S', 'Q', 'T', 'A', 'Z' };
	string temp;
	this->Points.clear();
	for (int i = 0; i < name.size(); ++i) {
		temp = name[i];
		if (temp == "d") {
			string point = value[i];

			for (int j = 0; j < point.length(); ++j)
			{
				for (int k = 0; k < CommandType.size(); ++k)
				{
					if (point[j] == CommandType[k]) {
						this->command.push_back(CommandType[k]);
						point.erase(point.begin() + j);
						break;
					}
				}
			}

			while (true) {
				string dup;
				int pos = point.find(' ');
				if (pos == string::npos) {
					Point2D a(point);
					this->Points.push_back(a);
					break;
				}

				dup = point.substr(0, pos);
				point.erase(0, pos + 1);
				Point2D a(dup);
				this->Points.push_back(a);
			}
			break;
		}
	}
}

void Path::print() {
	for (int i = 0; i < this->command.size(); ++i) {
		cout << this->command[i] << " ";
		for (int j = 0; j < this->Points.size(); ++j) {
			this->Points[j].print();
			cout << "; ";
		}
		cout << endl;
	}
		
}