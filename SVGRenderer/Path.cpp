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
	vector<char> CommandType = { 'M', 'L', 'H', 'V', 'C', 'S', 'Q', 'T', 'A', 'Z' };
	string temp;
	this->Points.clear();
	for (int i = 0; i < name.size(); ++i)
	{
		temp = name[i];
		if (temp == "d")
		{
			string point = value[i];

			for (int j = 0; j < point.length(); ++j)
				for (int k = 0; k < CommandType.size(); ++k)
					if (point[j] == CommandType[k])
					{
						command.push_back(CommandType[k]);

						if (point[j] == 'H')
						{
							string duplicateY;
							int mark, posInsert = j;

							for (int l = j - 2; l >= 0; --l)
								if (point[l] == ',' || point[l] == ' ')
								{
									mark = l;
									break;
								}

							duplicateY = point.substr(mark, j - 1 - mark);

							for (; posInsert < point.length(); ++posInsert)
								if (point[posInsert] == ' ' && posInsert > j + 1)
									break;
							point.insert(posInsert, duplicateY);
						}

						if (point[j] == 'V')
						{
							string duplicateX;
							int markStart, markEnd = 0;

							for (int l = j - 2; l >= 0; --l)
								if (point[l] == ',' || point[l] == ' ')
								{
									if (markEnd == 0)
										markEnd = l;
									else
									{
										markStart = l + 1;
										break;
									}
								}

							duplicateX = point.substr(markStart, markEnd - markStart + 1);

							if (point[j + 1] == ' ')
								point.insert(j + 2, duplicateX);
							else
								point.insert(j + 1, duplicateX);
						}


						if (j + 1 < point.length() && point[j + 1] == ' ')
							point.erase(j, 2);
						else
							point.erase(point.begin() + j);
						--j;

						break;
					}

			if (point[point.length() - 1] == ' ')
				point.erase(point.begin() + point.length() - 1);


			while (true)
			{
				string dup;
				int pos = point.find(' ');

				if (point.find(',') == string::npos)
				{
					pos = point.find(' ', pos + 1);
				}

				if (pos == string::npos)
				{
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