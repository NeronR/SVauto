#ifndef SERVICEPRICETABLE_H
#define SERVICEPRICETABLE_H

#include "servicestable.h"
#include "service.h"
#include "carids.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QMap>

class ServicesTable;

class ServicePriceTable : public QTableWidget
{
    Q_OBJECT
public:
    ServicePriceTable(ServicesTable* IParent, Service* IMainService, CarIDs* ICarIDs, bool IEditable);
private:
    ServicesTable* Parent;
    Service* MainService;
    CarIDs* MainCarIDs;
    bool Editable;

    int IDColumnNumber;
    int BrandColumnNumber;
    int ModelColumnNumber;
    int VersionColumnNumber;
    int PriceColumnNumber;

    int BrandID;
    int ModelID;
    int VersionID;
private slots:
    void CellChanged(int IRow, int IColumn);
    void Add();
    void Add2(int);
    void Add3(int);
    void Add4(int);
    void Remove(int IRow);
    void RemoveCurrent();
    void Close();
};

#endif // SERVICEPRICETABLE_H
