#include "inlisttable.h"
#include "mainscreen.h"

#include <QMessageBox>
#include <QStringList>
#include <QHeaderView>
#include <QMenuBar>
#include <QAction>

InListTable::InListTable(UI* IParent, InInvoiceList* IList) : QTableWidget(IParent), Parent(IParent),
    List(IList)
{
    if(!Parent)
        QMessageBox::about(0,"ERROR!", "No parent in InListTable");
    int ColumnNumberCounter = 0;
    IDColumnNumber = ColumnNumberCounter++;
    DateColumnNumber = ColumnNumberCounter++;
    TotalColumnNumber = ColumnNumberCounter++;
    setColumnCount(ColumnNumberCounter);
    if(!List)
        List = Parent->InList;
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
    MenuBar = new QMenuBar(this);
    QAction* CloseAction = new QAction("Назад", MenuBar);
    connect(CloseAction,SIGNAL(triggered(bool)),Parent,SLOT(ShowMainWindow()));
    MenuBar->addAction(CloseAction);
}
void InListTable::CellDoubleClick(int IRow)
{
    Parent->setCentralWidget(new InTable(Parent, new InInvoice(item(IRow,IDColumnNumber)->text()), true));
    Parent->centralWidget()->show();
    Parent->centralWidget()->setFocus();
    Parent->setMenuBar(((InTable*)Parent->centralWidget())->MenuBar);
}
