#include "storagetable.h"
#include "ui.h"
#include "storageitem.h"
#include "storage.h"
#include "mainscreen.h"
#include "main.cpp"
#include "utils.h"

#include <QString>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>
#include <QKeyEvent>
#include <QMenuBar>
#include <QAction>

//TODO:
//Add checks for editing non-editable items

StorageTable::StorageTable(UI *Iparent, bool IEditable) : QTableWidget(Iparent), Parent(Iparent)
{
    if(!Iparent)
        QMessageBox::about(0, "ERROR!", "No parent in StorageTable");
    Editable = IEditable;
    int ColumnNumberCounter = 0;
        IDColumnNumber = true ? ColumnNumberCounter++ : -1;
        NameColumnNumber = true ? ColumnNumberCounter++ : -1;
        BarcodeColumnNumber = true ? ColumnNumberCounter++ : -1;
        QuantityColumnNumber = true ? ColumnNumberCounter++ : -1;
        PurchasePriceColumnNumber = true ? ColumnNumberCounter++ : -1;
        MarkupColumnNumber = true ? ColumnNumberCounter++ : -1;
        SellingPriceColumnNumber = true ? ColumnNumberCounter++ : -1;
        DescriptionColumnNumber = true ? ColumnNumberCounter++ : -1;
    setColumnCount(ColumnNumberCounter);

    MainStorage = Iparent->MainStorage;
    QStringList SList;
    SList << "ID" << "Название" << "Штрихкод" << "Количество" << "Цена1" << "Наценка" << "Цена2" << "Описание";
    this->setHorizontalHeaderLabels(SList);
    this->verticalHeader()->hide();
    setSortingEnabled(true);

    for(int i=0; i<MainStorage->Size(); ++i)
    {
        setSortingEnabled(false);
        setRowCount(rowCount()+1);
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetID()));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetName()));
        if(!Editable)
            item(rowCount()-1,NameColumnNumber)->setFlags(item(rowCount()-1,NameColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,BarcodeColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetBarcode()));
        if(!Editable)
            item(rowCount()-1,BarcodeColumnNumber)->setFlags(item(rowCount()-1,BarcodeColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,QuantityColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetQuantityString()));
        item(rowCount()-1,QuantityColumnNumber)->setFlags(item(rowCount()-1,QuantityColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,PurchasePriceColumnNumber,new QTableWidgetItem(
                           (*MainStorage)[i].GetLastPurchasePriceString()));
        if(!Editable)
            item(rowCount()-1,PurchasePriceColumnNumber)->setFlags(item(rowCount()-1,PurchasePriceColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,MarkupColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetMarkupString()));
        if(!Editable)
            item(rowCount()-1,MarkupColumnNumber)->setFlags(item(rowCount()-1,MarkupColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,SellingPriceColumnNumber,new QTableWidgetItem(
                    (*MainStorage)[i].GetSellingPriceString()));
        if(!Editable)
            item(rowCount()-1,SellingPriceColumnNumber)->setFlags(item(rowCount()-1,SellingPriceColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        QPushButton* PB = new QPushButton("X");
        setCellWidget(rowCount()-1,DescriptionColumnNumber,PB);
        setSortingEnabled(true);
    }
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    MenuBar = new QMenuBar(this);
    if(Editable)
    {
        QAction* AddAction = new QAction("Добавить товар", MenuBar);
        connect(AddAction,SIGNAL(triggered(bool)),this,SLOT(Add()));
        MenuBar->addAction(AddAction);
        QAction* DeleteAction = new QAction("Удалить товар", MenuBar);
        connect(DeleteAction,SIGNAL(triggered(bool)),this,SLOT(RemoveCurrent()));
        MenuBar->addAction(DeleteAction);
    }
    QAction* CloseAction = new QAction("Назад", MenuBar);
    connect(CloseAction,SIGNAL(triggered(bool)),Parent,SLOT(ShowMainWindow()));
    MenuBar->addAction(CloseAction);
}
StorageTable::~StorageTable()
{
    clear();
    setRowCount(0);
}
void StorageTable::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Insert)
        emit Add();
    if(event->key()==Qt::Key_Delete)
        emit RemoveCurrent();
}

