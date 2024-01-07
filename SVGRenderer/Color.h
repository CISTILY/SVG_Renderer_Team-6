#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class ColorSVG 
{
private:
	bool flagURL;
	string url;
	int red, green, blue;

	static vector<string>basic_color_name;
	static vector<string>basic_color_value;
public:
	// Constructor
	ColorSVG();

	// Destructor
	~ColorSVG();

	// Setters
	void setColor(string);

	// Getters
	int getRed();
	int getGreen();
	int getBlue();
	string getURL();
	bool getFlagURL();

	// Print data of color
	void print();

	int HexadecimalToDecimal(string);
	bool operator!= (const ColorSVG&);
};
