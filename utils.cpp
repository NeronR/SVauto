#include "utils.h"
#include <QMessageBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QMessageBox>

#include <ui.h>

Utils::Utils()
{

}

QString Utils::StringToBarcode(QString IString)
{
    for(int i=0; i<IString.length(); ++i)
    {
        if(!IString[i].isDigit())
            return "";
    }
    return IString;
}
bool Utils::StringIsQuantity(QString IString)
{
    for(int i=0; i<IString.length(); ++i)
    {
        if(!IString[i].isDigit())
            return false;
    }
    return true;
}
QString Utils::StringToPrice(QString IString)
{
    bool PriceFlag = false;
    for(int i=0; i<IString.length(); ++i)
    {
        if(IString[i].isDigit())
            continue;
        if(IString[i]==',')
            IString[i]='.';
        if(IString[i]=='.' && i==IString.length()-3)
        {
            PriceFlag = true;
            continue;
        }
        else
            return "";
    }
    if(PriceFlag)
        return IString;
    else
    {
        return (IString + ".00");
    }
}
long long int Utils::StringMoneyToInt (QString IString)
{
    if(StringIsMoney(IString))
    {
        return IString.remove(".").toInt();
    }
    else
    {
        QMessageBox::about(0,"ERROR!", "Incorrect StringMoneyToInt input");
        return 0;
    }
}
QString Utils::IntMoneyToString (long long int IInt)
{
    QString End;
    if(IInt%100 == 0)
        End = "00";
    else if (IInt%100 > 0 && IInt%100 < 10)
        End = "0"+QString::number(IInt%100);
    else
        End = QString::number(IInt%100);
    return QString::number(IInt/100)+"."+End;
}
bool Utils::StringToBool (QString IString)
{
    if(IString == "0")
        return false;
    if(IString == "1")
        return true;
    QMessageBox::about(0,"ERROR!", "Incorrect StringToBool input");
    return 0;
}
QString Utils::BoolToString (bool IBool)
{
    if(IBool == false)
        return (QString)"0";
    else
        return (QString)"1";
}
bool Utils::StringIsMoney(QString IString)
{
    int i;
    for(i=0; i<IString.length(); ++i)
    {
        if(IString.at(i).isDigit())
            continue;
        else if(IString.at(i)==".")
            break;
        else
            return 0;
    }
    return (i==IString.length()-3 && IString.at(i+1).isDigit() && IString.at(i+2).isDigit());
}

const QString Utils::XML_ROOT_TAG = "root";
const QString Utils::XML_STORAGE_ITEM_TAG = "item";
const QString Utils::XML_IN_ITEM_TAG = "in_item";
const QString Utils::XML_OUT_ITEM_TAG = "out_item";
const QString Utils::XML_ID_TAG = "id";
const QString Utils::XML_NAME_TAG = "name";
const QString Utils::XML_BARCODE_TAG = "barcode";
const QString Utils::XML_QUANTITY_TAG = "quantity";
const QString Utils::XML_PURCHASE_PRICE_TAG = "price1";
const QString Utils::XML_MARKUP_TAG = "markup";
const QString Utils::XML_SELLING_PRICE_TAG = "price2";
const QString Utils::XML_DESCRIPTION_TAG = "description";
const QString Utils::XML_DATE_TAG = "date";
const QString Utils::XML_APPLIED_TAG = "applied";
const QString Utils::XML_STATE_TAG = "state";
const QString Utils::XML_TYPE_TAG = "type";
const bool Utils::OUTITEM_ITEM_TYPE = false;
const bool Utils::OUTITEM_SERVICE_TYPE = true;
const QString Utils::XML_LAST_ID_TAG = "last_id";
const QString Utils::XML_SERVICE_TAG = "service";
const long long int Utils::CAR_MAX_ID = 9999999;
const QString Utils::XML_BRAND_TAG = "brand";
const QString Utils::XML_MODEL_TAG = "model";
const QString Utils::XML_VERSION_TAG = "version";
const QString Utils::XML_SERVICE_NODE_TAG = "service_node";
const QString Utils::DATETIME_FORMAT = "yyyy_MM_dd_hh_mm_ss";
const QString Utils::DATETIME_VISIBLE_FORMAT = "yyyy.MM.dd hh.mm.ss";
const QString Utils::STORAGE_FILENAME = "Storage";
const QString Utils::SERVICES_FILENAME = "Services";
const QString Utils::CARIDS_FILENAME = "CarIDs";
const QString Utils::OPENED_ININVOICES_FOLDER = "InInvoices/";
const QString Utils::CLOSED_ININVOICES_FOLDER = "ClosedInInvoices/";
const QString Utils::OPENED_OUTINVOICES_FOLDER = "OutInvoices/";
const QString Utils::CLOSED_OUTINVOICES_FOLDER = "ClosedOutInvoices/";
const QString Utils::ORDERS_FOLDER = "Orders/";
const QString Utils::FILENAME_EXTENSION = ".xml";


PickButtonWidget::PickButtonWidget(UI* IParent, QStringList IList) : QWidget(IParent), Parent(IParent)
{
    setStyleSheet("QPushButton {font: 18px;}");
    int Sqrt = std::sqrt(IList.length()) + 1;
    DockWidget = new QWidget;
    Group = new QButtonGroup;
    connect(Group, SIGNAL(buttonClicked(int)), this, SLOT(ClickedSinal(int)));
    QGridLayout* Layout = new QGridLayout(this);
    setLayout(Layout);
    for(int i=0; i<IList.length(); ++i)
    {
        QPushButton* Button = new QPushButton(IList[i]);
        Group->addButton(Button, i);
        Button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        Layout->addWidget(Button, i/Sqrt, i%Sqrt);
    }
    IParent->MainWidget->setCurrentIndex(IParent->MainWidget->addWidget(this));
    IParent->DockMainWidget->setCurrentIndex(IParent->DockMainWidget->addWidget(DockWidget));
    IParent->PushDockTitle("");
}
void PickButtonWidget::ClickedSinal(int IID)
{
    delete DockWidget;
    Parent->PopDockTitle();
    emit Clicked(IID);
    delete this;
}
