#ifndef ORDER_H
#define ORDER_H

#include "outinvoice.h"
#include <QList>

class Order
{
public:
    Order();
private:
    enum State {NEGOTIATION, IN_PROGRESS, DONE, PAID, CANCELED};
    QList<OutItem> ItemList;
};

#endif // ORDER_H
