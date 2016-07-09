#include "settings.h"
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

Settings::Settings(QString IFileName)
{
    CurrentUser = -1;
    if(QFile(IFileName).exists())
        Load(IFileName);
}
void Settings::Save(QString IFileName)
{
    QDomDocument Document;
    QDomElement Root = Document.createElement(XML_ROOT_TAG);
    Document.appendChild(Root);
    for(int i=0; i<UserList.length(); ++i)
        Root.appendChild(UserList[i].ToXML(&Document));
    QFile OutputFile(IFileName);
    OutputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream OutStream(&OutputFile);
    OutStream << Document.toString();
    OutputFile.close();
}
void Settings::Load(QString IFileName)
{
    QFile InputFile(IFileName);
    InputFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QDomDocument Document;
    Document.setContent(&InputFile);
    InputFile.close();
    QDomElement Root = Document.documentElement();
    QDomNode Node = Root.firstChild();
    QDomElement Element;
    while(!Node.isNull())
    {
        if(!((Element = Node.toElement()).isNull()) && Element.tagName()==XML_USER_TAG)
            UserList.append(User(&Element));
        else
            QMessageBox::about(0,"ERROR!","NOT XML_USER_TAG");
        Node=Node.nextSibling();
    }
}
const QString Settings::XML_ROOT_TAG = "settings";
const QString Settings::XML_USER_TAG = "user";
const QString Settings::XML_USER_ID_TAG = "id";
const QString Settings::XML_USER_NAME_TAG = "name";
const QString Settings::XML_USER_SECONDNAME_TAG = "second_name";
const QString Settings::XML_USER_SURNAME_TAG = "surname";
const QString Settings::XML_USER_PASSWORD_TAG = "password_hash";
const QString Settings::XML_USER_PERMISSIONS_TAG = "permissions";
