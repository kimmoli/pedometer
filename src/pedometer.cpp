#include <sailfishapp.h>
#include <QtQml>
#include <QScopedPointer>
#include <QQuickView>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QCoreApplication>
#include "stepcounter.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<StepCounter>("harbour.pedometer", 1, 0, "StepCounter");

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    view->setSource(SailfishApp::pathTo("qml/pedometer.qml"));
    view->show();

    return app->exec();
}
