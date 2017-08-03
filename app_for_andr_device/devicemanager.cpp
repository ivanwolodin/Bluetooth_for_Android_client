#include "devicemanager.h"
#include "ui_devicemanager.h"


#include <QBluetoothAddress>
#include <QListWidgetItem>

DeviceManager::DeviceManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceManager)
{
    ui->setupUi(this);

    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
        this, &DeviceManager::deviceDiscovered);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &DeviceManager::discoveryFinished);

    connect(ui->discovery, &QPushButton::released,
            this, &DeviceManager::startDiscovery);
    connect(ui->list, &QListWidget::activated,
            this, &DeviceManager::selectDevice);

    if(localDevice.isValid())
    {
        localDevice.powerOn();

        ui->status->setText("Click \"search for devices\"");
        ui->discovery->setEnabled(true);
    }
    else
        ui->status->setText("Bluetooth module not found!");
}

DeviceManager::~DeviceManager()
{
    delete ui;
    delete discoveryAgent;
}

void DeviceManager::startDiscovery()
{
    ui->status->setText("Searching devices...");
    ui->discovery->setEnabled(false);
    ui->list->clear();

    discoveryAgent->start();
}

void DeviceManager::selectDevice(const QModelIndex &item)
{
    QString name = item.data(Qt::DisplayRole).toString();
    ui->status->setText("Connecting to " + name + "...");
    QString data = item.data(Qt::UserRole).toString();
    QBluetoothAddress address(data);
    emit deviceSelected(address);
}

void DeviceManager::deviceConnected()
{
    ui->status->setText("Select device for connecting");
}


void DeviceManager::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    QString name = device.name();
    QListWidgetItem *item = new QListWidgetItem(name);
    QVariant qv(device.address().toString());
    item->setData(Qt::UserRole, qv);

    QBluetoothLocalDevice::Pairing pairingStatus = localDevice.pairingStatus(device.address());
    if (pairingStatus == QBluetoothLocalDevice::Paired ||
            pairingStatus == QBluetoothLocalDevice::AuthorizedPaired)
        item->setTextColor(QColor(Qt::black));
    else
        item->setTextColor(QColor(Qt::red));

    ui->list->addItem(item);
}

void DeviceManager::discoveryFinished()
{
    ui->status->setText("Select device for connecting");
    ui->discovery->setEnabled(true);
}
