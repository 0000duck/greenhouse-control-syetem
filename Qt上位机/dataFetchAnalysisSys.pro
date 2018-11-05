#-------------------------------------------------
#
# Project created by QtCreator 2017-07-09T18:16:51
#
#-------------------------------------------------

QT       += core gui
QT       += core
QT       += sql
QT       += network
QT       += charts
QT       += quickwidgets
QT       += qml quick
QT       += axcontainer
INCLUDEPATH +=D:/Qt/opencv3.0_use/include\
             D:/Qt/opencv3.0_use/include/opencv2\
             D:/Qt/opencv3.0_use/include/opencv
LIBS += -L
LIBS += -L D:/Qt/opencv3.0_use/lib/libopencv_*.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataFetchAnalysisSys
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Logindialog.cpp \
    Registerdialog.cpp \
    tool_button.cpp \
    mainwindow.cpp \
    firstpageWidget.cpp \
    realdataDisplay.cpp \
    historydatadisplay.cpp \
    devicesManage.cpp \
    dapengIntro.cpp \
    companyIntro.cpp \
    sysIntro.cpp \
    server.cpp \
    tcpclientsocket.cpp \
    tcpserver.cpp \
    text_label.cpp \
    customtablemodel.cpp \
    tablewidget.cpp \
    controlonoff.cpp \
    myswitchitem.cpp \
    control.cpp \
    sliderruler.cpp \
    control_slider.cpp \
    userManage.cpp \
    RealTimeCurveQChartWidget.cpp \
    myswitchbutton.cpp \
    switchitem.cpp \
    custom_window.cpp \
    messagedialog.cpp \
    titlecontentwidget.cpp \
    qledindicator.cpp \
    warningHandle.cpp \
    diagremove.cpp \
    tableview.cpp \
    bigsystem.cpp \
    subsystem.cpp \
    dialog.cpp

HEADERS += \
    control.h \
    Logindialog.h \
    Registerdialog.h \
    tool_button.h \
    mainwindow.h \
    firstpageWidget.h \
    realdataDisplay.h \
    historydatadisplay.h \
    devicesManage.h \
    dapengIntro.h \
    companyIntro.h \
    sysIntro.h \
    server.h \
    tcpclientsocket.h \
    tcpserver.h \
    text_label.h \
    customtablemodel.h \
    tablewidget.h \
    controlonoff.h \
    myswitchitem.h \
    control.h \
    sliderruler.h \
    control_slider.h \
    userManage.h \
    RealTimeCurveQChartWidget.h \
    myswitchbutton.h \
    myswitchbutton.h \
    switchitem.h \
    custom_window.h \
    messagedialog.h \
    titlecontentwidget.h \
    qledindicator.h \
    warningHandle.h \
    warningHandle.h \
    diagremove.h \
    tableview.h \
    subsystem.h \
    bigsystem.h \
    dialog.h

FORMS += \
    RegisterDialog.ui \
    LoginDialog.ui \
    usermanage.ui \
    mainwindow.ui \
    controlonoff.ui \
    usermanage.ui \
    test.ui \
    messagedialog.ui \
    titlecontentwidget.ui \
    diagremove.ui \
    devicemanage.ui \
    dialog.ui

RESOURCES += \
    images.qrc
RC_FILE +=logo.rc
