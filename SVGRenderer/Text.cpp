#include "Text.h"

using namespace std;

TextSVG::TextSVG() {
    this->font_size = 0;
    this->dx = 0;
    this->dy = 0;
    //cout << "Text::Constructor" << endl;
}

TextSVG::~TextSVG() {
    //cout << "Text::Destructor" << endl;
}

string TextSVG::getContent()
{
    return this->content;
}

int TextSVG::getFont_size()
{
    return this->font_size;
}

float TextSVG::getDx() 
{
    return this->dx;
}

float TextSVG::getDy()
{
    return this->dy;
}

string TextSVG::getAnchor()
{
    return this->text_anchor;
}

void TextSVG::buildShape(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "x")
            this->coordinate.setX(stof(value[i]));
        else if (temp == "y")
            this->coordinate.setY(stof(value[i]));
        else if (temp == "dx")
            this->dx = stof(value[i]);
        else if (temp == "dy")
            this->dy = stof(value[i]);
        else if (temp == "font-size")
            this->setFontSize(atoi(value[i]));
        else if (temp == "text-anchor")
            this->text_anchor = value[i];
        else if (temp == "font-family")
            this->font_family = value[i];
        else if (temp == "font-style")
            this->font_style = value[i];
    }
}

void TextSVG::setContent(string content) {
    this->content = content;
}

void TextSVG::setFontSize(int size) {
    this->font_size = size;
}

void TextSVG::print() {
    this->coordinate.print();
    cout << " " << dx << " " << dy << " " << this->font_size << " " << this->font_family << " " << this->font_style << " ";
    cout << this->content << " ";
    Shape::print();
}
