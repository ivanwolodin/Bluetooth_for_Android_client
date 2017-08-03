#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QBluetoothAddress>
#include <QBluetoothSocket>

//для обеспечения соединения с BT девайсами
#include <QBluetoothSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
int value_for_prgs=50;
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

QBluetoothLocalDevice bluetooth_local;
QBluetoothSocket *socket;
//QBluetoothAddress* address = new QBluetoothAddress("00:1A:7D:DA:71:15");

bool is_local_bluetooth();

signals:

void  deviceConnected(QBluetoothAddress );
void signal_on_plu_clicked(); // испускаться будут в read_data()
void signal_on_min_clicked(); // испускаться будут в read_data()
void connectedToDevice();
void connected();

public slots:
    void on_plus_clicked();    // также здесь отправка данных в КОМ порт
    void on_minus_clicked();   // также здесь отправка данных в КОМ порт
    void try_connect_to_local_address(QBluetoothAddress address); //  "00:1A:7D:DA:71:15"
    void info_that_connected_to_local();
    void read_data();

    void isConnected_();

    /*
     * нам нужно считывать данные из последовательного порта
     * и отправлять данные в последовательный порт. Следовательно,
     * два слота send_plus() and send_minus() - для отправки сигнала в КОМ-порт
     *  /думаю, можно встроить это в on_plus_clicked and on_minus_clicked/
     *
     * и функцию read_data(), которая считывает то, что есть в последовательном порте
     * также должно быть два сигнала, которые испускаются в read_data(), в зависимости от того, что
     * пришло из КОМ порта
    */


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
