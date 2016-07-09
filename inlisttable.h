#ifndef INLISTTABLE_H
#define INLISTTABLE_H

#include "ui.h"
#include "ininvoicelist.h"
#include <QTableWidget>
#include <QMenuBar>

class InListTable : public QTableWidget
{
    Q_OBJECT
public:
    InListTable(UI* IParent, InInvoiceList* IList = 0);
    QMenuBar* MenuBar;
private:
    UI* Parent;
    InInvoiceList* List;
    int IDColumnNumber;
    int DateColumnNumber;
    int TotalColumnNumber;
private slots:
    void CellDoubleClick(int IRow);
};

#endif // INLISTTABLE_H
