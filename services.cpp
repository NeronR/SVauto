#include "services.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Services::Services(QString IFileName)
{
    LastID = "200000";
    if (QFile(IFileName).exists())
            Load(IFileName);
}
Services& Services::operator<< (Service& IService)
{
    if(ServiceList.empty() || ServiceList.last().GetID()<IService.GetID())
        ServiceList<<IService;
    else
    {
        int i;
        for(i=0; i<ServiceList.length() && ServiceList[i].GetID()<IService.GetID(); ++i);
        ServiceList.insert(i, IService);
    }
    return *this;
}
Service& Services::operator[] (int IIndex)
{
    return ServiceList[IIndex];
}
int Services::Size()
{
    return ServiceList.length();
}
void Services::Save(QString IFileName)
{
    QDomDocument Document;
    QDomElement Root = Document.createElement(Utils::XML_ROOT_TAG);
    Document.appendChild(Root);

    Root.setAttribute(Utils::XML_LAST_ID_TAG, LastID);
    for(int i=0; i<ServiceList.length(); ++i)
        Root.appendChild(ServiceList[i].ToXML(&Document));

    QFile OutputFile(IFileName);
    OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream OutStream(&OutputFile);
    OutStream << Document.toString();
    OutputFile.close();
}
void Services::Load(QString IFileName)
{
    QFile InputFile(IFileName);
    InputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument Document;
    Document.setContent(&InputFile);
    InputFile.close();
    QDomElement Root = Document.documentElement();
    if(Root.hasAttribute(Utils::XML_LAST_ID_TAG))
        LastID = Root.attribute(Utils::XML_LAST_ID_TAG);
    QDomNode Node = Root.firstChild();
    QDomElement Element;

    while(!Node.isNull())
    {
        if(!((Element = Node.toElement()).isNull()) && Element.tagName()==Utils::XML_SERVICE_TAG)
            *this << Service(&Element);
        else
            QMessageBox::about(0,"ERROR!","NOT XML_SERVICE_TAG");
        Node=Node.nextSibling();
    }
    if(!ServiceList.empty() && LastID < ServiceList.last().GetID())
        LastID = ServiceList.last().GetID();
}
int Services::SearchByID(QString IID)
{
    for(int i=0; i<ServiceList.length(); ++i)
        if(ServiceList[i].GetID() == IID)
            return i;
    return -1;
}
int Services::SearchByBarcode(QString IBarcode)
{
    for(int i=0; i<ServiceList.length(); ++i)
        if(ServiceList[i].GetBarcode() == IBarcode)
            return i;
    return -1;
}
QString Services::GetNextID()
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
void Services::AddNew()
{
    QString NewID = LastID = GetNextID();
    (*this)<<Service(NewID);
    Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
}
void Services::Remove(QString IID)
{
    ServiceList.removeAt(SearchByID(IID));
    Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
}
