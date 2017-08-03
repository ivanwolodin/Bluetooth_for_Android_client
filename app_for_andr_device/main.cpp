#include "widget.h"
#include <QApplication>
#include <devicemanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   /* Widget w;
    w.show();*/

    DeviceManager *dm = new DeviceManager;
    Widget *pc = new Widget;

    QObject::connect(dm, SIGNAL(deviceSelected(QBluetoothAddress)), pc, SLOT(try_connect_to_local_address(QBluetoothAddress)));
    QObject::connect(pc, &Widget::connectedToDevice, pc,&Widget::show);

    dm->show();

    return a.exec();
}
