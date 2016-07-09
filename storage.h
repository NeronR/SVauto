#ifndef STORAGE_H
#define STORAGE_H

#include "storageitem.h"
#include <QList>

class Storage
{
public:
    explicit Storage(QString IFileName);
    Storage& operator<< (StorageItem &IItem);
    StorageItem& operator[] (int IIndex);
    void Save(QString IFileName);
    void Load(QString IFileName);
    int Size();
    long int SearchByID(QString IID);
    long int SearchByBarcode(QString IBarcode);
    QString GetNextID();
    void AddNew();
    void Remove(QString IID);
private:
    QList<StorageItem> ItemList;
    QString LastID;
};

#endif // STORAGE_H
