#ifndef ININVOICE_H
#define ININVOICE_H

#include "initem.h"
#include "storage.h"

#include <QString>
#include <QList>
#include <QDateTime>

class InInvoice
{
public:
    InInvoice(QString IID);
    InInvoice& operator<< (InItem &IItem);
    InItem& operator[] (int IIndex);
    int Size();
    int SearchByID(QString IID);
    void Load(QString IFolder);
    void Save(QString IFolder);

    void SetDate (QDateTime IDateTime){DateTime = IDateTime;}
    void SetApplied(bool IApplied){Applied = IApplied;}

    QString GetID() {return ID;}
    QString GetDateString() {return DateTime.toString(Utils::DATETIME_VISIBLE_FORMAT);}
    long long GetTotal(){return Total;}
    QString GetTotalString() {return Utils::IntMoneyToString(Total);}
    bool GetApplied() {return Applied;}
    long long RecalculateTotal();
private:
    QList<InItem> ItemList;
    QString ID;
    long long Total;
    QDateTime DateTime;
    bool Applied;
};

#endif // ININVOICE_H
