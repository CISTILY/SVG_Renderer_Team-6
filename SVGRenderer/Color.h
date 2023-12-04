#pragma once
#include <iostream>
#include <string>

using namespace std;

class ColorSVG {
private:
	int red, green, blue;
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

	// Print data of color
	void print();
	int HexadecimalToDecimal(string);
	bool operator!= (const ColorSVG&);
};