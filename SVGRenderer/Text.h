#pragma once

#include "Shape.h"

class TextSVG : public Shape {
private:
    int font_size;
    float dx, dy;
    string text_anchor;
    string font_family;
    string font_style;
    string content;

public:
    // Constructor
    TextSVG();

    // Destructor
    ~TextSVG();

    // Getters
    string getContent();
    int getFont_size();
    float getDx();
    float getDy();
    string getAnchor();

    // Setters
    void setContent(string);
    void setFontSize(int);

    // Assign data function
    void buildShape(vector<char*>, vector<char*>) override;
    
    // Print data of Text
    void print() override;
};
