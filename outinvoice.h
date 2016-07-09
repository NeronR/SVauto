#ifndef OUTINVOICE_H
#define OUTINVOICE_H

#include "initem.h"
#include "storage.h"
#include "outitem.h"

#include <QString>
#include <QList>
#include <QDateTime>

class OutInvoice
{
public:
    OutInvoice(QString IID);
    OutInvoice& operator<< (OutItem& IItem);
    OutItem& operator[] (int IIndex) {return ItemList[IIndex];}
    int Size() {return ItemList.size();}
    int SearchByID(QString IID);
    void Load(QString IFolder);
    void Save(QString IFolder);

    void SetDate(QDateTime IDateTime) {DateTime = IDateTime;}
    void SetApplied(bool IApplied) {Applied = IApplied;}

    QString GetID() {return ID;}
    long long GetTotal() {return Total;}
    QString GetTotalString() {return Utils::IntMoneyToString(Total);}
    long long RecalculateTotal();
    QString GetDateString() {return DateTime.toString(Utils::DATETIME_VISIBLE_FORMAT);}
    bool GetApplied() {return Applied;}
private:
    QList<OutItem> ItemList;
    QString ID;
    long long Total;
    QDateTime DateTime;
    bool Applied;
};

#endif // OUTINVOICE_H
