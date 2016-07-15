#ifndef OUTINVOICELIST_H
#define OUTINVOICELIST_H

#include "outinvoice.h"
#include <QList>

class OutInvoiceList
{
public:
    OutInvoiceList(QString IFolderName);
    void Load(QString IFolderName);
    OutInvoiceList& operator<< (OutInvoice& IInvoice) {InvoiceList<<IInvoice; return *this;}
    OutInvoice& operator[] (int IIndex) {return InvoiceList[IIndex];}
    int SearchByID(QString IID);
    int Size() {return InvoiceList.size();}
    QString GetNextID();
    QString FolderName;
private:
    QList<OutInvoice> InvoiceList;

};

#endif // OUTINVOICELIST_H
