#include "mainscreen.h"
#include "ui.h"

#include <QMessageBox>

MainScreen::MainScreen(UI* IParent) : QWidget(IParent), Parent (IParent)
{
    setStyleSheet("QPushButton {font: 18px;}");
    if(!parent())
       QMessageBox::about(0, "ERROR!", "No parent in MainScreen");
    QVBoxLayout* Layout = new QVBoxLayout(this);

    QHBoxLayout* StorageLayout = new QHBoxLayout();
    if(true)
    {
        QPushButton* StorageButton = new QPushButton("Просмотреть список товаров", this);
        StorageButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        StorageLayout->addWidget(StorageButton, 5);
        connect(StorageButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowStorageTable()));
    }
    if(true)
    {
        QPushButton* StorageEditButton = new QPushButton("Редактировать", this);
        StorageEditButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        StorageLayout->addWidget(StorageEditButton, 1);
        connect(StorageEditButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowEditStorageTable()));
    }
    Layout->addLayout(StorageLayout);

    QHBoxLayout* ServicesLayout = new QHBoxLayout();
    if(true)
    {
        QPushButton* ServicesButton = new QPushButton("Просмотреть список услуг", this);
        ServicesButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ServicesLayout->addWidget(ServicesButton, 5);
        connect(ServicesButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowServicesTable()));
    }
    if(true)
    {
        QPushButton* ServicesEditButton = new QPushButton("Редактировать", this);
        ServicesEditButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        ServicesLayout->addWidget(ServicesEditButton, 1);
        connect(ServicesEditButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowEditServicesTable()));
    }
    Layout->addLayout(ServicesLayout);

    if(true)
    {
        QPushButton* InButton = new QPushButton("Новый приход", this);
        InButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(InButton);
        connect(InButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowInTable()));
    }
    if(true)
    {
        QPushButton* OutButton = new QPushButton("Новый расход", this);
        OutButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(OutButton);
        connect(OutButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowOutTable()));
    }
    if(true)
    {
        QPushButton* InListButton = new QPushButton("Список приходов");
        InListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(InListButton);
        connect(InListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowInListTable()));
    }
    if(true)
    {
        QPushButton* InClosedListButton = new QPushButton("Список закрытых приходов");
        InClosedListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(InClosedListButton);
        connect(InClosedListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowInClosedListTable()));
    }
    if(true)
    {
        QPushButton* OutListButton = new QPushButton("Список расходов");
        OutListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(OutListButton);
        connect(OutListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowOutListTable()));
    }
    if(true)
    {
        QPushButton* OutClosedListButton = new QPushButton("Список закрытых расходов");
        OutClosedListButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(OutClosedListButton);
        connect(OutClosedListButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowOutClosedListTable()));
    }
    if(true)
    {
        QPushButton* SettingsButton = new QPushButton("Настройки", this);
        SettingsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(SettingsButton);
        connect(SettingsButton,SIGNAL(clicked(bool)),Parent,SLOT(ShowSettingsWidget()));
    }
    setLayout(Layout);
}
