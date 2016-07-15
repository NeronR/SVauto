#include "outlisttable.h"
#include "outtable.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QHBoxLayout>

OutListTable::OutListTable(UI* IParent, OutInvoiceList* IList) : QTableWidget(IParent), Parent(IParent),
    List(IList)
{
    if(!Parent)
        QMessageBox::about(0,"ERROR!", "No parent in OutListTable");
    int ColumnNumberCounter = 0;
    IDColumnNumber = ColumnNumberCounter++;
    DateColumnNumber = ColumnNumberCounter++;
    TotalColumnNumber = ColumnNumberCounter++;
    setColumnCount(ColumnNumberCounter);
    if(!List)
        List = Parent->OutList;
    List->Load("");
    QStringList SList;
    SList << "ID" << "Дата" << "Сумма";
    setHorizontalHeaderLabels(SList);
    verticalHeader()->hide();

    for(int i=0; i<List->Size(); ++i)
    {
        setRowCount(rowCount()+1);
        setItem(rowCount()-1,IDColumnNumber,new QTableWidgetItem((*List)[i].GetID()));
        item(rowCount()-1,IDColumnNumber)->setFlags(item(rowCount()-1,IDColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,DateColumnNumber,new QTableWidgetItem((*List)[i].GetDateString()));
        item(rowCount()-1,DateColumnNumber)->setFlags(item(rowCount()-1,DateColumnNumber)->
                                                    flags() & ~Qt::ItemIsEditable);
        setItem(rowCount()-1,TotalColumnNumber,new QTableWidgetItem((*List)[i].GetTotalString()));
            item(rowCount()-1,TotalColumnNumber)->setFlags(item(rowCount()-1,TotalColumnNumber)->
                                                        flags() & ~Qt::ItemIsEditable);
    }
    setSortingEnabled(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(CellDoubleClick(int)));

    DockWidget = new QWidget;
    QHBoxLayout* DockLayout = new QHBoxLayout(DockWidget);
    QPushButton* CloseButton = new QPushButton("Назад");
    connect(CloseButton, SIGNAL(clicked(bool)), this, SLOT(Close()));
    DockLayout->addWidget(CloseButton, 0, Qt::AlignRight);
    Parent->PushDockTitle("Список приходов");
    Parent->DockMainWidget->setCurrentIndex(Parent->DockMainWidget->addWidget(DockWidget));
}
void OutListTable::CellDoubleClick(int IRow)
{
    OutTable* Table = new OutTable(Parent, new OutInvoice(item(IRow,IDColumnNumber)->text()), true);
    connect(Table, SIGNAL(Closing()), this, SLOT(Update()));
    Parent->MainWidget->setCurrentIndex(Parent->MainWidget->addWidget(Table));
    Parent->centralWidget()->show();
    Parent->centralWidget()->setFocus();
}
void OutListTable::Update()
{
    Parent->MainWidget->insertWidget((Parent->MainWidget->indexOf(this)), new OutListTable(Parent, List));
    Close();
}
void OutListTable::Close()
{
    Parent->PopDockTitle();
    delete DockWidget;
    delete this;
}
