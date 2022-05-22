QT += quick positioning multimedia websockets sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(QZXing/QZXing.pri)

SOURCES += \
        ../protocol/Client/clientgeneral.cpp \
        ../protocol/Server/servergeneral.cpp \
        ../protocol/Server/sql/child.cpp \
        ../protocol/Server/sql/transaction.cpp \
        ../protocol/Server/sql/doctor.cpp \
        ../protocol/Server/sql/locationlog.cpp \
        ../protocol/Server/sql/scheduleelement.cpp \
        ../protocol/Server/sql/servercontroller.cpp \
        ../protocol/commondata.cpp \
        ../protocol/protocolcommunication.cpp \
        cameraasist.cpp \
        geoclass.cpp \
        geopoint.cpp \
        main.cpp \
        plantid_api.cpp \
        tmp.cpp

RESOURCES += qml.qrc \
    ../protocol/Server/resourcesServer.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../protocol/Client/clientgeneral.h \
    ../protocol/Server/servergeneral.h \
    ../protocol/Server/sql/child.h \
    ../protocol/Server/sql/locationlog.h \
    ../protocol/Server/sql/scheduleelement.h \
    ../protocol/Server/sql/servercontroller.h \
    ../protocol/commondata.h \
    ../protocol/protocolcommunication.h \
    cameraasist.h \
    geoclass.h \
    geopoint.h \
    plantid_api.h \
    tmp.h

SUBDIRS += \
    ../protocol/Client/Client.pro \
    ../protocol/Server/Server.pro \
    ../protocol/Server/sql/sql.pro

DISTFILES += \
    ../protocol/Server/localhost.cert \
    ../protocol/Server/localhost.key \
    ../protocol/Server/sql/SuperDataBase.db
