QT -= gui
 QT += websockets sql

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        sql/locationlog.cpp \
        sql/child.cpp \
        sql/scheduleelement.cpp \
        sql/doctor.cpp \
        sql/transaction.cpp \
        sql/servercontroller.cpp \
        ../commondata.cpp \
        ../protocolcommunication.cpp \
        main.cpp \
        servergeneral.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    sql/locationlog.h \
    sql/child.h \
    sql/scheduleelement.h \
    sql/doctor.h \
    sql/transaction.h \
    sql/servercontroller.h \
    ../commondata.h \
    ../protocolcommunication.h \
    servergeneral.h

RESOURCES += resourcesServer.qrc
