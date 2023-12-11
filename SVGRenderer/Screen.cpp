#include "Screen.h"

ScreenSVG::ScreenSVG()
{
    this->width = 0;
    this->height = 0;
    for (int i = 0; i < 4; ++i)
    {
        this->view_box[i] = 0;
    }    
    this->flagWidth = 0;
    this->flagHeight = 0;
    this->flagViewBox = 0;

    cout << "ScreenSVG::Default Constructor" << endl;
}

ScreenSVG::~ScreenSVG()
{
    cout << "ScreenSVG::Destructor" << endl;
}

void ScreenSVG::buildScreen(vector<char*> name, vector<char*> value)
{
    for(int i = 0; i < name.size(); ++i)
    {
        string temp = name[i];
        
        if (temp == "width")
        {
            this->width = stof(value[i]);
            this->flagWidth = 1;
        }
            
        else if (temp == "height")
        {
            this->height = stof(value[i]);
            this->flagHeight = 1;
        }
            
        else if (temp == "viewBox")
        {
            this->flagViewBox = 1;
            string strViewBox = value[i];
            string dup;
            
            for(int j = 0; j < 4; ++j)
            {
                int pos = strViewBox.find(' ');

                if (pos == string::npos)
                    pos = strViewBox.find(',');
            
                dup = strViewBox.substr(0, pos);
			          strViewBox.erase(0, pos + 1);
			          this->view_box[j] = stof(dup);
            }
        }
    }
}

void ScreenSVG::readScreen(xml_node<>* node)
{
    vector<char*>attributeName;
    vector<char*>attributeValue;
    
    for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) 
    {
        attributeName.push_back(Attr->name());
        attributeValue.push_back(Attr->value());
    }
    
    this->buildScreen(attributeName, attributeValue);
    this->printScreen();
}

void ScreenSVG::printScreen()
{
    if (this->flagWidth == 1 || this->flagHeight == 1 || this->flagViewBox == 1)
    {
        cout << "Screen:"
            << " width = " << this->width
            << " height = " << this->height
            << " viewBox = ";
        for (int i = 0; i < 4; ++i)
            cout << this->view_box[i] << " ";
        cout << endl << endl;
    }
}
