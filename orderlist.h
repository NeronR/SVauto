#ifndef ORDERLIST_H
#define ORDERLIST_H

#include "order.h"

class OrderList
{
public:
    OrderList(QString IFolderName);
    void Load(QString IFolderName);
    OrderList& operator<< (Order& IOrder) {List<<IOrder; return *this;}
    Order& operator[] (int IIndex) {return List[IIndex];}
    int SearchByID(QString IID);
    int Size() {return List.length();}
    QString GetNextID();
    QString FolderName;
private:
    QList<Order> List;
};

#endif // ORDERLIST_H
