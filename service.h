#ifndef SERVICE_H
#define SERVICE_H

#include "utils.h"
#include <QString>
#include <QDomDocument>
#include <QDebug>

class Service
{
public:
    Service(QString IID = "", QString IName = "", QString IBarcode = "", long long IPrice = 0,
            QString IDescription = "") : ID(IID),  Name(IName), Barcode(IBarcode),
        Description(IDescription)
    {
        Price = new long long int[Utils::CAR_MAX_ID + 1];
        /*for (int i=0; i<(Utils::CAR_MAX_ID + 1); ++i)
        {
            Price[i] = IPrice;
            qDebug()<<i;
        }*/
    }
    Service(QDomElement* IElement);

    QString GetID() {return ID;}
    QString GetName() {return Name;}
    QString GetBarcode() {return Barcode;}
    long long GetPrice(long long ICarID) {return Price[ICarID];}
    QString GetPriceString(long long ICarID) {return Utils::IntMoneyToString(Price[ICarID]);}
    QString GetDescription() {return Description;}

    void SetID(QString IID) {ID = IID;}
    void SetName(QString IName) {Name = IName;}
    void SetBarcode(QString IBarcode) {Barcode = IBarcode;}
    void SetPrice(long long ICarID, long long IPrice) {Price[ICarID] = IPrice;}
    void SetPrice(long long ICarID, QString IPrice)
        {if (Utils::StringIsMoney(IPrice)) Price[ICarID] = Utils::StringMoneyToInt(IPrice);}
    void SetDescription(QString IDescription) {Description = IDescription;}

    QDomElement ToXML(QDomDocument* IDocument);
private:
    QString ID;
    QString Name;
    QString Barcode;
    long long int* Price;
    QString Description;
};

#endif // SERVICE_H
