#ifndef INTABLE_H
#define INTABLE_H

#include "ui.h"
#include <QTableWidget>
#include <QLabel>

class UI;

class InTable : public QTableWidget
{
    Q_OBJECT
public:
    InTable(UI* parent, InInvoice* IInvoice, bool IEditable = false);
private:
    int IDColumnNumber;
    int NameColumnNumber;
    int QuantityColumnNumber;
    int PriceColumnNumber;
    InInvoice* Invoice;
    void Add(int IIndex);
    void keyPressEvent(QKeyEvent *event);
    QString ReadedString;
    bool Editable;
    UI* Parent;
    QLabel* TotalLabel;
    QWidget* DockWidget;
public slots:
    void CellChanged(int IRow, int IColumn);
    void Apply();
    void Deapply();
    void Delete();
    void Close();
};

#endif // INTABLE_H
