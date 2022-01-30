#include "Models/ColorLinesSQLiteModel/ColorLinesSQLiteModel.h"
#include "GameStarter/GameStarter.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QtSql>


int main(int argc, char *argv[])
{
    if(GameStarter::makeValidConfiguration() == false) {
        qDebug() << "Failed configuration";
        return -1;
    }

    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    }

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<ColorLinesSQLiteModel>("CustomElements", 1, 0, "ColorLinesModel");

    const QUrl url(QStringLiteral("qrc:/QML/Application.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