void StorageTable::CellChanged(int IRow, int IColumn)
{
    disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    QString IText = item(IRow,IColumn)->text();
    StorageItem* TargetItem = &((*MainStorage)[MainStorage->SearchByID(item(IRow,IDColumnNumber)->text())]);
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
            QMessageBox::about(0,"WARNING","Товар с таким штрих-кодом уже существует");
        item(IRow,IColumn)->setText(TargetItem->GetBarcode());
    }
    /*if(IColumn == QuantityColumnNumber)
    {
        if(StorageItem::IsQuantity(IText))
            TargetItem->SetQuantity(IText);
        else
            QMessageBox::about(0,"ERROR!","Incorrect Quantity");
        item(IRow,IColumn)->setText(TargetItem->GetQuantityString());

    }*/
    if(IColumn == PurchasePriceColumnNumber)
    {
        QString ConvertedPrice = Utils::StringToPrice(IText);
        if(!ConvertedPrice.isEmpty())
            TargetItem->SetLastPurchasePrice(ConvertedPrice);
        else
            QMessageBox::about(0,"ERROR!","Некорректная цена");
        item(IRow,IColumn)->setText(TargetItem->GetLastPurchasePriceString());
        if(SellingPriceColumnNumber>-1)
            item(IRow,SellingPriceColumnNumber)->setText(TargetItem->GetSellingPriceString());
    }
    if(IColumn == MarkupColumnNumber)
    {
        QString ConvertedMarkup = Utils::StringToPrice(IText);
        if(!ConvertedMarkup.isEmpty())
            TargetItem->SetMarkup(ConvertedMarkup);
        else
            QMessageBox::about(0,"ERROR!","Некорректная наценка");
        item(IRow,IColumn)->setText(TargetItem->GetMarkupString());
        if(SellingPriceColumnNumber>-1)
            item(IRow,SellingPriceColumnNumber)->setText(TargetItem->GetSellingPriceString());
    }
    if(IColumn == SellingPriceColumnNumber)
    {
        QString ConvertedPrice = Utils::StringToPrice(IText);
        if(!ConvertedPrice.isEmpty())
        {
            if(Utils::StringMoneyToInt(ConvertedPrice) >= TargetItem->GetLastPurchasePrice())
                TargetItem->SetSellingPrice(ConvertedPrice);
            else
                QMessageBox::about(0,"WARNING","Цена продажи не может быть меньше закупочной");
        }
        else
            QMessageBox::about(0,"ERROR!","Некорректная цена");
        item(IRow,IColumn)->setText(TargetItem->GetSellingPriceString());
        if (MarkupColumnNumber>-1)
            item(IRow,MarkupColumnNumber)->setText(TargetItem->GetMarkupString());
    }
    MainStorage->Save(Utils::STORAGE_FILENAME + Utils::FILENAME_EXTENSION);
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
}
void StorageTable::Add()
{
    if(Editable)
    {
        disconnect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
        (*MainStorage).AddNew();
        setSortingEnabled(false);
        setRowCount(rowCount()+1);
        int i = (*MainStorage).Size()-1;
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetID()));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetName()));
        setItem(rowCount()-1,BarcodeColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetBarcode()));
        setItem(rowCount()-1,QuantityColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetQuantityString()));
        item(rowCount()-1,QuantityColumnNumber)->setFlags(item(rowCount()-1,QuantityColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,PurchasePriceColumnNumber,new QTableWidgetItem(
                           (*MainStorage)[i].GetLastPurchasePriceString()));
        setItem(rowCount()-1,MarkupColumnNumber,new QTableWidgetItem((*MainStorage)[i].GetMarkupString()));
        setItem(rowCount()-1,SellingPriceColumnNumber,new QTableWidgetItem(
                    (*MainStorage)[i].GetSellingPriceString()));
        QPushButton* PB = new QPushButton("X");
        setCellWidget(rowCount()-1,DescriptionColumnNumber,PB);
        setSortingEnabled(true);
        MainStorage->Save(Utils::STORAGE_FILENAME + Utils::FILENAME_EXTENSION);
        connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    }
}
void StorageTable::Remove(int IRow)
{
    if(Editable && UI::OKCancelWindow("","Удалить "+item(IRow,NameColumnNumber)->text()+" ?"))
    {
        if(!((*(Parent->MainStorage))[Parent->MainStorage->SearchByID(item(IRow,IDColumnNumber)->text())].
                GetQuantity()))
        {
            Parent->MainStorage->Remove(item(IRow,IDColumnNumber)->text());
            removeRow(IRow);
        }
        else
            QMessageBox::about(0,"WARNING","Невозможно удалить товар, присутствующий на складе");
    }
}
void StorageTable::RemoveCurrent()
{
    Remove(currentRow());
}
void StorageTable::Close()
{
    Parent->setCentralWidget(new MainScreen(Parent));
}
