#ifndef STORAGETABLE_H
#define STORAGETABLE_H

#include "storage.h"
#include "ui.h"

#include <QTableWidget>
#include <QMenuBar>

class UI;

class StorageTable : public QTableWidget
{
    Q_OBJECT
public:
    StorageTable(UI* Iparent, bool IEditable = false);
    ~StorageTable();
    void keyPressEvent(QKeyEvent *event);
    QMenuBar* MenuBar;
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
//signals:
//public slots:
private slots:
    void CellChanged(int IRow, int IColumn);
    void Add();
    void Remove(int IRow);
    void RemoveCurrent();
    void Close();
};

#endif // STORAGETABLE_H
