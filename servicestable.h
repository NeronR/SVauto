#ifndef SERVICESTABLE_H
#define SERVICESTABLE_H

#include "services.h"
#include "ui.h"

#include <QTableWidget>
#include <QMenuBar>

class UI;

class ServicesTable : public QTableWidget
{
    Q_OBJECT
public:
    ServicesTable(UI* IParent, bool IEditable = false);
    ~ServicesTable();
    void keyPressEvent(QKeyEvent* event);
    QMenuBar* MenuBar;
private:
    Services* MainServices;
    UI* Parent;
    bool Editable;

    int IDColumnNumber;
    int NameColumnNumber;
    int BarcodeColumnNumber;
    int PriceColumnNumber;
    int DescriptionColumnNumber;
private slots:
    void CellChanged(int IRow, int IColumn);
    void Add();
    void Remove(int IRow);
    void RemoveCurrent();
    void Close();
};

#endif // SERVICESTABLE_H
