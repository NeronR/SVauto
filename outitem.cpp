#include "outitem.h"
#include "storage.h"
#include "utils.h"

OutItem::OutItem(QDomElement *IElement)
{
    OutItem();
    if(IElement && IElement->tagName() == Utils::XML_OUT_ITEM_TAG)
    {
        if(IElement->hasAttribute(Utils::XML_ID_TAG))
            ID = IElement->attribute(Utils::XML_ID_TAG);
        if(IElement->hasAttribute(Utils::XML_NAME_TAG))
            Name = IElement->attribute(Utils::XML_NAME_TAG);
        if(IElement->hasAttribute(Utils::XML_QUANTITY_TAG))
            Quantity = IElement->attribute(Utils::XML_QUANTITY_TAG).toInt();
        if(IElement->hasAttribute(Utils::XML_SELLING_PRICE_TAG))
            Price = Utils::StringMoneyToInt(IElement->attribute(Utils::XML_SELLING_PRICE_TAG));
        if(IElement->hasAttribute(Utils::XML_TYPE_TAG))
            Type = Utils::StringToBool(IElement->attribute(Utils::XML_TYPE_TAG));
        else
            Type = false;
    }
}
QDomElement OutItem::ToXML(QDomDocument *IDocument)
{
    QDomElement Element = IDocument->createElement(Utils::XML_OUT_ITEM_TAG);
    Element.setAttribute(Utils::XML_ID_TAG, ID);
    Element.setAttribute(Utils::XML_NAME_TAG, Name);
    Element.setAttribute(Utils::XML_QUANTITY_TAG, QString::number(Quantity));
    Element.setAttribute(Utils::XML_SELLING_PRICE_TAG, Utils::IntMoneyToString(Price));
    Element.setAttribute(Utils::XML_TYPE_TAG, Utils::BoolToString(Type));
    return Element;
}

