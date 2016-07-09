#ifndef OUTLISTTABLE_H
#define OUTLISTTABLE_H

#include "ui.h"
#include "outinvoicelist.h"
#include <QMenuBar>
#include <QTableWidget>

class OutListTable : public QTableWidget
{
    Q_OBJECT
public:
    OutListTable(UI* IParent, OutInvoiceList* IList = 0);
    QMenuBar* MenuBar;
private:
    UI* Parent;
    OutInvoiceList* List;
    int IDColumnNumber;
    int DateColumnNumber;
    int TotalColumnNumber;
private slots:
    void CellDoubleClick(int IRow);
};

#endif // OUTLISTTABLE_H
