TARGET = pedometer

QT += dbus

CONFIG += sailfishapp link_pkgconfig
PKGCONFIG += sensord-qt5 sailfishapp

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

SOURCES += src/pedometer.cpp \
    src/stepcounter.cpp

OTHER_FILES += qml/pedometer.qml \
    qml/cover/CoverPage.qml \
    rpm/pedometer.spec \
    pedometer.desktop \
    qml/pages/Pedometer.qml

HEADERS += \
    src/stepcounter.h

