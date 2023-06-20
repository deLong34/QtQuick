#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
#include <qmltablemodel.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    QMLTableModel model;
    model.appendRowElement(QMLTableModel::RowElement{1, "Иван", "Петров", {"Сергей Сергеев", "Петр Иванович"}});
    model.appendRowElement(QMLTableModel::RowElement{2, "Стас", "Михайлов", {"Михаил Стасовa","Саша Сидоров", "Светлана Усова"}});
    model.appendRowElement(QMLTableModel::RowElement{3, "Владимир", "Пузиков", {"Иван Петров", "Саша Сидоровv", "Сергей Свиридов"}});
    engine.rootContext()->setContextProperty("mdl", &model);

    engine.load(url);
    return app.exec();
}
