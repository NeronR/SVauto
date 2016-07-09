#ifndef SETTINGS_H
#define SETTINGS_H

#include <user.h>
#include <QList>
#include <QString>

class Settings
{
public:
    Settings(QString IFileName = "");
    void Save(QString IFileName);
    void Load(QString IFileName);

    static const QString XML_ROOT_TAG;
    static const QString XML_USER_TAG;
    static const QString XML_USER_ID_TAG;
    static const QString XML_USER_NAME_TAG;
    static const QString XML_USER_SECONDNAME_TAG;
    static const QString XML_USER_SURNAME_TAG;
    static const QString XML_USER_PASSWORD_TAG;
    static const QString XML_USER_PERMISSIONS_TAG;
//private:
    QList<User> UserList;
    int CurrentUser;
};

#endif // SETTINGS_H
