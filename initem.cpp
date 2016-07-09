#include "initem.h"
#include "storageitem.h"
#include "storage.h"
#include "utils.h"

#include <QDomDocument>

InItem::InItem(QDomElement *IElement)
{
    InItem();
    if(IElement && IElement->tagName()==Utils::XML_IN_ITEM_TAG)
    {
        if(IElement->hasAttribute(Utils::XML_ID_TAG))
            ID = IElement->attribute(Utils::XML_ID_TAG);
        if(IElement->hasAttribute(Utils::XML_NAME_TAG))
            Name = IElement->attribute(Utils::XML_NAME_TAG);
        if(IElement->hasAttribute(Utils::XML_QUANTITY_TAG))
            Quantity = IElement->attribute(Utils::XML_QUANTITY_TAG).toInt();
        if(IElement->hasAttribute(Utils::XML_PURCHASE_PRICE_TAG))
            Price = Utils::StringMoneyToInt(IElement->attribute(Utils::XML_PURCHASE_PRICE_TAG));
    }
}
QDomElement InItem::ToXML(QDomDocument *IDocument)
{
    QDomElement Element=IDocument->createElement(Utils::XML_IN_ITEM_TAG);
    Element.setAttribute(Utils::XML_ID_TAG, ID);
    Element.setAttribute(Utils::XML_NAME_TAG, Name);
    Element.setAttribute(Utils::XML_QUANTITY_TAG, QString::number(Quantity));
    Element.setAttribute(Utils::XML_PURCHASE_PRICE_TAG, Utils::IntMoneyToString(Price));
    return Element;
}
