#include "mainscreen.h"
#include "ui.h"

#include <QMessageBox>
#include <QGridLayout>

MainScreen::MainScreen(UI* IParent) : QWidget(IParent), Parent (IParent)
{
    setStyleSheet("QPushButton {font: 18px;}");
    if(!parent())
       QMessageBox::about(0, "ERROR!", "No parent in MainScreen");
    QGridLayout* Layout = new QGridLayout(this);

    if(true)
    {
        QPushButton* StorageButton = new QPushButton("Просмотреть список товаров", this);
        StorageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(StorageButton, 0, 0, 1, 5);
        connect(StorageButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowStorageTable()));
    }
    if(true)
    {
        QPushButton* StorageEditButton = new QPushButton("Редактировать", this);
        StorageEditButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(StorageEditButton, 0, 5, 1, 1);
        connect(StorageEditButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowEditStorageTable()));
    }

    if(true)
    {
        QPushButton* ServicesButton = new QPushButton("Просмотреть список услуг", this);
        ServicesButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(ServicesButton, 1, 0, 1, 5);
        connect(ServicesButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowServicesTable()));
    }
    if(true)
    {
        QPushButton* ServicesEditButton = new QPushButton("Редактировать", this);
        ServicesEditButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(ServicesEditButton, 1, 5, 1, 1);
        connect(ServicesEditButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowEditServicesTable()));
    }

    if(true)
    {
        QPushButton* InButton = new QPushButton("Новый приход", this);
        InButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(InButton, 2, 0, 1, 3);
        connect(InButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowInTable()));
    }
    if(true)
    {
        QPushButton* OutButton = new QPushButton("Новый расход", this);
        OutButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(OutButton, 2, 3, 1, 3);
        connect(OutButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowOutTable()));
    }
    if(true)
    {
        QPushButton* InListButton = new QPushButton("Список приходов");
        InListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(InListButton, 3, 0, 1, 3);
        connect(InListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowInListTable()));
    }
    if(true)
    {
        QPushButton* InClosedListButton = new QPushButton("Список закрытых приходов");
        InClosedListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(InClosedListButton, 4, 0, 1, 3);
        connect(InClosedListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowInClosedListTable()));
    }
    if(true)
    {
        QPushButton* OutListButton = new QPushButton("Список расходов");
        OutListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(OutListButton, 3, 3, 1, 3);
        connect(OutListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowOutListTable()));
    }
    if(true)
    {
        QPushButton* OutClosedListButton = new QPushButton("Список закрытых расходов");
        OutClosedListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(OutClosedListButton, 4, 3, 1, 3);
        connect(OutClosedListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowOutClosedListTable()));
    }
    if(true)
    {
        QPushButton* CarsButton = new QPushButton("Автомобили", this);
        CarsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(CarsButton, 5, 4, 1, 1);
        connect(CarsButton, SIGNAL(clicked(bool)), Parent, SLOT(ShowCarsTable()));
    }
    if(true)
    {
        QPushButton* SettingsButton = new QPushButton("Настройки", this);
        SettingsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(SettingsButton, 5, 5, 1, 1);
        connect(SettingsButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowSettingsWidget()));
    }
    for(int i=0; i<Layout->columnCount(); ++i)
        Layout->setColumnStretch(i, 1);
}
