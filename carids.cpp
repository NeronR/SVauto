#include "carids.h"
#include "utils.h"

CarIDs::CarIDs(QDomElement *IElement)
{
//TODO
}
QDomElement CarIDs::ToXML(QDomDocument *IDocument)
{
    QDomElement RootElement = IDocument->createElement(Utils::XML_ROOT_TAG);
    for(int i=0; i<Brands.size(); ++i) //Brands cycle
    {
        QDomElement BrandElement = IDocument->createElement(Utils::XML_BRAND_TAG);
        BrandElement.setAttribute(Utils::XML_NAME_TAG, Brands[i].Name);
        for(int j=0; j<Brands[i].Models->size(); ++j) //Models cycle
        {
            QDomElement ModelElement = IDocument->createElement(Utils::XML_MODEL_TAG);
            ModelElement.setAttribute(Utils::XML_NAME_TAG, Brands[i].Models->at(j).Name);
            for(int k=0; k<Brands[i].Models->at(j).Versions->size(); ++k) // Versions cycle
            {
                QDomElement VersionElement = IDocument->createElement(Utils::XML_VERSION_TAG);
                VersionElement.setAttribute(Utils::XML_NAME_TAG, Brands[i].Models->at(j).Versions->at(k).Name);
                ModelElement.appendChild(VersionElement);
            }
            BrandElement.appendChild(ModelElement);
        }
        RootElement.appendChild(BrandElement);
    }
    return RootElement;
}

const short CarIDs::BRAND_ID_NUMBERS = 3;
const short CarIDs::MODEL_ID_NUMBERS = 2;
const short CarIDs::VERSION_ID_NUMBERS = 2;

