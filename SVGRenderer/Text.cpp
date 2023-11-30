#include "Text.h"

using namespace std;

TextSVG::TextSVG() {
    this->font_size = 0;

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

void TextSVG::buildShape(vector<char*> name, vector<char*> value) {
    string temp;
    for (int i = 0; i < name.size(); ++i) {
        temp = name[i];
        if (temp == "x")
            this->coordinate.setX(stof(value[i]));
        else if (temp == "y")
            this->coordinate.setY(stof(value[i]));
        else if (temp == "font-size")
            this->setFontSize(atoi(value[i]));
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
    cout << " " << this->font_size << " ";
    cout << this->content;
    Shape::print();
}