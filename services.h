#ifndef SERVICES_H
#define SERVICES_H

#include "service.h"
#include <QString>
#include <QList>

//TODO:
//Check ID when adding new service

class Services
{
public:
    Services(QString IFileName = "");
    Services& operator<< (Service& IService);
    Service& operator[] (int IIndex);
    int Size();
    void Save(QString IFileName);
    void Load(QString IFileName);
    int SearchByID(QString IID);
    int SearchByBarcode(QString IBarcode);
    QString GetNextID();
    void AddNew();
    void Remove(QString IID);
private:
    QList<Service> ServiceList;
    QString LastID;
};

#endif // SERVICES_H
