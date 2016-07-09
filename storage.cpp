#include "storage.h"

#include <QFile>
#include <QDomDocument>
#include <QMessageBox>
#include <QTextStream>

Storage::Storage(QString IFileName)
{
    LastID = "1999999000000";
    Load(IFileName);
}
Storage& Storage::operator<< (StorageItem &IItem)
{
    if(ItemList.isEmpty() || ItemList.last().GetID()<IItem.GetID())
        ItemList<<IItem;
    else
    {
        int i;
        for(i=0; i<ItemList.length() && ItemList[i].GetID()<IItem.GetID(); ++i);
        ItemList.insert(i, IItem);
    }
    return *this;
}
StorageItem& Storage::operator[] (int IIndex)
{
    return ItemList[IIndex];
}
void Storage::Save(QString IFileName)
{
    QDomDocument Document;
    QDomElement Root = Document.createElement(Utils::XML_ROOT_TAG);
    Document.appendChild(Root);

    Root.setAttribute(Utils::XML_LAST_ID_TAG, LastID);
    for(int i=0; i<ItemList.length(); ++i)
        Root.appendChild(ItemList[i].ToXML(&Document));

    QFile OutputFile(IFileName);
    OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream OutStream(&OutputFile);
    OutStream << Document.toString();
    OutputFile.close();
}
void Storage::Load(QString IFileName)
{
    QFile InputFile(IFileName);
    InputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument Document;
    Document.setContent(&InputFile);
    InputFile.close();
    QDomElement Root = Document.documentElement();
    if(Root.hasAttribute(Utils::XML_LAST_ID_TAG))
        LastID = Root.attribute(Utils::XML_LAST_ID_TAG);
    else
        LastID = "1999999000000";
    QDomNode Node = Root.firstChild();
    QDomElement Element;

    while(!Node.isNull())
    {
        if(!((Element = Node.toElement()).isNull()) && Element.tagName()==Utils::XML_STORAGE_ITEM_TAG)
            *this << StorageItem(&Element);
        else
            QMessageBox::about(0,"ERROR!","NOT XML_STORAGE_ITEM_TAG");
        Node=Node.nextSibling();
    }
    if(!ItemList.empty() && LastID < ItemList.last().GetID())
        LastID = ItemList.last().GetID();
}
int Storage::Size()
{
    return ItemList.length();
}

long int Storage::SearchByID(QString IID)
{
    int i;
    for(i=0; i<Size() && ItemList[i].GetID()<IID; ++i);
    if(i==Size() || !(ItemList[i].GetID()==IID))
    {
        return -1;
    }
    else
        return i;
}
long int Storage::SearchByBarcode(QString IBarcode)
{
    int i;
    for(i=0; i<Size(); ++i)
    {
        if(ItemList[i].GetBarcode()==IBarcode)
            return i;
    }
    return -1;
}

void Storage::AddNew()
{
    QString NewID = LastID = GetNextID();
    (*this)<<StorageItem(NewID,"","",0,000,000,000,"");
    Save(Utils::STORAGE_FILENAME + Utils::FILENAME_EXTENSION);
}
void Storage::Remove(QString IID)
{
    ItemList.removeAt(SearchByID(IID));
    Save(Utils::STORAGE_FILENAME + Utils::FILENAME_EXTENSION);
}

QString Storage::GetNextID()
{
    QString NewLastID = LastID;
    for(int i=NewLastID.length()-1; i>-1; --i)
    {
        if(NewLastID[i] == '9')
        {
            NewLastID[i] = '0';
            continue;
        }
        if(NewLastID[i] == '0')
            NewLastID[i] = '1';
        else if(NewLastID[i] == '1')
            NewLastID[i] = '2';
        else if(NewLastID[i] == '2')
            NewLastID[i] = '3';
        else if(NewLastID[i] == '3')
            NewLastID[i] = '4';
        else if(NewLastID[i] == '4')
            NewLastID[i] = '5';
        else if(NewLastID[i] == '5')
            NewLastID[i] = '6';
        else if(NewLastID[i] == '6')
            NewLastID[i] = '7';
        else if(NewLastID[i] == '7')
            NewLastID[i] = '8';
        else if(NewLastID[i] == '8')
            NewLastID[i] = '9';
        break;
    }
    return NewLastID;
}
