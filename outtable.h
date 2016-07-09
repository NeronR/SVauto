#ifndef OUTTABLE_H
#define OUTTABLE_H

#include "ui.h"
#include <QTableWidget>
#include <QMenuBar>
#include <QLabel>

class OutTable: public QTableWidget
{
    Q_OBJECT
public:
    OutTable(UI* IParent, OutInvoice* IInvoice, bool IEditable = false);
    QMenuBar* MenuBar;
private:
    int IDColumnNumber;
    int NameColumnNumber;
    int QuantityColumnNumber;
    int PriceColumnNumber;
    OutInvoice* Invoice;
    void Add(int IIndex);
    void keyPressEvent(QKeyEvent *event);
    QString ReadedString;
    bool Editable;
    UI* Parent;
    QAction* ApplyAction;
    QLabel* TotalLabel;
public slots:
    void CellChanged(int IRow, int IColumn);
    void Apply();
    void Deapply();
    void Delete();

};

#endif // OUTTABLE_H
