#include <QtWidgets/QApplication>
#include <QtCore/QSettings>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication::setOrganizationName("nehlsen");
    QApplication::setApplicationName("grafitti");
    QApplication app(argc, argv);

    QSettings settings;
    if (!settings.contains("mqtt/host")) settings.setValue("mqtt/host", "10.13.37.39");
    settings.sync();

    auto *main = new MainWindow();
    main->show();

    return app.exec();
}