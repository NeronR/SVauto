#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    Utils();
    static long long int StringMoneyToInt (QString IString);
    static QString IntMoneyToString (long long int IInt);
    static bool StringToBool (QString IString);
    static QString BoolToString (bool IBool);
    static bool StringIsMoney(QString IString);
    static QString StringToBarcode(QString IString);
    static bool StringIsQuantity(QString IString);
    static QString StringToPrice(QString IString);

    static const QString XML_ROOT_TAG;
    static const QString XML_STORAGE_ITEM_TAG;
    static const QString XML_IN_ITEM_TAG;
    static const QString XML_IN_TOTAL_TAG;
    static const QString XML_OUT_ITEM_TAG;
    static const QString XML_OUT_TOTAL_TAG;
    static const QString XML_ID_TAG;
    static const QString XML_NAME_TAG;
    static const QString XML_BARCODE_TAG;
    static const QString XML_QUANTITY_TAG;
    static const QString XML_PURCHASE_PRICE_TAG;
    static const QString XML_MARKUP_TAG;
    static const QString XML_SELLING_PRICE_TAG;
    static const QString XML_DESCRIPTION_TAG;
    static const QString XML_DATE_TAG;
    static const QString XML_APPLIED_TAG;
    static const QString XML_LAST_ID_TAG;
    static const QString XML_SERVICE_TAG;
    static const long long int CAR_MAX_ID;
    static const QString XML_BRAND_TAG;
    static const QString XML_MODEL_TAG;
    static const QString XML_VERSION_TAG;
    static const QString DATETIME_FORMAT;
    static const QString DATETIME_VISIBLE_FORMAT;
    static const QString STORAGE_FILENAME;
    static const QString SERVICES_FILENAME;
    static const QString CARIDS_FILENAME;
    static const QString OPENED_ININVOICES_FOLDER;
    static const QString CLOSED_ININVOICES_FOLDER;
    static const QString OPENED_OUTINVOICES_FOLDER;
    static const QString CLOSED_OUTINVOICES_FOLDER;
    static const QString FILENAME_EXTENSION;
};

#endif // UTILS_H
