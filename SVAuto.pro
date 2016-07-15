QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SVAuto
TEMPLATE = app


SOURCES += main.cpp \
    ui.cpp \
    storageitem.cpp \
    storage.cpp \
    settings.cpp \
    storagetable.cpp \
    mainscreen.cpp \
    initem.cpp \
    outitem.cpp \
    ininvoice.cpp \
    intable.cpp \
    ininvoicelist.cpp \
    inlisttable.cpp \
    outinvoice.cpp \
    outinvoicelist.cpp \
    outlisttable.cpp \
    outtable.cpp \
    user.cpp \
    order.cpp \
    service.cpp \
    utils.cpp \
    services.cpp \
    carids.cpp \
    servicestable.cpp \
    servicepricetable.cpp

HEADERS  += \
    ui.h \
    storageitem.h \
    storage.h \
    settings.h \
    storagetable.h \
    mainscreen.h \
    initem.h \
    outitem.h \
    ininvoice.h \
    intable.h \
    ininvoicelist.h \
    inlisttable.h \
    outinvoice.h \
    outinvoicelist.h \
    outlisttable.h \
    outtable.h \
    user.h \
    order.h \
    service.h \
    utils.h \
    services.h \
    carids.h \
    servicestable.h \
    servicepricetable.h
