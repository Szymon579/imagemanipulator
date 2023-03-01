#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QIcon>
#include <QQuickImageProvider>
#include <QPixmap>

#include "imageprocessor.h"
#include "jsonhandler.h"
//#include "imageprovider.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    //application icon on title bar
    app.setWindowIcon(QIcon(":/ui/assets/app_icon.png"));

    //required by QML FileDialog to work
    app.setOrganizationName("myself");
    app.setOrganizationDomain("myself.com");

    QQmlApplicationEngine engine;

    //make the class object available for QML
    ImageProcessor *imageProcessor = new ImageProcessor();
    engine.rootContext()->setContextProperty("imageProcessor", imageProcessor);

    JsonHandler *jsonHandler = new JsonHandler();
    engine.rootContext()->setContextProperty("jsonHandler", jsonHandler);


    //pixmap loading C++ -> QML
    //QQuickImageProvider imageProvider(QPixmap);
    //engine.addImageProvider("imageProvider", new ImageProvider(imageProcessor));


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
