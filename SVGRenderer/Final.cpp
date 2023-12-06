#include "Final.h"

FinalSVG::FinalSVG()
{
	cout << "FinalSVG::Default Constructor" << endl;
}

FinalSVG::~FinalSVG()
{
	this->final.clear();
	cout << "FinalSVG::Destructor" << endl;
}

vector<ShapeData> FinalSVG::getFinal()
{
    return this->final;
}

void FinalSVG::readFile(xml_node<>* node, string filename)
{
    ShapeData temp;
    int j = 0;
    static int i = 0;
    while (node != NULL) {

        SVGReader reader;
        xml_node<>* child = node->first_node();
        reader.setNodeName(node->name());
        reader.readContent(filename); // read all the text content


        // Read attributes and build properties
        for (xml_attribute<>* Attr = node->first_attribute(); Attr; Attr = Attr->next_attribute()) {
            char* attributeName = Attr->name();
            char* attributeValue = Attr->value();
            reader.PropertiesBuilder(attributeName, attributeValue);
        }

        /*cout << reader.getNodeName() << " ";
        for (int j = 0; j < reader.getPropsAttrName().size(); ++j)
            cout << reader.getPropsAttrName()[j] << " " << reader.getPropsAttrValue()[j] << " ";

        for (int j = 0; j < reader.getOtherAttrName().size(); ++j)
            cout << reader.getOtherAttrName()[j] << " " << reader.getOtherAttrValue()[j] << " ";

        cout << endl;*/

        string nameSVGReader = reader.getNodeName();
        if (!reader.getOtherAttrName().empty() || !reader.getPropsAttrName().empty() || nameSVGReader == "g") {
            this->final.push_back(temp);
            this->final[j].buildAndPrintShapeInfo(reader, i);
            j++;
        }

        if (child != NULL)
        {
            if (nameSVGReader == "g")
            {
                //vector<ShapeData> *childData = &(this->final[j - 1].getShape()->getG());
                //this->readFile(child, *childData, filename);

                //Khong hieu tai sao class group bien g phai la pointer chu khong dc bien thuong 
                this->readFile(child, *(this->final[j - 1].getShape()->getG()), filename);
            }
        }
        node = node->next_sibling();
    }
    cout << endl;
}