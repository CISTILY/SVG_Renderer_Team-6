#pragma once
#include <iostream>
#include <string>

using namespace std;

class Color {
private:
	int red, green, blue;
public:
	// Constructor
	Color();

	// Destructor
	~Color();

	// Setters
	void setColor(string);

	// Getters
	int getRed();
	int getGreen();
	int getBlue();

	// Print data of color
	void print();

	bool operator!= (const Color&);
};