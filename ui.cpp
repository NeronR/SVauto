#include <QStringList>
#include <QHeaderView>
#include <QKeyEvent>
#include <QPushButton>
#include <QDomDocument>
#include <QHBoxLayout>
#include <QMessageBox>

#include "ui.h"
#include "storagetable.h"
#include "services.h"
#include "mainscreen.h"
#include "ininvoicelist.h"
#include "inlisttable.h"
#include "outinvoicelist.h"
#include "outlisttable.h"
#include "outtable.h"
#include "user.h"

UI::UI(QWidget *parent) : QMainWindow(parent)
{
    CurrentUser = new User("Иван", "Иванович", "Иванов", "333");
    CurrentUser->SetPermission(User::PERMISSION_EDIT_CLOSED_INIVOICES, true);
    PSettings = new Settings("Settings.xml");

    MainStorage = new Storage(Utils::STORAGE_FILENAME + Utils::FILENAME_EXTENSION);
    //MainServices = new Services(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
    //MainServices->AddNew();
    //MainServices->Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);

    InList = new InInvoiceList(Utils::OPENED_ININVOICES_FOLDER);
    InClosedList = new InInvoiceList(Utils::CLOSED_ININVOICES_FOLDER);
    OutList = new OutInvoiceList(Utils::OPENED_OUTINVOICES_FOLDER);
    OutClosedList = new OutInvoiceList(Utils::CLOSED_OUTINVOICES_FOLDER);

    //
    CarIDs CIDS;
    CIDS.AddBrand("Opel");
    CIDS.AddModel(0, "Astra");
    CIDS.AddModel(0, "Jetta");
    CIDS.AddVersion(0, 0, "1");
    CIDS.AddVersion(0,0,"1/1/");
    qDebug()<<CIDS.GetBrands();
    qDebug()<<CIDS.GetModels(0);
    qDebug()<<CIDS.GetVersions(0,0);
    qDebug()<<CIDS.GetVersions(0,1);
    qDebug()<<CarIDs::GetCarID(1,1,1);
    //

    ShowMainWindow();
}
void UI::ShowMainWindow()
{
    setCentralWidget(new MainScreen(this));
    centralWidget()->show();
    centralWidget()->setFocus();
    InList->Load("InInvoices");
    InClosedList->Load("ClosedInInvoices");
    OutList->Load(Utils::OPENED_OUTINVOICES_FOLDER);
    OutClosedList->Load(Utils::CLOSED_OUTINVOICES_FOLDER);
    if(menuBar())
        delete menuBar();
}
void UI::ShowStorageTable()
{
    setCentralWidget(new StorageTable(this));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((StorageTable*)centralWidget())->MenuBar);
}
void UI::ShowEditStorageTable()
{
    setCentralWidget(new StorageTable(this, true));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((StorageTable*)centralWidget())->MenuBar);
}
void UI::ShowInTable()
{
    setCentralWidget(new InTable(this, 0, true));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((InTable*)centralWidget())->MenuBar);
}
void UI::ShowOutTable()
{
    setCentralWidget(new OutTable(this, 0, true));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((OutTable*)centralWidget())->MenuBar);
}
void UI::ShowInListTable()
{
    setCentralWidget(new InListTable(this));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((InListTable*)centralWidget())->MenuBar);
}
void UI::ShowInClosedListTable()
{
    setCentralWidget(new InListTable(this, InClosedList));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((InListTable*)centralWidget())->MenuBar);
}
void UI::ShowOutListTable()
{
    setCentralWidget(new OutListTable(this));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((OutListTable*)centralWidget())->MenuBar);
}
void UI::ShowOutClosedListTable()
{
    setCentralWidget(new OutListTable(this, OutClosedList));
    centralWidget()->show();
    centralWidget()->setFocus();
    setMenuBar(((OutListTable*)centralWidget())->MenuBar);
}
void UI::ShowSettingsWidget()
{}

bool UI::OKCancelWindow(QString ITitle, QString IText)
{
    QMessageBox MessageBox;
    MessageBox.setWindowTitle(ITitle);
    MessageBox.setText(IText);
    MessageBox.setStandardButtons(QMessageBox::Yes);
    MessageBox.addButton(QMessageBox::No);
    if(MessageBox.exec() == QMessageBox::Yes)
        return true;
    else
        return false;
}
void UI::closeEvent(QCloseEvent *)
{}
