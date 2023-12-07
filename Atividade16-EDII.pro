QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    etiqueta.cpp \
    main.cpp \
    mainwindow.cpp \
    tabela.cpp

HEADERS += \
    etiqueta.h \
    grafo.h \
    grafodirecionado.h \
    grafonaoorientado.h \
    lista.h \
    mainwindow.h \
    no.h \
    nografo.h \
    tabela.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
