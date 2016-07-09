#ifndef USER_H
#define USER_H

#include <QString>
#include <QDomDocument>

class User
{
public:
    User(QString IName = "", QString ISecondName = "", QString ISurname = "", QString IPassword = "");
    User(QDomElement* IElement);

    void SetName(QString IName) {Name = IName;}
    void SetSecondName(QString ISecondName) {SecondName = ISecondName;}
    void SetSurname(QString ISurname) {Surname = ISurname;}
    void SetPassword(QString IPassword);

    QString GetName() {return Name;}
    QString GetSecondName() {return SecondName;}
    QString GetSurname() {return Surname;}
    bool CheckPassword(QString IPassword);

    bool* PermisionsArray;
    void SetPermission(int IPermission, bool IValue) {PermisionsArray[IPermission] = IValue;}
    void SetAllPermissions();
    bool GetPermission(int IPermission) {return PermisionsArray[IPermission];}
    void SetPermissionsFromString(QString IString);
    QString GetPermissionString();

    QDomElement ToXML (QDomDocument* IDocument);

    static const int PERMISSION_VIEW_STORAGE;
    static const int PERMISSION_EDIT_STORAGE;
    static const int PERMISSION_VIEW_OPENED_INIVOICES;
    static const int PERMISSION_VIEW_CLOSED_INIVOICES;
    static const int PERMISSION_EDIT_OPENED_INIVOICES;
    static const int PERMISSION_EDIT_CLOSED_INIVOICES;
    static const int PERMISSION_VIEW_OPENED_OUTINVOICES;
    static const int PERMISSION_VIEW_CLOSED_OUTINVOICES;
    static const int PERMISSION_EDIT_OPENED_OUTINVOICES;
    static const int PERMISSION_EDIT_CLOSED_OUTINVOICES;

    static const int PERMISSION_VIEW_STORAGE_ID;
    static const int PERMISSION_EDIT_STORAGE_ID;
    static const int PERMISSION_VIEW_STORAGE_NAME;
    static const int PERMISSION_EDIT_STORAGE_NAME;
    static const int PERMISSION_VIEW_STORAGE_BARCODE;
    static const int PERMISSION_EDIT_STORAGE_BARCODE;
    static const int PERMISSION_VIEW_STORAGE_QUANTITY;
    static const int PERMISSION_EDIT_STORAGE_QUANTITY;
    static const int PERMISSION_VIEW_STORAGE_PURCHACE_PRICE;
    static const int PERMISSION_EDIT_STORAGE_PURCHACE_PRICE;
    static const int PERMISSION_VIEW_STORAGE_MARKUP;
    static const int PERMISSION_EDIT_STORAGE_MARKUP;
    static const int PERMISSION_VIEW_STORAGE_SELLING_PRICE;
    static const int PERMISSION_EDIT_STORAGE_SELLING_PRICE;
    static const int PERMISSION_VIEW_STORAGE_DESCRIPTION;
    static const int PERMISSION_EDIT_STORAGE_DESCRIPTION;

    static const int LAST_PERMISSION;

private:
    QString Name;
    QString SecondName;
    QString Surname;
    QByteArray PasswordHash;
};

#endif // USER_H
