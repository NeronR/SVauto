#include "ininvoice.h"
#include "storage.h"
#include "initem.h"
#include "utils.h"

#include <QFile>
#include <QDomDocument>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QDomText>

InInvoice::InInvoice(QString IID)
{
    Total = 0;
    DateTime = QDateTime::currentDateTime();
    Applied = false;
    ID = IID;
    if(QFile(Utils::OPENED_ININVOICES_FOLDER+"/"+ID+Utils::FILENAME_EXTENSION).exists())
        Load(Utils::OPENED_ININVOICES_FOLDER+"/");
    if(QFile(Utils::CLOSED_ININVOICES_FOLDER+"/"+ID+Utils::FILENAME_EXTENSION).exists())
        Load(Utils::CLOSED_ININVOICES_FOLDER+"/");
}
InInvoice& InInvoice::operator<< (InItem &IItem)
{
    Total += IItem.GetPrice()*IItem.GetQuantity();
    ItemList<<IItem;
    return *this;
}
InItem& InInvoice::operator[] (int IIndex)
{
    return ItemList[IIndex];
}
void InInvoice::Load(QString IFolder)
{
    QFile InputFile(IFolder+ID+Utils::FILENAME_EXTENSION);
    InputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument Document;
    Document.setContent(&InputFile);
    InputFile.close();
    QDomElement Root = Document.documentElement();
    if(Root.hasAttribute(Utils::XML_DATE_TAG))
        DateTime = QDateTime::fromString(Root.attribute(Utils::XML_DATE_TAG),Utils::DATETIME_FORMAT);
    if(Root.hasAttribute(Utils::XML_ID_TAG))
        ID = Root.attribute(Utils::XML_ID_TAG);
    if(Root.hasAttribute(Utils::XML_APPLIED_TAG))
        Applied = Utils::StringToBool(Root.attribute(Utils::XML_APPLIED_TAG));
    QDomNode Node = Root.firstChild();
    QDomElement Element;
    while(!Node.isNull())
    {
        if(!((Element = Node.toElement()).isNull()) && Element.tagName()==Utils::XML_IN_ITEM_TAG)
        {
            InItem NewItem(&Element);
            *this << NewItem;
        }
        else
            QMessageBox::about(0,"ERROR!","NOT XML_IN_ITEM_TAG");
        Node=Node.nextSibling();
    }
}
void InInvoice::Save(QString IFolder)
{
    QDomDocument Document;
    QDomElement Root = Document.createElement(Utils::XML_ROOT_TAG);
    Root.setAttribute(Utils::XML_DATE_TAG,DateTime.toString(Utils::DATETIME_FORMAT));
    Root.setAttribute(Utils::XML_ID_TAG,ID);
    Root.setAttribute(Utils::XML_APPLIED_TAG,Utils::BoolToString(Applied));
    Document.appendChild(Root);

    for(int i=0; i<ItemList.length(); ++i)
        Root.appendChild(ItemList[i].ToXML(&Document));

    QFile OutputFile(IFolder+"/"+ID+Utils::FILENAME_EXTENSION);
    OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream OutStream(&OutputFile);
    OutStream << Document.toString();
    OutputFile.close();
}
int InInvoice::Size()
{
    return ItemList.size();
}
int InInvoice::SearchByID(QString IID)
{
    for(int i=0; i<ItemList.size(); ++i)
    {
        if(ItemList[i].GetID()==IID)
            return i;
    }
    return -1;
}
long long InInvoice::RecalculateTotal()
{
    Total = 0;
    for(int i=0; i<ItemList.size(); ++i)
        Total += ItemList[i].GetPrice() * ItemList[i].GetQuantity();
    return Total;
}
