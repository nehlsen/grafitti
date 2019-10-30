#ifndef GRAFITTI_MAINWINDOW_H
#define GRAFITTI_MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <qmqtt.h>

class QPushButton;

class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected slots:
    void handelConnectButtonClicked();
    void handelDisconnectButtonClicked();
    void handelWallPowerButtonClicked();

    void onMqttConnected();
    void onMqttDisconnected();

protected:
    void initMqttClient();
    QMQTT::Client *m_mqttClient = nullptr;

    void initUi();
    QPushButton *m_btnConnect = nullptr;
    QPushButton *m_btnDisconnect = nullptr;
    QPushButton *m_btnWallPower = nullptr;

    void setIsConnectedState(bool isConnected);
};

#endif //GRAFITTI_MAINWINDOW_H
