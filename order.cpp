#include "order.h"
#include "outitem.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

Order::Order(QString IID) : ID(IID), Total(0), DateTime(QDateTime::currentDateTime()), CurrentState(State::NEGOTIATION)
{
    if(QFile(Utils::ORDERS_FOLDER + ID + Utils::FILENAME_EXTENSION).exists())
        Load(Utils::ORDERS_FOLDER);
}
void Order::AddItem(OutItem IItem)
{
    Total += IItem.GetPrice()*IItem.GetQuantity();
    ItemList<<IItem;
}
void Order::AddService(OutItem IItem)
{
    Total += IItem.GetPrice()*IItem.GetQuantity();
    ServiceList<<IItem;
}
void Order::Load(QString IFolder)
{
    QFile InputFile(IFolder + ID + Utils::FILENAME_EXTENSION);
    InputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument Document;
    Document.setContent(&InputFile);
    InputFile.close();
    QDomElement Root = Document.documentElement();
    if(Root.hasAttribute(Utils::XML_DATE_TAG))
        DateTime = QDateTime::fromString(Root.attribute(Utils::XML_DATE_TAG), Utils::DATETIME_FORMAT);
    if(Root.hasAttribute(Utils::XML_ID_TAG))
        ID = Root.attribute(Utils::XML_ID_TAG);
    if(Root.hasAttribute(Utils::XML_STATE_TAG))
        CurrentState = (State)Root.attribute(Utils::XML_STATE_TAG).toInt();
    QDomNode Node = Root.firstChild();
    QDomElement Element;
    while(!Node.isNull())
    {
        if(!(Element = Node.toElement()).isNull())
        {
            OutItem NewItem(&Element);
            if(Element.tagName()==Utils::XML_STORAGE_ITEM_TAG)
                AddItem(NewItem);
            else if(Element.tagName()==Utils::XML_SERVICE_TAG)
                AddService(NewItem);
            else
                QMessageBox::about(0,"ERROR!","NOT XML_STORAGE_ITEM_TAG OR XML_SERVICE_TAG");
        }
        else
            QMessageBox::about(0,"ERROR!","NOT XML_OUT_ITEM_TAG");
        Node=Node.nextSibling();
    }
}
void Order::Save(QString IFolder)
{
    QDomDocument Document;
    QDomElement Root = Document.createElement(Utils::XML_ROOT_TAG);
    Root.setAttribute(Utils::XML_DATE_TAG,DateTime.toString(Utils::DATETIME_FORMAT));
    Root.setAttribute(Utils::XML_ID_TAG,ID);
    Root.setAttribute(Utils::XML_STATE_TAG, (int)CurrentState);
    Document.appendChild(Root);

    for(int i=0; i<ItemList.length(); ++i)
    {
        QDomElement Appending = ItemList[i].ToXML(&Document);
        Appending.setTagName(Utils::XML_STORAGE_ITEM_TAG);
        Root.appendChild(Appending);
    }
    for(int i=0; i<ServiceList.length(); ++i)
    {
        QDomElement Appending = ServiceList[i].ToXML(&Document);
        Appending.setTagName(Utils::XML_SERVICE_TAG);
        Root.appendChild(Appending);
    }

    QFile OutputFile(IFolder+"/"+ID+Utils::FILENAME_EXTENSION);
    OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream OutStream(&OutputFile);
    OutStream << Document.toString();
    OutputFile.close();
}
int Order::SearchItemByID(QString IID)
{
    for(int i=0; i<ItemList.size(); ++i)
    {
        if(ItemList[i].GetID()==IID)
            return i;
    }
    return -1;
}
int Order::SearchServiceByID(QString IID)
{
    for(int i=0; i<ServiceList.size(); ++i)
    {
        if(ServiceList[i].GetID()==IID)
            return i;
    }
    return -1;
}
long long Order::RecalculateTotal()
{
    Total = 0;
    for(int i=0; i<ItemList.size(); ++i)
        Total += ItemList[i].GetPrice() * ItemList[i].GetQuantity();
    for(int i=0; i<ServiceList.size(); ++i)
        Total += ServiceList[i].GetPrice() * ItemList[i].GetQuantity();
    return Total;
}
