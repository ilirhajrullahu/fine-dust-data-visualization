#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <QCoreApplication>
#include <QDir>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlContext>

#include "Sensor.h"
#include "Connection.h"
#include "Sensormanager.h"
#include "HexagonModel.h"
#include <QGeoCoordinate>
#include <QGeoRectangle>


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlRegisterType<Connection>("Connection", 1, 0, "Connection");
    qmlRegisterType<SensorManager>("SensorManager", 1, 0, "SensorManager");
    qmlRegisterType<HexagonModel>("HexagonModel", 1, 0, "HexagonModel");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<QGeoCoordinate>();
    
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
                
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    SensorManager sm;

    HexagonModel modelBT0(&sm);
    HexagonModel modelBT7(&sm);
    HexagonModel modelBT9(&sm);
    HexagonModel modelBT10(&sm);
    HexagonModel modelBT12(&sm);

    QQmlContext *ctxt = engine.rootContext();
    modelBT0.zoomLevelBT0(modelBT0, ctxt);
    modelBT7.zoomLevelBT7(modelBT7, ctxt);
    modelBT9.zoomLevelBT9(modelBT9, ctxt);
    modelBT10.zoomLevelBT10(modelBT10, ctxt);
    modelBT12.zoomLevelBT12(modelBT12, ctxt);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
