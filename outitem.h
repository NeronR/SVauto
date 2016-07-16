#ifndef OUTITEM_H
#define OUTITEM_H

#include "storageitem.h"

#include <QString>
#include <QDomElement>

class OutItem
{
public:
    OutItem(QString IID = "", QString IName = "", long long IQuantity = 0, long long IPrice = 0, bool IsTypeService = false):
        ID(IID), Name(IName), Quantity(IQuantity), Price(IPrice), Type(IsTypeService)
    {}
    OutItem(QDomElement* IElement);

    QString GetID() {return ID;}
    QString GetName() {return Name;}
    long long GetQuantity() {return Quantity;}
    QString GetQuantityString() {return QString::number(Quantity);}
    long long GetPrice() {return Price;}
    QString GetPriceString() {return Utils::IntMoneyToString(Price);}
    bool GetType() {return Type;}

    void QuantityInc() {++Quantity;}
    void SetQuantity(QString IQuantity) {Quantity = IQuantity.toInt();}
    void SetPrice(QString IPrice) {Price = Utils::StringMoneyToInt(IPrice);}
    void SetType(bool IType) {Type = IType;}

    QDomElement ToXML (QDomDocument* IDocument);
private:
    QString ID;
    QString Name;
    long long Quantity;
    long long Price;
    bool Type; //false - item, true - service
};

#endif // OUTITEM_H
