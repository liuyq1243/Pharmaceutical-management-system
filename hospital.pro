QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MyDelegate.cpp \
    MyDelegatePurchase.cpp \
    QLineEditPassword.cpp \
    addmeddialog.cpp \
    addpurchasedialog.cpp \
    addsupplierdialog.cpp \
    adduserdialog.cpp \
    index.cpp \
    main.cpp \
    mainwindow.cpp \
    med_sim.cpp \
    medinfo.cpp \
    modifymeddialog.cpp \
    modifypurchasedialog.cpp \
    modifysupplierdialog.cpp \
    modifyuserdialog.cpp \
    mytableview.cpp \
    purchase.cpp \
    purchasedetailsdialog.cpp \
    qanimationstackedwidget.cpp \
    supplier.cpp \
    user.cpp

HEADERS += \
    QLineEditPassword.h \
    addmeddialog.h \
    addpurchasedialog.h \
    addsupplierdialog.h \
    adduserdialog.h \
    index.h \
    mainwindow.h \
    med_sim.h \
    medinfo.h \
    modifymeddialog.h \
    modifypurchasedialog.h \
    modifysupplierdialog.h \
    modifyuserdialog.h \
    mytableview.h \
    purchase.h \
    purchasedetailsdialog.h \
    qanimationstackedwidget.h \
    supplier.h \
    user.h

FORMS += \
    index.ui \
    mainwindow.ui \
    medinfo.ui \
    purchase.ui \
    supplier.ui \
    user.ui

TRANSLATIONS += \
    hospital_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc
