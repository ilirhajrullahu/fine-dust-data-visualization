# QT -= gui ; Line from backend.pro but its not necessary here 
QT += quick
QT += network
QT += core
QT += widgets
QT += positioning
QT += location

CONFIG += c++11
CONFIG += c++11 console
CONFIG -= app_bundle
# CONFIG += force_debug_info

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Connection.cpp \
        Hexagon.cpp \
        HexagonModel.cpp \
        Record.cpp \
        Sensor.cpp \
        main.cpp \
        Sensormanager.cpp

RESOURCES += qml.qrc \
             icons/24dp/arrow_back.png \
             icons/24dp/burgermenu.png \
             icons/24dp/minus.png \
             icons/24dp/plus.png \


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



DISTFILES += \
    icons/24dp/arrow_back.png \
    icons/24dp/burgermenu.png \
    icons/24dp/minus.png \
    icons/24dp/plus.png

    
HEADERS += \
    Connection.h \
    Hexagon.h \
    HexagonModel.h \
    Record.h \
    Sensor.h \
    Sensormanager.h


