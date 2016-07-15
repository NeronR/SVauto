#ifndef STORAGETABLE_H
#define STORAGETABLE_H

#include "storage.h"
#include "ui.h"

#include <QTableWidget>

class UI;

class StorageTable : public QTableWidget
{
    Q_OBJECT
public:
    StorageTable(UI* Iparent, bool IEditable = false);
    ~StorageTable();
    void keyPressEvent(QKeyEvent *event);
private:
    Storage* MainStorage;
    UI* Parent;
    bool Editable;

    int IDColumnNumber;
    int NameColumnNumber;
    int BarcodeColumnNumber;
    int QuantityColumnNumber;
    int PurchasePriceColumnNumber;
    int MarkupColumnNumber;
    int SellingPriceColumnNumber;
    int DescriptionColumnNumber;
private slots:
    void CellChanged(int IRow, int IColumn);
    void Add();
    void Remove(int IRow);
    void RemoveCurrent();
    void Close();
};

#endif // STORAGETABLE_H
