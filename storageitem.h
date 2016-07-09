#ifndef STORAGEITEM_H
#define STORAGEITEM_H

#include "utils.h"
#include <QString>
#include <QDomDocument>

class StorageItem
{
public:
    StorageItem(QString IID = "", QString IName = "", QString IBarcode = "",
         long long int IQuantity = 0, long long int ILastPurchasePrice = 0,
         long long int IMarkup = 0, long long int ISellingPrice = 0, QString IDescription = "");
    StorageItem(QDomElement* IElement);

    void SetID (QString IID) {ID=IID;}
    void SetName (QString IName) {Name=IName;}
    void SetBarcode (QString IBarcode) {Barcode=IBarcode;}
    void SetQuantity (long long int IQuantity) {Quantity=IQuantity;}
    void SetQuantity (QString IQuantity) {Quantity=IQuantity.toInt();}
    void SetLastPurchasePrice (long long int ILastPurchasePrice)
        {LastPurchasePrice=ILastPurchasePrice;CalculateSellingPrice();}
    void SetLastPurchasePrice (QString ILastPurchasePrice)
        {LastPurchasePrice = Utils::StringMoneyToInt(ILastPurchasePrice);CalculateSellingPrice();}
    void SetMarkup (long long IMarkup);
    void SetMarkup (QString IMarkup);
    void SetSellingPrice (long long int ISellingPrice);
    void SetSellingPrice (QString ISellingPrice);

    void IncreaseQuantity(long long IInt) {Quantity+=IInt;}

    QString GetID() {return ID;}
    QString GetName() {return Name;}
    QString GetBarcode() {return Barcode;}
    long long int GetQuantity() {return Quantity;}
    QString GetQuantityString() {return QString::number(Quantity);}
    long long int GetLastPurchasePrice() {return LastPurchasePrice;}
    QString GetLastPurchasePriceString() {return Utils::IntMoneyToString(LastPurchasePrice);}
    long long int GetMarkup() {return Markup;}
    QString GetMarkupString() {return Utils::IntMoneyToString(Markup);}
    long long int GetSellingPrice() {return SellingPrice;}
    QString GetSellingPriceString() {return Utils::IntMoneyToString(SellingPrice);}

    void CalculateSellingPrice();

    QDomElement ToXML(QDomDocument* IDocument);

private:
    QString ID;
    QString Name;
    QString Barcode;
    long long int Quantity;
    long long int LastPurchasePrice;
    long long int Markup;
    long long int SellingPrice;
    QString Description;
};

#endif // STORAGEITEM_H
