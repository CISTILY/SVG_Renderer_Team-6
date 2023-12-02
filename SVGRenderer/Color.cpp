#include "Color.h"

using namespace std;

Color::Color() {
    red = blue = green = 0;
    //cout << "Color::Default Constructor" << endl;
}

Color::~Color()
{
    //cout << "Color::Destructor" << endl;
}
int Color::HexadecimalToDecimal(string hex) {
        int hexLength = hex.length();
        double dec = 0;

        for (int i = 0; i < hexLength; ++i)
        {
            char b = hex[i];

            if (b >= 48 && b <= 57)
                b -= 48;
            else if (b >= 65 && b <= 70)
                b -= 55;

            dec += b * pow(16, ((hexLength - i) - 1));
        }

        return (int)dec;
}

void Color::setColor(string s) {
    if (s[0] == '#') {
        s = s.erase(0, 1);

        this->red = HexadecimalToDecimal(s.substr(0, 2));
        this->green = HexadecimalToDecimal(s.substr(2, 2));
        this->blue = HexadecimalToDecimal(s.substr(4, 2));
    }

    else {
        int pos = s.find(',');
        this->red = stoi(s.substr(4, pos));
        s.erase(0, pos + 1);

        pos = s.find(',');
        this->green = stoi(s.substr(0, pos));
        s.erase(0, pos + 1);

        this->blue = stoi(s.substr(0, s.length()));
    }
}

bool Color::operator!= (const Color& other) {
    return !(this->red == other.red && this->green == other.green && this->blue == other.blue);
} 

void Color::print() {
    cout << this->red << ", " << this->green << ", " << this->blue;
}

int Color::getRed() {
    return this->red;
}

int Color::getBlue() {
    return this->blue;
}

int Color::getGreen() {
    return this->green;
}