#ifndef GEOTRANS_H
#define GEOTRANS_H

#include <QMainWindow>
#include <QSettings>
#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoPositionInfoSource>
#include <QGeoSatelliteInfoSource>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QFileDialog>
#include "cnmeagen.h"


namespace Ui {
class GeoTrans;
}

class GeoTrans : public QMainWindow
{
    Q_OBJECT

public:
    explicit GeoTrans(QWidget *parent = 0);
    ~GeoTrans();

private slots:
    void on_cmdQuit_clicked();
    void on_cmdStart_clicked();
    void on_Update(const QGeoPositionInfo &update);
    void on_pushButton_clicked();
    void on_SatUseUpdate(QList<QGeoSatelliteInfo> llist);
    void on_SatViewUpdate(QList<QGeoSatelliteInfo> llist);

private:    
    Ui::GeoTrans *ui;
    QSettings* m_settings;
    QWidget *m_parent;
    QGeoPositionInfoSource *m_sat;
    QGeoSatelliteInfoSource *m_satinf;
    QHostAddress *m_host;
    QUdpSocket *m_socket;         
    QString* m_filename;
    CNmeaGen *m_nmea;
    QList<QGeoSatelliteInfo> m_inView;
    QList<QGeoSatelliteInfo> m_inUse;
};

#endif // GEOTRANS_H
