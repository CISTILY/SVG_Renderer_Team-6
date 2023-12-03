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

void Path::buildShape(vector<char*> name, vector<char*> value)
{
	string temp;
	this->Points.clear();
	for (int i = 0; i < name.size(); ++i)
	{
		temp = name[i];
		if (temp == "d")
		{
			string point = value[i];

			for (int j = 0; j < point.length(); ++j)
			{
				point[j] = toupper(point[j]);
				if(point[j] == ' ' || point[j] == ',' || point[j] == '\n')
					continue;
				
				if ((point[j] < '0' || point[j] > '9') && point[j] != '.' && point[j] != '-')
				{
					command.push_back(point[j]);
					if (j + 1 < point.length() && point[j + 1] == ' ')
						point.erase(point.begin() + j + 1);
					++j;
				}
				else
					command.push_back('L');


				int n = command.size() - 1, markStart = j, markEnd = 0, count = 0;

				if (toupper(command[n]) == 'C')
				{
					for (; j < point.length(); ++j)
					{
						if ((point[j] < '0' || point[j] > '9') && point[j] != '.' && point[j] != '-')
							++count;
						if (count == 6)
						{
							markEnd = j - 1;
							if (point[j] != ' ' && point[j] != ',' && point[j] != '\n')
								--j;
							break;
						}
					}
				}
				if (toupper(command[n]) == 'M' || toupper(command[n]) == 'L')
				{
					for (; j < point.length(); ++j)
					{
						if ((point[j] < '0' || point[j] > '9') && point[j] != '.' && point[j] != '-')
							++count;
						if (count == 2)
						{
							markEnd = j - 1;
							if (point[j] != ' ' && point[j] != ',' && point[j] != '\n')
								--j;
							break;
						}
					}
				}
				if (toupper(command[n]) == 'Z')
				{
					--j;
					continue;
				}
				if (toupper(command[n]) == 'H' || toupper(command[n]) == 'V')
				{
					for (; j < point.length(); ++j)
					{
						if ((point[j] < '0' || point[j] > '9') && point[j] != '.' && point[j] != '-')
							++count;
						if (count == 1)
						{
							markEnd = j - 1;
							if (point[j] != ' ' && point[j] != ',' && point[j] != '\n')
								--j;
							break;
						}
					}
				}

				string temp = point.substr(markStart, markEnd - markStart + 1);
				if (toupper(command[n]) == 'H')
				{
					if (temp.find(',') == string::npos)
						temp += " " + to_string(this->Points[this->Points.size() - 1].getY());
					else
						temp += "," + to_string(this->Points[this->Points.size() - 1].getY());
				}
					
				if (toupper(command[n]) == 'V')
				{
					if (temp.find(',') == string::npos)
						temp = to_string(this->Points[this->Points.size() - 1].getX()) + " " + temp;
					else
						temp = to_string(this->Points[this->Points.size() - 1].getX()) + "," + temp;
				}
					

				while (true)
				{
					string dup;
					int pos = temp.find(' ');

					if (temp.find(',') == string::npos)
					{
						pos = temp.find(' ', pos + 1);
					}

					if (pos == string::npos)
					{
						Point2D a(temp);
						this->Points.push_back(a);
						break;
					}

					dup = temp.substr(0, pos);
					temp.erase(0, pos + 1);
					Point2D a(dup);
					this->Points.push_back(a);
				}
			}
			break;
		}
	}
}
void Path::print() {
	for (int i = 0; i < this->command.size(); ++i) {
		cout << this->command[i] << " ";
	}
	cout << endl;
	for (int j = 0; j < this->Points.size(); ++j) {
		this->Points[j].print();
		cout << "; ";
	}
	cout << endl;
	Shape::print();
}
