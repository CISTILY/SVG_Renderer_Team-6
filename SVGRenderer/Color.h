#pragma once
#include <iostream>
#include <string>

using namespace std;

class Color {
private:
	int red, green, blue;
public:
	Color();
	~Color();

	void setColor(string);
	void print();

	int getRed();
	int getGreen();
	int getBlue();
};