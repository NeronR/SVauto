#ifndef SERVICESTABLE_H
#define SERVICESTABLE_H

#include "services.h"
#include "ui.h"
#include "servicepricetable.h"

#include <QTableWidget>
#include <QPushButton>

class UI;

class ServicePointerButton : public QObject
{
    Q_OBJECT
public:
    ServicePointerButton(QString IText, Service* IPointer) : Button(new QPushButton(IText)), Pointer(IPointer)
    {connect(Button, SIGNAL(clicked(bool)), this, SLOT(Clicked()));}
    ~ServicePointerButton() {delete Button;}
    QPushButton* Button;
    Service* Pointer;
private slots:
    void Clicked() {emit Clicked(Pointer);}
signals:
    void Clicked(Service*);
};

class ServicesTable : public QTableWidget
{
    Q_OBJECT
public:
    ServicesTable(UI* IParent, bool IEditable = false);
    ~ServicesTable();
    void keyPressEvent(QKeyEvent* event);
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
    void PriceButtonClicked(Service* IService);

    friend ServicePriceTable;
};

#endif // SERVICESTABLE_H
