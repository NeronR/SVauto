#include "service.h"
#include "services.h"
#include <QDomDocument>

Service::Service(QDomElement *IElement) : Service()
{
    if(IElement && IElement->tagName()==Utils::XML_SERVICE_TAG)
    {
        if(IElement->hasAttribute(Utils::XML_ID_TAG))
            ID = IElement->attribute(Utils::XML_ID_TAG);
        if(IElement->hasAttribute(Utils::XML_NAME_TAG))
            Name = IElement->attribute(Utils::XML_NAME_TAG);
        if(IElement->hasAttribute(Utils::XML_BARCODE_TAG))
            Barcode = IElement->attribute(Utils::XML_BARCODE_TAG);
        for(int i=0; i<(Utils::CAR_MAX_ID + 1); ++i)
        {
            if(IElement->hasAttribute(Utils::XML_SELLING_PRICE_TAG + QString::number(i)))
                Price[i] = Utils::StringMoneyToInt(IElement->attribute(Utils::XML_SELLING_PRICE_TAG + QString::number(i)));
        }
        if(IElement->hasAttribute(Utils::XML_DESCRIPTION_TAG))
            Description = IElement->attribute(Utils::XML_DESCRIPTION_TAG);
    }
}
QDomElement Service::ToXML(QDomDocument *IDocument)
{
    QDomElement Element = IDocument->createElement(Utils::XML_SERVICE_TAG);
    Element.setAttribute(Utils::XML_ID_TAG, ID);
    Element.setAttribute(Utils::XML_NAME_TAG, Name);
    Element.setAttribute(Utils::XML_BARCODE_TAG, Barcode);
    for(int i=0; i<(Utils::CAR_MAX_ID + 1); ++i)
    {
        Element.setAttribute(Utils::XML_SELLING_PRICE_TAG + QString::number(i), Utils::IntMoneyToString(Price[i]));
    }
    Element.setAttribute(Utils::XML_DESCRIPTION_TAG, Description);
    return Element;
}
