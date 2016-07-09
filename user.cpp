#include "user.h"
#include "settings.h"
#include "storageitem.h"
#include "utils.h"
#include <QCryptographicHash>

User::User(QString IName, QString ISecondName, QString ISurname, QString IPassword):
    Name(IName), SecondName(ISecondName), Surname(ISurname)
{
    PermisionsArray = new bool[LAST_PERMISSION+1];
    for(int i=0; i<LAST_PERMISSION+1; ++i)
        PermisionsArray[i] = false;

    QByteArray PasswordByteArray;
    PasswordByteArray.clear();
    PasswordByteArray+=IPassword;
    PasswordHash = QCryptographicHash::hash(PasswordByteArray, QCryptographicHash::Md5);
}
User::User(QDomElement *IElement) : User()
{
    PasswordHash.clear();
    if(IElement && IElement->tagName()==Settings::XML_USER_TAG)
    {
        if(IElement->hasAttribute(Settings::XML_USER_NAME_TAG))
            Name = IElement->attribute(Settings::XML_USER_NAME_TAG);
        if(IElement->hasAttribute(Settings::XML_USER_SECONDNAME_TAG))
            SecondName = IElement->attribute(Settings::XML_USER_SECONDNAME_TAG);
        if(IElement->hasAttribute(Settings::XML_USER_SURNAME_TAG))
            Surname = IElement->attribute(Settings::XML_USER_SURNAME_TAG);
        if(IElement->hasAttribute(Settings::XML_USER_PASSWORD_TAG))
            PasswordHash += IElement->attribute(Settings::XML_USER_PASSWORD_TAG);
        if(IElement->hasAttribute(Settings::XML_USER_PERMISSIONS_TAG))
            SetPermissionsFromString(IElement->attribute(Settings::XML_USER_PERMISSIONS_TAG));
    }
}
void User::SetPassword(QString IPassword)
{
    QByteArray PasswordByteArray;
    PasswordByteArray.clear();
    PasswordByteArray+=IPassword;
    PasswordHash = QCryptographicHash::hash(PasswordByteArray, QCryptographicHash::Md5);
}
bool User::CheckPassword(QString IPassword)
{
    QByteArray PasswordByteArray;
    PasswordByteArray.clear();
    PasswordByteArray+=IPassword;
    return (PasswordHash == QCryptographicHash::hash(PasswordByteArray, QCryptographicHash::Md5));
}
void User::SetAllPermissions()
{
    for(int i=0; i<LAST_PERMISSION+1; ++i)
        PermisionsArray[i] = true;
}
void User::SetPermissionsFromString(QString IString)
{
    for(int i=0; i<IString.length() && i<LAST_PERMISSION+1; ++i)
    {
        PermisionsArray[i] = Utils::StringToBool(QString(IString[i]));
    }
}
QString User::GetPermissionString()
{
    QString OutString;
    for(int i=0; i<LAST_PERMISSION+1; ++i)
        OutString.append(Utils::BoolToString(PermisionsArray[i]));
    return OutString;
}
QDomElement User::ToXML(QDomDocument *IDocument)
{
    QDomElement Element=IDocument->createElement(Settings::XML_USER_TAG);
    Element.setAttribute(Settings::XML_USER_NAME_TAG, Name);
    Element.setAttribute(Settings::XML_USER_SECONDNAME_TAG, SecondName);
    Element.setAttribute(Settings::XML_USER_SURNAME_TAG, Surname);
    Element.setAttribute(Settings::XML_USER_PASSWORD_TAG, QString(PasswordHash));
    Element.setAttribute(Settings::XML_USER_PERMISSIONS_TAG, GetPermissionString());
    return Element;
}

const int User::PERMISSION_VIEW_STORAGE = 0x0001;
const int User::PERMISSION_EDIT_STORAGE = 0x0002;
const int User::PERMISSION_VIEW_OPENED_INIVOICES = 0x0003;
const int User::PERMISSION_VIEW_CLOSED_INIVOICES = 0x0004;
const int User::PERMISSION_EDIT_OPENED_INIVOICES = 0x0005;
const int User::PERMISSION_EDIT_CLOSED_INIVOICES = 0x0006;
const int User::PERMISSION_VIEW_OPENED_OUTINVOICES = 0x0007;
const int User::PERMISSION_VIEW_CLOSED_OUTINVOICES = 0x0008;
const int User::PERMISSION_EDIT_OPENED_OUTINVOICES = 0x0009;
const int User::PERMISSION_EDIT_CLOSED_OUTINVOICES = 0x000a;

const int User::PERMISSION_VIEW_STORAGE_ID = 0x000b;
const int User::PERMISSION_EDIT_STORAGE_ID = 0x000c;
const int User::PERMISSION_VIEW_STORAGE_NAME = 0x000d;
const int User::PERMISSION_EDIT_STORAGE_NAME = 0x000e;
const int User::PERMISSION_VIEW_STORAGE_BARCODE = 0x000f;
const int User::PERMISSION_EDIT_STORAGE_BARCODE = 0x0010;
const int User::PERMISSION_VIEW_STORAGE_QUANTITY = 0x0011;
const int User::PERMISSION_EDIT_STORAGE_QUANTITY = 0x0012;
const int User::PERMISSION_VIEW_STORAGE_PURCHACE_PRICE = 0x0013;
const int User::PERMISSION_EDIT_STORAGE_PURCHACE_PRICE = 0x0014;
const int User::PERMISSION_VIEW_STORAGE_MARKUP = 0x0015;
const int User::PERMISSION_EDIT_STORAGE_MARKUP = 0x0016;
const int User::PERMISSION_VIEW_STORAGE_SELLING_PRICE = 0x0017;
const int User::PERMISSION_EDIT_STORAGE_SELLING_PRICE = 0x0018;
const int User::PERMISSION_VIEW_STORAGE_DESCRIPTION = 0x0019;
const int User::PERMISSION_EDIT_STORAGE_DESCRIPTION = 0x001a;

const int User::LAST_PERMISSION = 0x001a;
