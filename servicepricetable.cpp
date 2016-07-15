#include "servicepricetable.h"
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
ServicePriceTable::ServicePriceTable(ServicesTable* IParent, Service* IMainService, CarIDs* ICarIDs, bool IEditable) :
    QTableWidget(0), Parent(IParent), MainService(IMainService), Editable(IEditable), MainCarIDs(ICarIDs)
{
    if(!Parent)
        QMessageBox::about(0,"ERROR!","No parent in ServicePriceTable");
    int ColumnNumberCounter = 0;
        IDColumnNumber = true ? ColumnNumberCounter++ : -1;
        BrandColumnNumber = true ? ColumnNumberCounter++ : -1;
        ModelColumnNumber = true ? ColumnNumberCounter++ : -1;
        VersionColumnNumber = true ? ColumnNumberCounter++ : -1;
        PriceColumnNumber = true ? ColumnNumberCounter++ : -1;
    setColumnCount(ColumnNumberCounter);
    QStringList SList;
    SList << "ID" << "Марка" << "Модель" << "Версия" << "Цена";
    this->setHorizontalHeaderLabels(SList);
    this->verticalHeader()->hide();
    setSortingEnabled(true);

    QMap<long long int, long long int>::const_iterator i = MainService->Price.constBegin();
    while(i != MainService->Price.constEnd())
    {
        setSortingEnabled(false);
        setRowCount(rowCount()+1);
        CarIDs::CarName CurrentCarName = MainCarIDs->GetCarNameByIntID(i.key());
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem(CarIDs::IntCarIDToString(i.key())));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,BrandColumnNumber,new QTableWidgetItem(CurrentCarName.Brand));
        item(rowCount()-1,BrandColumnNumber)->setFlags(item(rowCount()-1,BrandColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,ModelColumnNumber,new QTableWidgetItem(CurrentCarName.Model));
        item(rowCount()-1,ModelColumnNumber)->setFlags(item(rowCount()-1,ModelColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,VersionColumnNumber,new QTableWidgetItem(CurrentCarName.Version));
        item(rowCount()-1,VersionColumnNumber)->setFlags(item(rowCount()-1,VersionColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,PriceColumnNumber,new QTableWidgetItem(Utils::IntMoneyToString(i.value())));
        if(!Editable)
            item(rowCount()-1,PriceColumnNumber)->setFlags(item(rowCount()-1,PriceColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setSortingEnabled(true);
        ++i;
    }
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    QWidget* DockWidget = new QWidget;
    QHBoxLayout* DockLayout = new QHBoxLayout(this);
    DockWidget->setLayout(DockLayout);
    if(Editable)
    {
        QPushButton* AddButton = new QPushButton("Добавить цену");
        connect(AddButton, SIGNAL(clicked(bool)), this, SLOT(Add()));
        DockLayout->addWidget(AddButton,0,Qt::AlignLeft);
        QPushButton* DeleteButton = new QPushButton("Удалить цену");
        connect(DeleteButton, SIGNAL(clicked(bool)), this, SLOT(RemoveCurrent()));
        DockLayout->addWidget(DeleteButton,0,Qt::AlignLeft);
    }
    DockLayout->addStretch();
    QPushButton* CloseButton = new QPushButton("Назад");
    connect(CloseButton, SIGNAL(clicked(bool)), this, SLOT(Close()));
    DockLayout->addWidget(CloseButton, 0, Qt::AlignRight);
    Parent->Parent->DockMainWidget->setCurrentIndex(Parent->Parent->DockMainWidget->addWidget(DockWidget));
    Parent->Parent->PushDockTitle("\"" + MainService->GetName() + "\"" + (IEditable ? " Цены (редактирование)" : " Цены"));
}
void ServicePriceTable::CellChanged(int IRow, int IColumn)
{
        disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
        QString IText = item(IRow,IColumn)->text();
        long long int TargetID = item(IRow,IDColumnNumber)->text().toLongLong();
        if(IColumn == PriceColumnNumber)
        {
            QString PriceString = Utils::StringToPrice(IText);
            if(!PriceString.isEmpty())
            {
                MainService->SetPrice(TargetID, Utils::StringMoneyToInt(PriceString));
                //MainService->Price.insert(TargetID, Utils::StringMoneyToInt(IText));
                item(IRow,IColumn)->setText(MainService->GetPriceString(TargetID));
            }
            else
            {
                QMessageBox::about(0,"WARNING","Некорректная цена");
                item(IRow,IColumn)->setText(MainService->GetPriceString(TargetID));
                //item(IRow,IColumn)->setText(Utils::IntMoneyToString(MainService->Price.value(TargetID)));
            }
        }
        else; //Should never reach here
        Parent->MainServices->Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
        connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
}
void ServicePriceTable::Add()
{
    disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    PickButtonWidget* Widget = new PickButtonWidget(Parent->Parent, Parent->Parent->MainCarIDs->GetBrands());
    connect(Widget, SIGNAL(Clicked(int)), this, SLOT(Add2(int)));
}
void ServicePriceTable::Add2(int IID)
{
    BrandID = IID;
    PickButtonWidget* Widget = new PickButtonWidget(Parent->Parent, Parent->Parent->MainCarIDs->GetModels(IID));
    connect(Widget, SIGNAL(Clicked(int)), this, SLOT(Add3(int)));
}
void ServicePriceTable::Add3(int IID)
{
    ModelID = IID;
    PickButtonWidget* Widget = new PickButtonWidget(Parent->Parent, Parent->Parent->MainCarIDs->GetVersions(BrandID, IID));
    connect(Widget, SIGNAL(Clicked(int)), this, SLOT(Add4(int)));
}
void ServicePriceTable::Add4(int IID)
{
    VersionID = IID;
    long long int CarID = CarIDs::GetCarIDInt(BrandID, ModelID, VersionID);
    MainService->SetPrice(CarID, 0);
    setSortingEnabled(false);
    setRowCount(rowCount()+1);
    CarIDs::CarName CurrentCarName = MainCarIDs->GetCarNameByIntID(CarID);
    setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem(CarIDs::IntCarIDToString(CarID)));
    item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                flags() & ~Qt::ItemIsEditable);
    setItem(rowCount()-1,BrandColumnNumber,new QTableWidgetItem(CurrentCarName.Brand));
    item(rowCount()-1,BrandColumnNumber)->setFlags(item(rowCount()-1,BrandColumnNumber)->
                                                flags() & ~Qt::ItemIsEditable);
    setItem(rowCount()-1,ModelColumnNumber,new QTableWidgetItem(CurrentCarName.Model));
    item(rowCount()-1,ModelColumnNumber)->setFlags(item(rowCount()-1,ModelColumnNumber)->
                                                flags() & ~Qt::ItemIsEditable);
    setItem(rowCount()-1,VersionColumnNumber,new QTableWidgetItem(CurrentCarName.Version));
    item(rowCount()-1,VersionColumnNumber)->setFlags(item(rowCount()-1,VersionColumnNumber)->
                                                flags() & ~Qt::ItemIsEditable);
    setItem(rowCount()-1,PriceColumnNumber,new QTableWidgetItem(Utils::IntMoneyToString(0)));
    setSortingEnabled(true);
    Parent->MainServices->Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
}
void ServicePriceTable::Remove(int IRow)
{
    if(Editable && UI::OKCancelWindow("","Удалить "+item(IRow, BrandColumnNumber)->text() + " " +
                                      item(IRow, ModelColumnNumber)->text() + " " +
                                      item(IRow, VersionColumnNumber)->text() + " ?"))
    {
        MainService->RemovePrice(item(IRow,IDColumnNumber)->text().toLongLong());
        removeRow(IRow);
    }
}
void ServicePriceTable::RemoveCurrent()
{
    Remove(currentRow());
}
void ServicePriceTable::Close()
{
    Parent->Parent->PopDockTitle();
    delete Parent->Parent->DockMainWidget->currentWidget();
    delete this;
}
