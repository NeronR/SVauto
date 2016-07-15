#ifndef OUTLISTTABLE_H
#define OUTLISTTABLE_H

#include "ui.h"
#include "outinvoicelist.h"
#include <QTableWidget>

class OutListTable : public QTableWidget
{
    Q_OBJECT
public:
    OutListTable(UI* IParent, OutInvoiceList* IList = 0);
private:
    UI* Parent;
    QWidget* DockWidget;
    OutInvoiceList* List;
    int IDColumnNumber;
    int DateColumnNumber;
    int TotalColumnNumber;
private slots:
    void CellDoubleClick(int IRow);
    void Update();
    void Close();
};

#endif // OUTLISTTABLE_H
