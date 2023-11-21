#pragma once

#include "Shape.h"

class TextSVG : public Shape {
private:
    int font_size;
    string content;
public:
    // Constructor
    TextSVG();

    // Destructor
    ~TextSVG();

    // Getters
    string getContent();
    int getFont_size();

    // Setters
    void setFontSize(int);

    // Assign data function
    void buildText(vector<char*>, vector<char*>, string);
    
    // Print data of Text
    void print() override;
};