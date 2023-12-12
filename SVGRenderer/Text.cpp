#include "Text.h"

using namespace std;

TextSVG::TextSVG() {
    this->font_size = 0;
    this->dx = 0;
    this->dy = 0;
    this->font_family.push_back("Times new Roman");
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

vector<string> TextSVG::getFont_family()
{
    return this->font_family;
}

string TextSVG::getFont_style() 
{
    return this->font_style;
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
        else if (temp == "font-style")
            this->font_style = value[i];
        else if (temp == "font-family")
        {
            string font = value[i];
            
            while (true)
			{
				string dup;
				int pos = font.find(',');

				if (pos == string::npos)
				{
					this->font_family.push_back(font);
					break;
				}

				dup = font.substr(0, pos);
				font.erase(0, pos + 1);
				this->font_family.push_back(dup);
			}
        }
            
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
    cout << " " << dx << " " << dy << " " << this->font_size << " " << this->font_style << " ";
    for(int i = 0; i < this->font_family.size(); ++i)
        cout << this->font_family[i] << " ";
    cout << this->content << " ";
    Shape::print();
}
