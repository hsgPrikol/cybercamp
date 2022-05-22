#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "geopoint.h"
#include "geoclass.h"
#include <QQmlContext>
#include <tmp.h>
#include "../protocol/Client/clientgeneral.h"
#include "cameraasist.h"
#include "plantid_api.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));


    ClientGeneral* client=new ClientGeneral();
    engine.rootContext()->setContextProperty("client", client);

    CameraAsist* cameraAsist = new CameraAsist();
    engine.rootContext()->setContextProperty("cameraAsist", cameraAsist);

    PlantID_API* planAPI = new PlantID_API();
    engine.rootContext()->setContextProperty("planAPI", planAPI);

    Tmp tmp;
    tmp.getKeyLeaderBoards();

        GeoPoint* gp=new GeoPoint();
    engine.rootContext()->setContextProperty("gp", gp);

    GeoClass* ss=new GeoClass();
    engine.rootContext()->setContextProperty("geodd", ss);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
