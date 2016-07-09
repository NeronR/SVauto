#include "intable.h"
#include "ui.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>
#include <QKeyEvent>
#include <QLayout>
#include <QPushButton>
#include <QDateTime>

InTable::InTable(UI* Iparent, InInvoice* IInvoice, bool IEditable) : QTableWidget(Iparent),
    Parent(Iparent), Invoice(IInvoice), Editable(IEditable)
{
    if(!Iparent)
        QMessageBox::about(0, "ERROR!", "No parent in InTable");
    if(Invoice == 0)
    {
        Invoice = new InInvoice(Parent->InList->GetNextID() > Parent->InClosedList->GetNextID() ?
                                    Parent->InList->GetNextID() : Parent->InClosedList->GetNextID());
        (*(Parent->InList))<<*Invoice;
    }
    if(Invoice->GetApplied())
        Editable = false;
    int ColumnNumberCounter = 0;
    IDColumnNumber = true ? ColumnNumberCounter++ : -1;
    NameColumnNumber = true ? ColumnNumberCounter++ : -1;
    QuantityColumnNumber = true ? ColumnNumberCounter++ : -1;
    PriceColumnNumber = true ? ColumnNumberCounter++ : -1;
    setColumnCount(ColumnNumberCounter);
    QStringList SList;
    SList << "ID" << "Название" << "Количество" << "Цена";
    setHorizontalHeaderLabels(SList);
    verticalHeader()->hide();
    setSortingEnabled(true);

    for(int i=0; i<Invoice->Size(); ++i)
    {
        setSortingEnabled(false);
        setRowCount(rowCount()+1);
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*Invoice)[i].GetID()));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem((*Invoice)[i].GetName()));
        item(rowCount()-1,NameColumnNumber)->setFlags(item(rowCount()-1,NameColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,QuantityColumnNumber,new QTableWidgetItem((*Invoice)[i].GetQuantityString()));
        if(!Editable)
            item(rowCount()-1,QuantityColumnNumber)->setFlags(item(rowCount()-1,QuantityColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,PriceColumnNumber,new QTableWidgetItem(
                           (*Invoice)[i].GetPriceString()));
        if(!Editable)
            item(rowCount()-1,PriceColumnNumber)->setFlags(item(rowCount()-1,PriceColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
        setSortingEnabled(true);
    }
    connect(this,SIGNAL(cellChanged(int,int)),this,SLOT(CellChanged(int,int)));
    MenuBar = new QMenuBar(this);
    QAction* CloseAction = new QAction("Назад",MenuBar);
    connect(CloseAction,SIGNAL(triggered(bool)),Parent,SLOT(ShowMainWindow()));
    MenuBar->addAction(CloseAction);
    if(Invoice->GetApplied())
    {
        ApplyAction = new QAction("Отменить",MenuBar);
        connect(ApplyAction, SIGNAL(triggered(bool)),this,SLOT(Deapply()));
    }
    else
    {
        ApplyAction = new QAction("Применить",MenuBar);
        connect(ApplyAction, SIGNAL(triggered(bool)),this,SLOT(Apply()));
    }
    MenuBar->addAction(ApplyAction);
    if(!Invoice->GetApplied())
    {
        QAction* DeleteAction = new QAction("Удалить приход", MenuBar);
        connect(DeleteAction,SIGNAL(triggered(bool)),this,SLOT(Delete()));
        MenuBar->addAction(DeleteAction);
    }
    TotalLabel = new QLabel(this);
    TotalLabel->setMinimumWidth(TotalLabel->width());
    TotalLabel->setText(Utils::IntMoneyToString(Invoice->GetTotal()));
    MenuBar->setCornerWidget(TotalLabel);
}
void InTable::Add(int IIndex)
{
    if(IIndex>-1 && IIndex<Parent->MainStorage->Size())
    {
        if(Invoice->SearchByID((*Parent->MainStorage)[IIndex].GetID())==-1)
        {
            setSortingEnabled(false);
            setRowCount(rowCount()+1);
            *Invoice<<(InItem((*Parent->MainStorage)[IIndex].GetID(),
                              (*Parent->MainStorage)[IIndex].GetName(),1,
                              (*Parent->MainStorage)[IIndex].GetLastPurchasePrice()));
            int i = (*Invoice).Size()-1;
            setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*Invoice)[i].GetID()));
            item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
            setItem(rowCount()-1,NameColumnNumber,new QTableWidgetItem((*Invoice)[i].GetName()));
            item(rowCount()-1,NameColumnNumber)->setFlags(item(rowCount()-1,NameColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
            setItem(rowCount()-1,QuantityColumnNumber,new QTableWidgetItem((*Invoice)[i].GetQuantityString()));
            setItem(rowCount()-1,PriceColumnNumber,new QTableWidgetItem(
                               (*Invoice)[i].GetPriceString()));
            setSortingEnabled(true);
        }
        else
        {
            (*Invoice)[Invoice->SearchByID((*Parent->MainStorage)[IIndex].GetID())].QuantityInc();
            for(int i=0; i<Invoice->Size(); ++i)
            {
                if(item(i,IDColumnNumber)->text()==(*Parent->MainStorage)[IIndex].GetID())
                {
                    item(i,QuantityColumnNumber)->setText((*Invoice)
                           [Invoice->SearchByID((*Parent->MainStorage)[IIndex].GetID())].GetQuantityString());
                }
            }
        }
        TotalLabel->setText(Utils::IntMoneyToString(Invoice->GetTotal()));
    }
    Invoice->Save(Utils::OPENED_ININVOICES_FOLDER);
}
void InTable::Apply()
{
    if(UI::OKCancelWindow("","Вы действительно хотите применить приход?"))
    {
        for(int i=0; i<Invoice->Size(); ++i)
        {
            if((Parent->MainStorage->SearchByID((*Invoice)[i].GetID()))>-1)
                (*(Parent->MainStorage))[(Parent->MainStorage->SearchByID((*Invoice)[i].GetID()))].
                        IncreaseQuantity((*Invoice)[i].GetQuantity());
        }
        Invoice->SetApplied(true);
        QFile DeletingFile(Utils::OPENED_ININVOICES_FOLDER+Invoice->GetID()+Utils::FILENAME_EXTENSION);
        if(DeletingFile.exists())
            DeletingFile.remove();
        Parent->MainStorage->Save(Utils::STORAGE_FILENAME+Utils::FILENAME_EXTENSION);
        Invoice->SetDate(QDateTime::currentDateTime());
        Invoice->Save(Utils::CLOSED_ININVOICES_FOLDER);
        QMessageBox::about(0,"OK","Приход учтен");
        Parent->ShowMainWindow();
    }
}
void InTable::Deapply()
{
    if(UI::OKCancelWindow("","Вы действительно хотите отменить приход?"))
    {
        for(int i=0; i<Invoice->Size(); ++i)
        {
            if((Parent->MainStorage->SearchByID((*Invoice)[i].GetID()))>-1)
                (*(Parent->MainStorage))[(Parent->MainStorage->SearchByID((*Invoice)[i].GetID()))].
                        IncreaseQuantity((*Invoice)[i].GetQuantity()*-1);
        }
        Invoice->SetApplied(false);
        QFile DeletingFile("ClosedInInvoices/"+Invoice->GetID()+".xml");
        if(DeletingFile.exists())
            DeletingFile.remove();
        Parent->MainStorage->Save("Storage.xml");
        Invoice->SetDate(QDateTime::currentDateTime());
        Invoice->Save("InInvoices");
        QMessageBox::about(0,"OK","Приход не учтен");
        Parent->ShowMainWindow();
    }
}
void InTable::Delete()
{
    if(!Invoice->GetApplied() && UI::OKCancelWindow("","Вы действительно хотите удалить приход?") && !Invoice->GetApplied())
    {
        QFile DeletingFile(Utils::OPENED_ININVOICES_FOLDER+"/"+Invoice->GetID()+
                           Utils::FILENAME_EXTENSION);
        if(DeletingFile.exists())
            DeletingFile.remove();
        Parent->ShowMainWindow();
    }
}
void InTable::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Return)
    {
        if((Parent->MainStorage->SearchByBarcode(ReadedString))>-1)
            Add(Parent->MainStorage->SearchByBarcode(ReadedString));
        ReadedString.clear();
    }
    else
    {
        ReadedString = ReadedString + event->text();
    }
}
void InTable::CellChanged(int IRow, int IColumn)
{
    if(IColumn == QuantityColumnNumber)
    {
        if(Utils::StringIsQuantity(item(IRow,IColumn)->text()))
        {
            (*Invoice)[Invoice->SearchByID(item(IRow,IDColumnNumber)->text())].
                    SetQuantity(item(IRow,IColumn)->text());
        }
        else
            QMessageBox::about(0,"ERROR!","Incorrect Quantity");
        item(IRow,IColumn)->setText((*Invoice)
               [Invoice->SearchByID(item(IRow,IDColumnNumber)->text())].GetQuantityString());
        TotalLabel->setText(Utils::IntMoneyToString(Invoice->RecalculateTotal()));
        Invoice->Save(Utils::OPENED_ININVOICES_FOLDER);
    }
    if(IColumn == PriceColumnNumber)
    {
        if(!Utils::StringToPrice(item(IRow,IColumn)->text()).isEmpty())
        {
            (*Invoice)[Invoice->SearchByID(item(IRow,IDColumnNumber)->text())].
                SetPrice(Utils::StringToPrice(item(IRow,IColumn)->text()));
            (*(Parent->MainStorage))[Parent->MainStorage->SearchByID(item(IRow,IDColumnNumber)->text())].
                    SetLastPurchasePrice(Utils::StringToPrice(item(IRow,IColumn)->text()));
            item(IRow,IColumn)->setText((*(Parent->MainStorage))[Parent->MainStorage->SearchByID
                    (item(IRow,IDColumnNumber)->text())].GetLastPurchasePriceString());
            Invoice->Save(Utils::OPENED_ININVOICES_FOLDER);
        }
    }
}
