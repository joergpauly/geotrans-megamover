#include "geotrans.h"
#include "ui_geotrans.h"



GeoTrans::GeoTrans(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GeoTrans)
{
    ui->setupUi(this);
    m_parent = parent;
    m_settings = new QSettings("MEGAMover.de","GeoTrans",this);
    ui->txtIPadr->setText(m_settings->value("IPadr","").toString());
    ui->txtPort->setText(m_settings->value("Port","").toString());
    m_sat = QGeoPositionInfoSource::createDefaultSource(this);
    if(m_sat)
    {
        QStringList llst = m_sat->availableSources();
        ui->txtState->append(m_sat->sourceName());
        m_sat->setPreferredPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
        m_sat->setUpdateInterval(1000);
    }
    m_satinf = QGeoSatelliteInfoSource::createDefaultSource(this);
    if(m_satinf)
    {
        m_satinf->setUpdateInterval(1000);
    }
    connect(m_sat,SIGNAL(positionUpdated(QGeoPositionInfo)),SLOT(on_Update(QGeoPositionInfo)));      
    connect(m_satinf, SIGNAL(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)), this, SLOT(on_SatUseUpdate(QList<QGeoSatelliteInfo>)));
    connect(m_satinf, SIGNAL(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)), this, SLOT(on_SatViewUpdate(QList<QGeoSatelliteInfo>)));
}

GeoTrans::~GeoTrans()
{
    delete ui;
    delete m_settings;
    delete m_sat;
    delete m_socket;
}

void GeoTrans::on_cmdQuit_clicked()
{
    this->close();
}

void GeoTrans::on_cmdStart_clicked()
{
    m_inView = new QList<QGeoSatelliteInfo>();
    m_inUse = new QList<QGeoSatelliteInfo>();
    m_settings->setValue("IPadr", QVariant(ui->txtIPadr->text()));
    m_settings->setValue("Port", QVariant(ui->txtPort->text()));    
    m_host = new QHostAddress(m_settings->value("IPadr").toString());
    m_socket = new QUdpSocket();
    m_nmea = new CNmeaGen();
    m_nmea->setRMC(true);
    m_nmea->setGSA(false);
    m_nmea->setGGA(true);
    m_sat->startUpdates();
    m_satinf->startUpdates();
}

void GeoTrans::on_Update(const QGeoPositionInfo &update)
{
    m_nmea->generate(update, m_inView, m_inUse);
    QString lrmc = m_nmea->sRMC();
    if(lrmc.length() > 6)
    {
        m_socket->writeDatagram(lrmc.toLocal8Bit(),*m_host,m_settings->value("Port").toInt());
        ui->txtState->append(lrmc);
    }

    QString lgga = m_nmea->sGGA();
    if(lgga.length() > 6)
    {
        m_socket->writeDatagram(lgga.toLocal8Bit(),*m_host,m_settings->value("Port").toInt());
        ui->txtState->append(lgga);
    }

    QString lgsa = m_nmea->sGSA();
    if(lgsa.length() > 6)
    {
        m_socket->writeDatagram(lgsa.toLocal8Bit(),*m_host,m_settings->value("Port").toInt());
        ui->txtState->append(lgsa);
    }
}

void GeoTrans::on_pushButton_clicked()
{
}

void GeoTrans::on_SatUseUpdate(QList<QGeoSatelliteInfo> llist)
{
    *m_inUse = llist;
}

void GeoTrans::on_SatViewUpdate(QList<QGeoSatelliteInfo> llist)
{
    *m_inView = llist;
}
