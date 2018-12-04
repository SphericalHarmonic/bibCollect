#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include <CReaderModel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    CReaderModel readerModel;
    engine.rootContext()->setContextProperty("readerModel", &readerModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
