#ifndef INLISTTABLE_H
#define INLISTTABLE_H

#include "ui.h"
#include "ininvoicelist.h"
#include <QTableWidget>

class InListTable : public QTableWidget
{
    Q_OBJECT
public:
    InListTable(UI* IParent, InInvoiceList* IList = 0);
private:
    UI* Parent;
    QWidget* DockWidget;
    InInvoiceList* List;
    int IDColumnNumber;
    int DateColumnNumber;
    int TotalColumnNumber;
private slots:
    void CellDoubleClick(int IRow);
    void Close();
};

#endif // INLISTTABLE_H
