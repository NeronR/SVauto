#include "outinvoice.h"
#include "utils.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

OutInvoice::OutInvoice(QString IID)
{
    Total = 0;
    DateTime = QDateTime::currentDateTime();
    Applied = false;
    ID = IID;
    if(QFile(Utils::OPENED_OUTINVOICES_FOLDER+"/"+ID+Utils::FILENAME_EXTENSION).exists())
        Load(Utils::OPENED_OUTINVOICES_FOLDER+"/");
    if(QFile(Utils::CLOSED_OUTINVOICES_FOLDER+"/"+ID+Utils::FILENAME_EXTENSION).exists())
        Load(Utils::CLOSED_OUTINVOICES_FOLDER+"/");
}
OutInvoice& OutInvoice::operator << (OutItem& IItem)
{
    Total += IItem.GetPrice()*IItem.GetQuantity();
    ItemList<<IItem;
    return *this;
}
void OutInvoice::Load(QString IFolder)
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
        if(!((Element = Node.toElement()).isNull()) && Element.tagName()==Utils::XML_OUT_ITEM_TAG)
        {
            OutItem NewItem(&Element);
            *this << NewItem;
        }
        else
            QMessageBox::about(0,"ERROR!","NOT XML_OUT_ITEM_TAG");
        Node=Node.nextSibling();
    }
}
void OutInvoice::Save(QString IFolder)
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
int OutInvoice::SearchByID(QString IID)
{
    for(int i=0; i<ItemList.size(); ++i)
    {
        if(ItemList[i].GetID()==IID)
            return i;
    }
    return -1;
}
long long OutInvoice::RecalculateTotal()
{
    Total = 0;
    for(int i=0; i<ItemList.size(); ++i)
        Total += ItemList[i].GetPrice() * ItemList[i].GetQuantity();
    return Total;
}
