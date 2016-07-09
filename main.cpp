#include <QApplication>
#include <QTextCodec>
#include <QDir>

#include "ui.h"
#include "storage.h"

int main(int argc, char *argv[])
{
    QTextCodec *russianCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(russianCodec);
    QApplication a(argc, argv);

    if(!QDir(Utils::OPENED_ININVOICES_FOLDER).exists())
        QDir().mkdir(Utils::OPENED_ININVOICES_FOLDER);
    if(!QDir(Utils::CLOSED_ININVOICES_FOLDER).exists())
        QDir().mkdir(Utils::CLOSED_ININVOICES_FOLDER);
    if(!QDir(Utils::OPENED_OUTINVOICES_FOLDER).exists())
        QDir().mkdir(Utils::OPENED_OUTINVOICES_FOLDER);
    if(!QDir(Utils::CLOSED_OUTINVOICES_FOLDER).exists())
        QDir().mkdir(Utils::CLOSED_OUTINVOICES_FOLDER);

    a.setStyleSheet("QPushButton {"
                    "background-color: rgb(230,230,230);"
                    "border: 2px solid rgb(100,100,100);"
                    "padding: 7px; "
                    "min-width: 50px; }"
                    "QPushButton:hover {"
                    "background-color: rgb(180,180,180); }"
                    "QPushButton:pressed {"
                    "background-color: rgb(100,100,100); }");

    UI w;
    w.showMaximized();
    return a.exec();
}
