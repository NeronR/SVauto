#ifndef SERVICE_H
#define SERVICE_H

#include "utils.h"
#include <QString>
#include <QDomDocument>
#include <QDebug>
#include <QMap>

//TODO:
//Add CarID check when adding price

class ServicePriceTable;

class Service
{
public:
    Service(QString IID = "", QString IName = "", QString IBarcode = "",
            QString IDescription = "") : ID(IID),  Name(IName), Barcode(IBarcode),
        Description(IDescription)
    {}
    Service(QDomElement* IElement);

    QString GetID() {return ID;}
    QString GetName() {return Name;}
    QString GetBarcode() {return Barcode;}
    long long GetPrice(long long ICarID) {return Price.value(ICarID, -1);}
    QString GetPriceString(long long ICarID) {return Utils::IntMoneyToString(Price.value(ICarID, -1));}
    QString GetDescription() {return Description;}

    void SetID(QString IID) {ID = IID;}
    void SetName(QString IName) {Name = IName;}
    void SetBarcode(QString IBarcode) {Barcode = IBarcode;}
    void SetPrice(long long ICarID, long long IPrice){Price.insert(ICarID, IPrice);}
    void SetPrice(long long ICarID, QString IPrice)
        {if (Utils::StringIsMoney(IPrice)) Price.insert(ICarID,Utils::StringMoneyToInt(IPrice));}
    void RemovePrice(long long ICarID) {Price.remove(ICarID);}
    void SetDescription(QString IDescription) {Description = IDescription;}

    QDomElement ToXML(QDomDocument* IDocument);
private:
    QString ID;
    QString Name;
    QString Barcode;
    QMap<long long int, long long int> Price;
    QString Description;

    friend ServicePriceTable;
};

#endif // SERVICE_H
