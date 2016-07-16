#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

#include "carstable.h"

CarsTable::CarsTable(UI* IParent, CarIDs* ICarIDs, long int IBrandID, long int IModelID) :
    Parent(IParent), MainCarIDs(ICarIDs), BrandID(IBrandID), ModelID(IModelID)
{
    if(!Parent)
        QMessageBox::about(0, "ERROR!", "No parent in CarsTable");
    int ColumnNumberCounter = 0;
    IDColumnNumber = ColumnNumberCounter++;
    NameColumnNumber = ColumnNumberCounter++;
    OpenColumnNumber = (BrandID == -1 || ModelID == -1) ? ColumnNumberCounter++ : -1;
    setColumnCount(ColumnNumberCounter);
    QStringList SList;
    SList << "ID" << "Название" << "Раскрыть";
    setHorizontalHeaderLabels(SList);
    verticalHeader()->hide();

    QStringList NamesList;
    if(BrandID == -1)
        NamesList = MainCarIDs->GetBrands();
    else if(ModelID == -1)
        NamesList = MainCarIDs->GetModels(BrandID);
    else
        NamesList = MainCarIDs->GetVersions(BrandID, ModelID);

    QStringList IDList;
    QString IDPrefix;
    QString (*IDPostfix)(long int);
    if(BrandID > -1)
        IDPrefix = CarIDs::IntBrandIDToString(BrandID);
    else
        IDPostfix = CarIDs::IntBrandIDToString;
    if(ModelID > -1)
        IDPrefix += CarIDs::IntModelIDToString(ModelID);
    else if(BrandID > -1)
        IDPostfix = CarIDs::IntModelIDToString;
    if(BrandID > -1 && ModelID > -1)
        IDPostfix = CarIDs::IntVersionIDToString;
    for(int i=0; i<NamesList.length(); ++i)
        IDList.append(IDPrefix + (*IDPostfix)(i));
    Group = new QButtonGroup;
    connect(Group, SIGNAL(buttonClicked(int)), this, SLOT(Open(int)));
    for(int i=0; i<NamesList.length(); ++i)
    {
        setRowCount(rowCount()+1);
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem(IDList.at(i)));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem(NamesList.at(i)));
        if(i > 0)
        {
            QPushButton* OpenButton = new QPushButton("X");
            Group->addButton(OpenButton, i);
            setCellWidget(rowCount()-1,OpenColumnNumber,OpenButton);
        }
    }
    setSortingEnabled(true);
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));

    DockWidget = new QWidget;
    QHBoxLayout* DockLayout = new QHBoxLayout(DockWidget);
    QPushButton* AddButton = new QPushButton("Добавить");
    connect(AddButton, SIGNAL(clicked(bool)), this, SLOT(Add()));
    DockLayout->addWidget(AddButton, 0, Qt::AlignLeft);
    DockLayout->addStretch();
    QPushButton* CloseButton = new QPushButton("Назад");
    connect(CloseButton, SIGNAL(clicked(bool)), this, SLOT(Close()));
    DockLayout->addWidget(CloseButton, 0, Qt::AlignRight);
    QString TitlePostfix;
    if(BrandID > -1)
        TitlePostfix = " " + MainCarIDs->GetBrands().at(BrandID);
    if(ModelID > -1)
        TitlePostfix += " " + MainCarIDs->GetModels(BrandID).at(ModelID);
    Parent->PushDockTitle("Список автомобилей" + TitlePostfix);
    Parent->DockMainWidget->setCurrentIndex(Parent->DockMainWidget->addWidget(DockWidget));
}
void CarsTable::CellChanged(int IRow, int IColumn)
{
    if(IColumn == NameColumnNumber)
    {
        if(!item(IRow,IColumn)->text().isEmpty())
        {
            if(BrandID == -1)
                MainCarIDs->Rename(CarIDs::StringIDToBrandID(item(IRow,IDColumnNumber)->text()),
                                   -1, -1, item(IRow,IColumn)->text());
            else if(ModelID == -1)
                MainCarIDs->Rename(BrandID, CarIDs::StringIDToModelID(item(IRow,IDColumnNumber)->text()),
                                   -1, item(IRow,IColumn)->text());
            else
                MainCarIDs->Rename(BrandID, ModelID, CarIDs::StringIDToVersionID(item(IRow,IDColumnNumber)->text()),
                                   item(IRow,IColumn)->text());
        }
        else
            item(IRow,IColumn)->setText("");
        MainCarIDs->Save();
    }
}
void CarsTable::Add()
{
    disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    int NewID;
    if(BrandID == -1)
    {
        MainCarIDs->AddBrand("", true);
        NewID = MainCarIDs->GetBrands().length() - 1;
    }
    else if(ModelID == -1)
    {
        MainCarIDs->AddModel(BrandID, "", true);
        NewID = MainCarIDs->GetModels(BrandID).length() - 1;
    }
    else
    {
        MainCarIDs->AddVersion(BrandID, ModelID, "");
        NewID = MainCarIDs->GetVersions(BrandID, ModelID).length() - 1;
    }
    setSortingEnabled(false);
    setRowCount(rowCount()+1);

    QString IDPrefix;
    QString (*IDPostfix)(long int);
    if(BrandID > -1)
        IDPrefix = CarIDs::IntBrandIDToString(BrandID);
    else
        IDPostfix = CarIDs::IntBrandIDToString;
    if(ModelID > -1)
        IDPrefix += CarIDs::IntModelIDToString(ModelID);
    else if(BrandID > -1)
        IDPostfix = CarIDs::IntModelIDToString;
    if(BrandID > -1 && ModelID > -1)
        IDPostfix = CarIDs::IntVersionIDToString;
    QString ID = (IDPrefix + (*IDPostfix)(NewID));

    setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem(ID));
    item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                flags() & ~Qt::ItemIsEditable);
    setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem(""));
    if(NewID > 0)
    {
        QPushButton* OpenButton = new QPushButton("X");
        Group->addButton(OpenButton, NewID);
        setCellWidget(rowCount()-1,OpenColumnNumber,OpenButton);
    }

    setSortingEnabled(true);
    MainCarIDs->Save();
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
}
void CarsTable::Open(int IID)
{
    if(IID == 0) return;
    CarsTable* Table;
    if(BrandID == -1)
        Table = new CarsTable(Parent, MainCarIDs, IID, -1);
    else if(ModelID == -1)
        Table = new CarsTable(Parent, MainCarIDs, BrandID, IID);
    Parent->MainWidget->setCurrentIndex(Parent->MainWidget->addWidget(Table));
    Parent->MainWidget->currentWidget()->show();
    Parent->MainWidget->currentWidget()->setFocus();
}
void CarsTable::Close()
{
    Parent->PopDockTitle();
    delete DockWidget;
    delete this;
}
