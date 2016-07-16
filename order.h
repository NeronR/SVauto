#ifndef ORDER_H
#define ORDER_H

#include "outinvoice.h"
#include <QList>
#include <QDateTime>

enum State {NEGOTIATION, IN_PROGRESS, DONE, PAID, CANCELED};

class Order
{
public:
    Order(QString IID);
    void AddItem (OutItem IItem);
    void AddService (OutItem IItem);
    int ItemSize() {return ItemList.length();}
    int ServiceSize() {return ServiceList.length();}
    void Load(QString IFolder);
    void Save(QString IFolder);
    void SetDate(QDateTime IDateTime) {DateTime = IDateTime;}
    void SetState(State IState) {CurrentState = IState;}
    QString GetID() {return ID;}
    long long GetTotal() {return Total;}
    QString ReturnTotalString() {return Utils::IntMoneyToString(Total);}
    void RecalculateTotal();
    QString GetDateString() {return DateTime.toString(Utils::DATETIME_VISIBLE_FORMAT);}
    State GetState() {return CurrentState;}
private:
    UI* Parent;
    QList<OutItem> ItemList;
    QList<OutItem> ServiceList;
    QString ID;
    long long Total;
    QDateTime DateTime;
    State CurrentState;
};

#endif // ORDER_H
