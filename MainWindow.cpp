#include <QtCore/QSettings>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent)
{
    initUi();
    initMqttClient();

    QSettings settings;
    if (settings.value("mqtt/autoconnect", true).toBool()) {
        m_mqttClient->connectToHost();
    }
}

void MainWindow::handelConnectButtonClicked()
{
    m_mqttClient->connectToHost();
}

void MainWindow::handelDisconnectButtonClicked()
{
    m_mqttClient->disconnectFromHost();
}

void MainWindow::handelWallPowerButtonClicked()
{
    QMQTT::Message message(0, "/ledwall/cmd/power", QByteArray::fromStdString("1"));

    m_mqttClient->publish(message);
}

void MainWindow::onMqttConnected()
{
    setIsConnectedState(true);
}

void MainWindow::onMqttDisconnected()
{
    setIsConnectedState(false);
}

void MainWindow::initMqttClient()
{
    QSettings settings;

    m_mqttClient = new QMQTT::Client(QHostAddress(settings.value("mqtt/host").toString()));
    m_mqttClient->setClientId("grafitti");
    connect(m_mqttClient, &QMQTT::Client::connected,
            this, &MainWindow::onMqttConnected
    );
    connect(m_mqttClient, &QMQTT::Client::disconnected,
            this, &MainWindow::onMqttDisconnected
    );
}

void MainWindow::initUi()
{
    m_btnConnect = new QPushButton(this);
    m_btnConnect->setText("Connect");
    connect(m_btnConnect, &QPushButton::clicked,
            this, &MainWindow::handelConnectButtonClicked
            );

    m_btnDisconnect = new QPushButton(this);
    m_btnDisconnect->setText("Disconnect");
    connect(m_btnDisconnect, &QPushButton::clicked,
            this, &MainWindow::handelDisconnectButtonClicked
    );

    m_btnWallPower = new QPushButton(this);
    m_btnWallPower->setText("Power on/off");
    connect(m_btnWallPower, &QPushButton::clicked,
            this, &MainWindow::handelWallPowerButtonClicked
    );

    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_btnConnect);
    mainLayout->addWidget(m_btnDisconnect);
    mainLayout->addWidget(m_btnWallPower);
    setLayout(mainLayout);

    setIsConnectedState(false);
}

void MainWindow::setIsConnectedState(bool isConnected)
{
    m_btnConnect->setEnabled(!isConnected);
    m_btnDisconnect->setEnabled(isConnected);
    m_btnWallPower->setEnabled(isConnected);
}