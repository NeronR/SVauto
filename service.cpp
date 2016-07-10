#include "service.h"
#include "services.h"
#include "carids.h"
#include <QDomDocument>
#include <QDebug>

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
        QDomNode PriceNode = IElement->firstChild();
        while(!PriceNode.isNull())
        {
            QDomElement PriceElement = PriceNode.toElement();
            if(PriceElement.tagName() == Utils::XML_SELLING_PRICE_TAG && PriceElement.hasAttribute(Utils::XML_ID_TAG) &&
                    PriceElement.hasAttribute(Utils::XML_SELLING_PRICE_TAG))
                Price.insert(PriceElement.attribute(Utils::XML_ID_TAG).toLongLong(),
                             Utils::StringMoneyToInt(PriceElement.attribute(Utils::XML_SELLING_PRICE_TAG)));
            else
                QMessageBox::about(0, "ERROR!", "XML_SELLING_PRICE_TAG ERROR");
            PriceNode = PriceNode.nextSibling();
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
    QMap<long long int, long long int>::const_iterator i = Price.constBegin();
    while(i != Price.constEnd())
    {
        QDomElement PriceElement = IDocument->createElement(Utils::XML_SELLING_PRICE_TAG);
        PriceElement.setAttribute(Utils::XML_ID_TAG, CarIDs::IntCarIDToString(i.key()));
        PriceElement.setAttribute(Utils::XML_SELLING_PRICE_TAG, Utils::IntMoneyToString(i.value()));
        Element.appendChild(PriceElement);
        ++i;
    }
    Element.setAttribute(Utils::XML_DESCRIPTION_TAG, Description);
    return Element;
}
