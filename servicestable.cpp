#include "servicestable.h"
#include "mainscreen.h"
#include <QHeaderView>
#include <QPushButton>
#include <QKeyEvent>

//TODO:
//Add checks for editing non-editable items

ServicesTable::ServicesTable(UI* IParent, bool IEditable) : QTableWidget(IParent), Parent(IParent)
{
    if(!IParent)
        QMessageBox::about(0, "ERROR!", "No parent in ServicesTable");
    Editable = IEditable;
    int ColumnNumberCounter = 0;
        IDColumnNumber = true ? ColumnNumberCounter++ : -1;
        NameColumnNumber = true ? ColumnNumberCounter++ : -1;
        BarcodeColumnNumber = true ? ColumnNumberCounter++ : -1;
        PriceColumnNumber = true ? ColumnNumberCounter++ : -1;
        DescriptionColumnNumber = true ? ColumnNumberCounter++ : -1;
    setColumnCount(ColumnNumberCounter);

    MainServices = IParent->MainServices;
    QStringList SList;
    SList << "ID" << "Название" << "Штрихкод" << "Цена" << "Описание";
    this->setHorizontalHeaderLabels(SList);
    this->verticalHeader()->hide();
    setSortingEnabled(true);

    for(int i=0; i<MainServices->Size(); ++i)
    {
        setSortingEnabled(false);
        setRowCount(rowCount()+1);
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*MainServices)[i].GetID()));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem((*MainServices)[i].GetName()));
        if(!Editable)
            item(rowCount()-1,NameColumnNumber)->setFlags(item(rowCount()-1,NameColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,BarcodeColumnNumber,new QTableWidgetItem((*MainServices)[i].GetBarcode()));
        if(!Editable)
            item(rowCount()-1,BarcodeColumnNumber)->setFlags(item(rowCount()-1,BarcodeColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        QPushButton* PriceButton = new QPushButton("X");
        setCellWidget(rowCount()-1,PriceColumnNumber,PriceButton);
        QPushButton* DescriptionButton = new QPushButton("X");
        setCellWidget(rowCount()-1,DescriptionColumnNumber,DescriptionButton);
        setSortingEnabled(true);
    }
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    MenuBar = new QMenuBar(this);
    if(Editable)
    {
        QAction* AddAction = new QAction("Добавить услугу", MenuBar);
        connect(AddAction,SIGNAL(triggered(bool)),this,SLOT(Add()));
        MenuBar->addAction(AddAction);
        QAction* DeleteAction = new QAction("Удалить услугу", MenuBar);
        connect(DeleteAction,SIGNAL(triggered(bool)),this,SLOT(RemoveCurrent()));
        MenuBar->addAction(DeleteAction);
    }
    QAction* CloseAction = new QAction("Назад", MenuBar);
    connect(CloseAction,SIGNAL(triggered(bool)),Parent,SLOT(ShowMainWindow()));
    MenuBar->addAction(CloseAction);
}
ServicesTable::~ServicesTable()
{
    clear();
    setRowCount(0);
}
void ServicesTable::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Insert)
        emit Add();
    if(event->key()==Qt::Key_Delete)
        emit RemoveCurrent();
}
void ServicesTable::CellChanged(int IRow, int IColumn)
{
    {
        disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
        QString IText = item(IRow,IColumn)->text();
        Service* TargetItem = &((*MainServices)[MainServices->SearchByID(item(IRow,IDColumnNumber)->text())]);
        if(IColumn == NameColumnNumber)
        {
            TargetItem->SetName(IText);
        }
        if(IColumn == BarcodeColumnNumber)
        {
            QString ConvertedBarcode = Utils::StringToBarcode(IText);
            if(item(IRow,IColumn)->text() == "")
                TargetItem->SetBarcode("");
            else if(Parent->MainStorage->SearchByBarcode(ConvertedBarcode)==-1)
            {
                if(!ConvertedBarcode.isEmpty())
                    TargetItem->SetBarcode(ConvertedBarcode);
                else
                    QMessageBox::about(0,"ERROR!","Некорректный штрих-код");
            }
            else
                QMessageBox::about(0,"WARNING","Услуга с таким штрих-кодом уже существует");
            item(IRow,IColumn)->setText(TargetItem->GetBarcode());
        }
        MainServices->Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
        connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    }
}
void ServicesTable::Add()
{
    if(Editable)
    {
        disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
        (*MainServices).AddNew();
        setSortingEnabled(false);
        setRowCount(rowCount()+1);
        int i = (*MainServices).Size()-1;
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*MainServices)[i].GetID()));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem((*MainServices)[i].GetName()));
        setItem(rowCount()-1,BarcodeColumnNumber,new QTableWidgetItem((*MainServices)[i].GetBarcode()));
        QPushButton* PriceButton = new QPushButton("X");
        setCellWidget(rowCount()-1,PriceColumnNumber,PriceButton);
        QPushButton* DescriptionButton = new QPushButton("X");
        setCellWidget(rowCount()-1,DescriptionColumnNumber,DescriptionButton);
        setSortingEnabled(true);
        MainServices->Save(Utils::SERVICES_FILENAME + Utils::FILENAME_EXTENSION);
        connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    }
}
void ServicesTable::Remove(int IRow)
{
    if(Editable && UI::OKCancelWindow("","Удалить "+item(IRow,NameColumnNumber)->text()+" ?"))
    {
        Parent->MainServices->Remove(item(IRow,IDColumnNumber)->text());
        removeRow(IRow);
    }
}
void ServicesTable::RemoveCurrent()
{
    Remove(currentRow());
}
void ServicesTable::Close()
{
    Parent->setCentralWidget(new MainScreen(Parent));
}
