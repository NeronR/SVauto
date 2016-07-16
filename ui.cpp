#include <QStringList>
#include <QHeaderView>
#include <QKeyEvent>
#include <QPushButton>
#include <QDomDocument>
#include <QHBoxLayout>
#include <QMessageBox>

#include <QDockWidget>

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
#include "carstable.h"

UI::UI(QWidget *parent) : QMainWindow(parent)
{
    MainWidget = new QStackedWidget;
    setCentralWidget(MainWidget);

    CurrentUser = new User("Иван", "Иванович", "Иванов", "333");
    CurrentUser->SetPermission(User::PERMISSION_EDIT_CLOSED_INIVOICES, true);
    PSettings = new Settings("Settings.xml");
    MainStorage = new Storage(Utils::STORAGE_FILENAME + Utils::FILENAME_EXTENSION);
    MainServices = new Services(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
    InList = new InInvoiceList(Utils::OPENED_ININVOICES_FOLDER);
    InClosedList = new InInvoiceList(Utils::CLOSED_ININVOICES_FOLDER);
    OutList = new OutInvoiceList(Utils::OPENED_OUTINVOICES_FOLDER);
    OutClosedList = new OutInvoiceList(Utils::CLOSED_OUTINVOICES_FOLDER);
    MainCarIDs = new CarIDs;
    MainCarIDs->Load();
    MainOrderList = new OrderList(Utils::ORDERS_FOLDER);

    DockWidget = new QDockWidget("", this);
    DockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
    addDockWidget(Qt::TopDockWidgetArea, DockWidget);
    DockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    DockMainWidget = new QStackedWidget;
    DockWidget->setWidget(DockMainWidget);

    ShowMainWindow();

    //TEST

}
void UI::ShowMainWindow()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new MainScreen(this)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
    DockWidget->setWindowTitle("");
}
void UI::ShowStorageTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new StorageTable(this, false)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowEditStorageTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new StorageTable(this, true)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowServicesTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new ServicesTable(this, false)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowEditServicesTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new ServicesTable(this, true)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowInTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new InTable(this, 0, true)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowOutTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new OutTable(this, 0, true)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowInListTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new InListTable(this)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowInClosedListTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new InListTable(this, InClosedList)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowOutListTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new OutListTable(this)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowOutClosedListTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new OutListTable(this, OutClosedList)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
}
void UI::ShowCarsTable()
{
    MainWidget->setCurrentIndex(MainWidget->addWidget(new CarsTable(this, MainCarIDs)));
    MainWidget->currentWidget()->show();
    MainWidget->currentWidget()->setFocus();
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
void UI::PushDockTitle(QString ITitle)
{
    DockTitleStack.push(ITitle);
    DockWidget->setWindowTitle(ITitle);
}
void UI::PopDockTitle()
{
    DockTitleStack.pop();
    if(DockTitleStack.isEmpty())
        DockWidget->setWindowTitle("");
    else
        DockWidget->setWindowTitle(DockTitleStack.top());
}
