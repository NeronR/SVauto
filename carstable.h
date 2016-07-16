#ifndef CARSTABLE_H
#define CARSTABLE_H

#include <QTableWidget>
#include <QButtonGroup>
#include "carids.h"
#include "ui.h"

class CarsTable : public QTableWidget
{
    Q_OBJECT
public:
    CarsTable(UI* IParent, CarIDs* ICarIDs, long int IBrandID = -1, long int IModelID = -1);
private:
    UI* Parent;
    QWidget* DockWidget;
    CarIDs* MainCarIDs;
    QButtonGroup* Group;
    long int BrandID;
    long int ModelID;
    int IDColumnNumber;
    int NameColumnNumber;
    int OpenColumnNumber;
private slots:
    void CellChanged(int IRow, int IColumn);
    void Add();
    void Open(int IID);
    void Close();
};

#endif // CARSTABLE_H
