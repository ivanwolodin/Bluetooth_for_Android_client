#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QBluetoothSocket>
#include <QByteArray>
#include <QDataStream>

//probably QBArray is unneccessary


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(value_for_prgs);
    is_local_bluetooth();   //выводит информацию о наличаи либо отсутствии Bluetooth модуля

    //открываем Последовательный порт!

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    //socket->open(QIODevice::WriteOnly);
   // socket->setSocketState(QBluetoothSocket::ConnectingState);
    QByteArray  byteArr;
    QDataStream out(&byteArr, QIODevice::ReadWrite);
    QBluetoothLocalDevice localDevice;
    QString localName = localDevice.name();
    out <<  localName << '\n';
    socket->write(byteArr);

    //connect( socket,&QBluetoothSocket::error(QBluetoothSocket::UnknownSocketError 2),this,&Widget::isConnected_);

 //   qDebug()<< socket->isOpen();
    connect(ui->pushButton,
            SIGNAL(clicked(bool)),this,
            SLOT(try_connect_to_local_address( )));
    //connect(socket,SIGNAL(connected()),this,SLOT(connected_to_local()));
     connect( socket,&QBluetoothSocket::connected,this,&Widget::info_that_connected_to_local);
      //connect(this, &Widget::connectToDevice,  &Widget::try_connect_to_local_address);
     connect(this,SIGNAL(connected()),this,SLOT(isConnected_()));
 }

Widget::~Widget()
{
    delete ui;
}

bool Widget::is_local_bluetooth()
{
  //  QBluetoothAddress* addres=new QBluetoothAddress(bluetooth_local.address());
 //   qDebug()<<addres->toString()<<endl;
//    QBluetoothAddress address("00:1A:7D:DA:71:15");

//    qDebug()<<bluetooth_local.address().toString()<<endl;
    if(bluetooth_local.isValid()==true){ui->label->setText("There is BT!");
 //         emit try_to_connect(address);
    return true;}
    else{  ui->label->setText("No BT!");
    return false;}
}

// ОТПРАВКА ДАННЫХ ПРОИСХОДИТ! в Последовательный порт.
// Теперь задача: считывать эти данные в Desktop-e и НУЖНО УСТАНОВИТЬ СОЕДИНЕНИЕ С Bluetooth модулем!
void Widget::on_plus_clicked()
{

     //   qDebug()<< socket->isOpen();
    //qDebug()<<bluetooth_local.address().toString()<<endl;
    if(value_for_prgs!=100)
    value_for_prgs+=10;
    ui->progressBar->setValue(value_for_prgs);
    /*добавить отправку данных в последовательный порт
     * но перед этим девайс надо открыть!
     */
    //неоптимальное решение, как минимум, так как отправляем всего лишь одну цифру в ByteAray
    QByteArray  byteArr;
    QDataStream out(&byteArr, QIODevice::WriteOnly);
    out << 1 << '\n';        //если плюс, то отправляем единицу!

   // socket->write(byteArr);
    for(int i=0;i<100000;i++){};
     qDebug()<<socket->write(byteArr)<<endl;
      for(int i=0;i<100000;i++){};
    // socket->writeData("1",3);
   //   qDebug()<<socket->readAll()<<endl;
}

void Widget::on_minus_clicked()
{
    if(value_for_prgs!=0)
    value_for_prgs-=10;
    ui->progressBar->setValue(value_for_prgs);
    /* добавить отправку данных в последовательный порт */

    QByteArray  byteArr;
    QDataStream out(&byteArr, QIODevice::WriteOnly);
    out << 2 << '\n';        //если минус, то отправляем двойку!

   qDebug()<< socket->write(byteArr)<<endl;
 //   qDebug()<<socket->readAll()<<endl;
}

void Widget::try_connect_to_local_address( QBluetoothAddress address)
{

     qDebug()<<socket->errorString()<<endl;
     qDebug()<<"trying to connect"<<endl;
  // QBluetoothAddress address("00:1A:7D:DA:71:15");
     qDebug()<<address.toString()<<endl;
    if(socket->state() != QBluetoothSocket::UnconnectedState)
   {
        qDebug()<<"socket.state"<<endl;
       if(address != socket->peerAddress())//???
       {
            qDebug()<<"socket.peeradress"<<endl;
           socket->disconnectFromService();
           socket->connectToService(address, QBluetoothUuid(QBluetoothUuid::SerialPort));
       }
        else
            emit connected();
   }
   else{
        qDebug()<<"else"<<endl;
        socket->connectToService(address, QBluetoothUuid(QBluetoothUuid::SerialPort));
        qDebug()<<socket->error()<<endl;
        qDebug()<<socket->errorString()<<endl;
    }
    emit bluetooth_local.deviceConnected(address);
//    qDebug()<<"Error SOCKEt,,???"<<endl;
    qDebug()<<socket->errorString()<<endl;
    qDebug()<<socket->state()<<endl;
    emit connectedToDevice();

}

void Widget::info_that_connected_to_local()
{
    qDebug()<<"Connected!"<<endl;
}

void Widget::read_data()
{
    while(1){

        //считывать в бесконечном цикле, что нам прислал последовательный порт

    }
}

void Widget::isConnected_()
{
    ui->label->setText("UnConnected!");
}


