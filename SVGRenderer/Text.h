#pragma once
#include "Shape.h"

class TextSVG : public Shape {
private:
    int font_size;
    string content;
public:
    TextSVG();
    ~TextSVG();

    string getContent();
    int getFont_size();
    void buildText(vector<char*>, vector<char*>, string);
    void setFontSize(int);
    void print() override;
};