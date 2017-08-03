#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QWidget>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>

namespace Ui {
class DeviceManager;
}

/*!
 * \brief Менеджер устройств
 */
class DeviceManager : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Инициализирует менеджер устройтв
     * \param parent предок
     */
    explicit DeviceManager(QWidget *parent = 0);
    ~DeviceManager();

signals:
    /*!
     * \brief Устройство выбрано для подключения
     * \param address MAC-адрес устройства
     */
    void deviceSelected(QBluetoothAddress address);

public slots:
    /*!
     * \brief Вызывается при успешном подключении к устройству
     */
    void deviceConnected();

private slots:
    /*!
     * \brief Вызывается при обнаружении устройства
     * \param device информация об устройстве
     */
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    /*!
     * \brief Вызывается при завершении поиска устройств
     */
    void discoveryFinished();

    /*!
     * \brief Вызывается при запуске поиска устройств
     */
    void startDiscovery();
    /*!
     * \brief Вызывается при нажатии на устройтво в списке устройтв
     * \param index устройтво
     */
    void selectDevice(const QModelIndex &index);

private:
    /*!
     * \brief Графический интерфейс
     */
    Ui::DeviceManager *ui;
    /*!
     * \brief Агент для поиска устройств
     */
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    /*!
     * \brief Информация о локальном устройстве
     */
    QBluetoothLocalDevice localDevice;
};

#endif // DEVICEMANAGER_H
