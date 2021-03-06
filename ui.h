#ifndef UI_H
#define UI_H

#include "storage.h"
#include "services.h"
#include "storagetable.h"
#include "ininvoice.h"
#include "intable.h"
#include "inlisttable.h"
#include "ininvoicelist.h"
#include "outlisttable.h"
#include "outinvoicelist.h"
#include "user.h"
#include "settings.h"
#include "carids.h"

#include <QTableWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include <QMenuBar>

class StorageTable;
class InTable;

class UI : public QMainWindow
{
Q_OBJECT
public:
    explicit UI(QWidget *parent = 0);
    Storage* MainStorage;
    Services* MainServices;
    InInvoiceList* InList;
    InInvoiceList* InClosedList;
    OutInvoiceList* OutList;
    OutInvoiceList* OutClosedList;
    QMenuBar* MenuBar;
    static bool OKCancelWindow (QString ITitle = "", QString IText = "");
    void closeEvent(QCloseEvent *);

    User* CurrentUser;
    Settings* PSettings;
public slots:
    void ShowMainWindow();
    void ShowStorageTable();
    void ShowEditStorageTable();
    void ShowInTable();
    void ShowOutTable();
    void ShowInListTable();
    void ShowInClosedListTable();
    void ShowOutListTable();
    void ShowOutClosedListTable();
    void ShowSettingsWidget();
};

#endif // UI_H
