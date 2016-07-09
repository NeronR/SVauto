#ifndef ININVOICELIST_H
#define ININVOICELIST_H

#include "ininvoice.h"
#include <QList>

class InInvoiceList
{
public:
    InInvoiceList(QString IFolderName);
    void Load(QString IFolderName);
    InInvoiceList& operator<< (InInvoice& IInvoice) {InvoiceList<<IInvoice; return *this;}
    InInvoice& operator[] (int IIndex) {return InvoiceList[IIndex];}
    int SearchByID(QString IID);
    int Size() {return InvoiceList.size();}
    QString GetNextID();
private:
    QList<InInvoice> InvoiceList;
};

#endif // ININVOICELIST_H
