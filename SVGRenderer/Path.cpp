#include "Path.h"

using namespace std;

PathSVG::PathSVG() {
	//cout << "Path::Constructor" << endl;
}

PathSVG::~PathSVG() {
	//cout << "Path::Destructor" << endl;
}

void PathSVG::setCommand(vector<char> command) {
	this->command = command;
}

void PathSVG::setPoints(vector<Point2D> point) {
	this->Points = point;
}

vector<char> PathSVG::getCommand() {
	return this->command;
}

vector<Point2D> PathSVG::getPoints() {
	return this->Points;
}

void PathSVG::replaceOnePoint(Point2D temp, int j) {
	for (int i = 0; i < this->Points.size(); ++i)
		if (i == j) {
			this->Points[j].setX(temp.getX());
			this->Points[j].setY(temp.getY());
		}
}

void PathSVG::buildShape(vector<char*> name, vector<char*> value)
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
				if(j > 0 && point[j] == '-')
					if (point[j - 1] >= '0' && point[j - 1] <= '9')
					{
						point.insert(j, " ");
						++j;
					}
			}

			if (point.find('.') != string::npos)
			{
				int posDotStart = point.find('.');
				int posDotEnd = point.find('.', posDotStart + 1);
				int k;
				while (posDotEnd != string::npos)
				{
					for (k = posDotStart + 1; k < posDotEnd; ++k)
						if (!isdigit(point[k]))
							break;

					if (k == posDotEnd)
					{
						point.insert(k, " 0");
						posDotStart = posDotEnd + 2;
						posDotEnd = point.find('.', posDotStart + 1);
					}
					else
					{
						posDotStart = posDotEnd;
						posDotEnd = point.find('.', posDotStart + 1);
					}
						
				}
			}

			for (int j = 0; j < point.length(); ++j)
			{
				if (point[j] == ' ' || point[j] == ',' || point[j] == '\n' || point[j] == '\t')
					continue;
				
				if ((point[j] < '0' || point[j] > '9') && point[j] != '.' && point[j] != '-')
				{
					command.push_back(point[j]);
					if (j + 1 < point.length() && point[j + 1] == ' ')
						point.erase(point.begin() + j + 1);
					++j;
				}
				else
				{
					if (toupper(command[command.size() - 1]) == 'M')
					{

						if (command[command.size() - 1] == toupper(command[command.size() - 1]))
							command.push_back('L');
						else
							command.push_back('l');
					}
					else
						command.push_back(command[command.size() - 1]);
				}


				int n = command.size() - 1, markStart = j, markEnd = 0, count = 0, numberOfXY = 0;

				if (toupper(command[n]) == 'A')
				{
					numberOfXY = 7;
				}
				else if (toupper(command[n]) == 'C')
				{
					numberOfXY = 6;
				}
				else if (toupper(command[n]) == 'S')
				{
					numberOfXY = 4;
				}
				else if (toupper(command[n]) == 'M' || toupper(command[n]) == 'L')
				{
					numberOfXY = 2;
				}
				else if (toupper(command[n]) == 'H' || toupper(command[n]) == 'V')
				{
					numberOfXY = 1;
				}
				else if (toupper(command[n]) == 'Z')
				{
					--j;
					continue;
				}

				for (; j < point.length(); ++j)
				{
					if ((point[j] < '0' || point[j] > '9') && point[j] != '.' && point[j] != '-')
						++count;
					if (count == numberOfXY)
					{
						markEnd = j - 1;
						if (point[j] != ' ' && point[j] != ',' && point[j] != '\n' && point[j] != '\t')
							--j;
						break;
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
				
				if (toupper(command[n]) == 'A')
				{
					int countXY = 0;
					int phiStart = 0, phiEnd;

					for (int k = 0; k < temp.length(); ++k)
					{
						if ((temp[k] < '0' || temp[k] > '9') && temp[k] != '.' && temp[k] != '-')
							++countXY;
						if (countXY == 2 && phiStart == 0)
						{
							phiStart = k;
						}
						if (countXY == 3)
						{
							phiEnd = k;
							break;
						}
					}
					
					string addPhi = temp.substr(phiStart, phiEnd - phiStart);
					temp.insert(phiEnd, addPhi);
				}

				while (true)
				{
					string dup;
					int pos = 0, flag = 0;

					for (int i = 0; i < temp.length(); ++i) {
						if (temp[i] == ' ' || temp[i] == ',' || temp[i] == '\n' || temp[i] == '\t') {
							if (flag == 0)
								++flag;
							else
							{
								pos = i;
								break;
							}
						}
					}						

					if (pos == 0)
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

void PathSVG::print() {
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
