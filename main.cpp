#include "geotrans.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GeoTrans w;
    w.show();

    return a.exec();
}
