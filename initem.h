#ifndef INITEM_H
#define INITEM_H

#include "storageitem.h"

#include <QString>
#include <QDomElement>

class InItem
{
public:
    InItem(QString IID = "", QString IName = "", long long IQuantity = 0, long long IPrice = 0):
        ID(IID), Name(IName), Quantity(IQuantity), Price(IPrice)
    {}
    InItem(QDomElement* IElement);

    QString GetID(){return ID;}
    QString GetName(){return Name;}
    long long GetQuantity(){return Quantity;}
    QString GetQuantityString(){return QString::number(Quantity);}
    long long GetPrice(){return Price;}
    QString GetPriceString(){return Utils::IntMoneyToString(Price);}

    void QuantityInc() {++Quantity;}
    void SetQuantity(QString IQuantity) {Quantity = IQuantity.toInt();}
    void SetPrice(QString IPrice) {Price = Utils::StringMoneyToInt(IPrice);}

    QDomElement ToXML (QDomDocument* IDocument);
private:
    QString ID;
    QString Name;
    long long Quantity;
    long long Price;
};

#endif // INITEM_H
