#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "todomodel.h"
#include "employeemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/untitled/Main.qml"));

    qmlRegisterType<TodoModel>("service.TodoModel", 1, 0, "TodoModel");
    qmlRegisterType<EmployeeModel>("service.EmployeeModel", 1, 0, "EmployeeModel");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
