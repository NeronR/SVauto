#include "storageitem.h"
#include "storage.h"
#include "utils.h"

#include <QDomDocument>
#include <QMessageBox>

StorageItem::StorageItem(QString IID, QString IName, QString IBarcode, long long IQuantity,
                         long long ILastPurchasePrice, long long IMarkup,
                         long long ISellingPrice,/*, bool IPriority*/ QString IDescription):
    ID(IID), Name(IName), Barcode(IBarcode), Quantity(IQuantity), LastPurchasePrice(ILastPurchasePrice),
    Markup (IMarkup), SellingPrice(ISellingPrice),/*, Priority(IPriority)*/Description(IDescription)
{}
StorageItem::StorageItem(QDomElement *IElement)
{
    StorageItem();
    if(IElement && IElement->tagName()==Utils::XML_STORAGE_ITEM_TAG)
    {
        if(IElement->hasAttribute(Utils::XML_ID_TAG))
            ID = IElement->attribute(Utils::XML_ID_TAG);

        if(IElement->hasAttribute(Utils::XML_NAME_TAG))
            Name = IElement->attribute(Utils::XML_NAME_TAG);

        if(IElement->hasAttribute(Utils::XML_BARCODE_TAG))
            Barcode = IElement->attribute(Utils::XML_BARCODE_TAG);

        if(IElement->hasAttribute(Utils::XML_QUANTITY_TAG))
            Quantity = IElement->attribute(Utils::XML_QUANTITY_TAG).toInt();

        if(IElement->hasAttribute(Utils::XML_PURCHASE_PRICE_TAG))
            LastPurchasePrice = Utils::StringMoneyToInt(IElement->attribute(Utils::XML_PURCHASE_PRICE_TAG));

        if(IElement->hasAttribute(Utils::XML_MARKUP_TAG))
            Markup = Utils::StringMoneyToInt(IElement->attribute(Utils::XML_MARKUP_TAG));

        if(IElement->hasAttribute(Utils::XML_SELLING_PRICE_TAG))
            SellingPrice = Utils::StringMoneyToInt(IElement->attribute(Utils::XML_SELLING_PRICE_TAG));

        if(IElement->hasAttribute(Utils::XML_DESCRIPTION_TAG))
            Description = IElement->attribute(Utils::XML_DESCRIPTION_TAG);
    }
}

QDomElement StorageItem::ToXML(QDomDocument* IDocument)
{
    QDomElement Element=IDocument->createElement(Utils::XML_STORAGE_ITEM_TAG);
    Element.setAttribute(Utils::XML_ID_TAG, ID);
    Element.setAttribute(Utils::XML_NAME_TAG, Name);
    Element.setAttribute(Utils::XML_BARCODE_TAG, Barcode);
    Element.setAttribute(Utils::XML_QUANTITY_TAG, QString::number(Quantity));
    Element.setAttribute(Utils::XML_PURCHASE_PRICE_TAG, Utils::IntMoneyToString(LastPurchasePrice));
    Element.setAttribute(Utils::XML_MARKUP_TAG, Utils::IntMoneyToString(Markup));
    Element.setAttribute(Utils::XML_SELLING_PRICE_TAG, Utils::IntMoneyToString(SellingPrice));
    Element.setAttribute(Utils::XML_DESCRIPTION_TAG, Description);
    return Element;
}

void StorageItem::SetMarkup (long long IMarkup)
{
    Markup=IMarkup;
    double NewSellingPrice = (double)LastPurchasePrice*(double)Markup;
    NewSellingPrice /= 10000;
    SellingPrice=(LastPurchasePrice+(long long)NewSellingPrice)/1000*1000;
}
void StorageItem::SetMarkup (QString IMarkup)
{
    Markup = Utils::StringMoneyToInt(IMarkup);
    double NewSellingPrice = (double)LastPurchasePrice*(double)Markup;
    NewSellingPrice /= 10000;
    SellingPrice=(LastPurchasePrice+(long long)NewSellingPrice)/1000*1000;
}
void StorageItem::SetSellingPrice(long long ISellingPrice)
{
    SellingPrice = ISellingPrice;
    double NewMarkup = (SellingPrice/LastPurchasePrice)-1;
    NewMarkup *= 10000;
    Markup = NewMarkup;
}
void StorageItem::SetSellingPrice(QString ISellingPrice)
{
    SellingPrice = Utils::StringMoneyToInt(ISellingPrice);
    double NewMarkup = ((double)SellingPrice/(double)LastPurchasePrice)-1;
    NewMarkup *= 10000;
    Markup = NewMarkup;
}

void StorageItem::CalculateSellingPrice()
{
    SetMarkup(Markup);
}
