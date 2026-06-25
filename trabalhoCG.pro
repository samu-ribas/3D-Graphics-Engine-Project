QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Forma.cpp \
    Matriz.cpp \
    MeuFrame.cpp \
    camera.cpp \
    main.cpp \
    mainwindow.cpp \
    modelo3d.cpp \
    viewport.cpp

HEADERS += \
    Forma.h \
    Matriz.h \
    MeuFrame.h \
    Poligono.h \
    Ponto.h \
    Reta.h \
    camera.h \
    mainwindow.h \
    modelo3d.h \
    viewport.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    arquivo_de_recursos.qrc
