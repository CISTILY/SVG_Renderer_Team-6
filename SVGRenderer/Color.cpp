#include "Color.h"

using namespace std;

ColorSVG::ColorSVG() {
    red = blue = green = 0;
    //cout << "Color::Default Constructor" << endl;
}

ColorSVG::~ColorSVG()
{
    //cout << "Color::Destructor" << endl;
}
int ColorSVG::HexadecimalToDecimal(string hex) {
    int decimalValue = 0;

    // Iterate through each character in the hexadecimal string
    for (int i = hex.size() - 1; i >= 0; --i) {
        char digit = hex[i];

        // Convert hexadecimal digit to decimal equivalent
        int digitValue;
        if (isdigit(digit)) {
            digitValue = digit - '0';
        }
        else {
            digitValue = toupper(digit) - 'A' + 10;
        }

        // Update the decimal value
        decimalValue += digitValue * pow(16, hex.size() - 1 - i);
    }

    return decimalValue;
}

void ColorSVG::setColor(string s) {
    if (s[0] == '#') {
        s = s.erase(0, 1);

        this->red = HexadecimalToDecimal(s.substr(0, 2));
        this->green = HexadecimalToDecimal(s.substr(2, 2));
        this->blue = HexadecimalToDecimal(s.substr(4, 2));
    }

    else if (s == "black")
        this->red = this->blue = this->green = 0;

    else if (s == "yellow") {
        this->red = this->green = 255;
        this->blue = 0;;
    }

    else if (s == "blue") {
        this->red = this->green = 0;
        this->blue = 255;
    }

    else if (s == "green") {
        this->red = this->blue = 0;
        this->green = 255;
    }
        
    else if (s == "red") {
        this->green = this->blue = 0;
        this->red = 255;
    }

    else if (s == "darkslategray") {
        this->green = this->blue = 79;
        this->red = 47;
    }

    else if (s == "grey") {
        this->red = this->green = this->blue = 128;
    }

    else if (s == "blueviolet") {
        this->red = 138;
        this->green = 43;
        this->blue = 226;
    }

    else if (s == "midnightblue") {
        this->red = 25;
        this->green = 25;
        this->blue = 112;
    }

    else if (s == "CYAN") {
        this->red = 0;
        this->green = 255;
        this->blue = 255;
    }

    else if (s == "navy") {
        this->red = 0;
        this->green = 0;
        this->blue = 128;
    }
  
    else if (s == "deepskyblue") {
        this->red = 0;
        this->green = 191;
        this->blue = 255;
    }

    else if (s == "darkmagenta") {
        this->red = 139;
        this->green = 0;
        this->blue = 139;
    }

    else if (s == "purple") {
        this->red = 128;
        this->green = 0;
        this->blue = 128;
    }

    else if (s == "white") {
        this->red = 255;
        this->blue = 255;
        this->green = 255;
    }

    else if (s == "skyblue") {
        this->red = 135;
        this->green = 206;
        this->blue = 235;
    }

    else {
        int tempColor = 0;

        int pos = s.find(',');
        tempColor = stoi(s.substr(4, pos));
        if (tempColor > 255)
            tempColor = 255;

        this->red = tempColor;
        s.erase(0, pos + 1);

        pos = s.find(',');
        tempColor = stoi(s.substr(0, pos));
        if (tempColor > 255)
            tempColor = 255;

        this->green = tempColor;
        s.erase(0, pos + 1);

        tempColor = stoi(s.substr(0, s.length()));
        if (tempColor > 255)
            tempColor = 255;

        this->blue = tempColor;
    }
}

bool ColorSVG::operator!= (const ColorSVG& other) {
    return !(this->red == other.red && this->green == other.green && this->blue == other.blue);
} 

void ColorSVG::print() {
    cout << this->red << ", " << this->green << ", " << this->blue;
}

int ColorSVG::getRed() {
    return this->red;
}

int ColorSVG::getBlue() {
    return this->blue;
}

int ColorSVG::getGreen() {
    return this->green;
}
