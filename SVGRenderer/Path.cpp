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
	vector<int> sentinel;
	string temp = value[0];
	for (int i = 0; i < CommandType.size(); ++i) {
		for (int j = 0; j < temp.length(); ++j) {
			if (value[0][j] == CommandType[i]) {
				this->command.push_back(CommandType[i]);
			}
		}
	}

	for (int i = 0; i < temp.length(); ++i) {
		if (temp[i] >= 'A' && temp[i] <= 'Z' || temp[i] >= 'a' && temp[i] <= 'z')
			sentinel.push_back(i);
	}
	sentinel.push_back(temp.length() - 1);
	
	for (int i = 0; i < sentinel.size(); ++i) {
		cout << sentinel[i] << " ";
	}

	for (int i = 0; i < sentinel.size() - 1; ++i) {
		string point = temp.substr(sentinel[i] + 1, sentinel[i + 1]);
		cout << point << "-------------";
		/*while (true) {
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
		}*/
	}
}

void Path::print() {
	for (int i = 0; i < this->command.size(); ++i)
		cout << this->command[i] << " ";
}