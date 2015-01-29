/***************************************************************************************
*
*   This file is part of the MEGA-Series Project.
*   Copyright (C) 2015 Joerg Pauly
*   Created 25.01.2015 by joerg
*   All Rights reserved
*
*   Alle Programme der MEGA-Serie sind Freie Software: Sie können sie unter den
*   Bedingungen der GNU Lesser General Public License (LGPL), wie von der
*   Free Software Foundation, Version 3 der Lizenz oder (nach Ihrer Option)
*   jeder späteren veröffentlichten Version, weiterverbreiten und/oder
*   modifizieren.
*
*   Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
*   OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
*   Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
*   Siehe die GNU Lesser General Public License für weitere Details.
*
*   Sie sollten eine Kopie der GNU Lesser General Public License zusammen mit diesem
*   Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*
*   All programs of the MEGA-series are Free Software: You can distribute and/or modify
*   them under the terms of the GNU Lesser General Public License (LGPL), as published
*   by the Free Software Foundation, version 3 or (your option) any later published
*   version.
*
*   This program is provided in the hope that it will be usefull, but WITHOUT ANY
*   WARRANTY; even without the implicit warrant of COMMERCIAL BENEFIT or ABILITY FOR A
*   DEFINED UNSAGE.
*   See GNU Lesser General Public License for more details.
*
*   You should have obtained a copy of the GNU Lesser General Public License with this
*   software. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************************/

#include "cnmeagen.h"

CNmeaGen::CNmeaGen()
{
    m_sRMC = "";
    m_sGGA = "";
    m_sGSA = "";
}

CNmeaGen::~CNmeaGen()
{

}

void CNmeaGen::generate(QGeoPositionInfo pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{    
    if(m_RMC)
    {
        setSRMC(makeRMC(&pos, pView, pUse));
    }

    if(m_GGA)
    {
        setSGGA(makeGGA(&pos, pView, pUse));
    }

    if(m_GSA)
    {
        setSGSA(makeGSA(&pos, pView, pUse));
    }    
}

bool CNmeaGen::RMC() const
{
    return m_RMC;
}

void CNmeaGen::setRMC(bool RMC)
{
    m_RMC = RMC;
}

bool CNmeaGen::GGA() const
{
    return m_GGA;
}

void CNmeaGen::setGGA(bool GGA)
{
    m_GGA = GGA;
}

bool CNmeaGen::GSA() const
{
    return m_GSA;
}

void CNmeaGen::setGSA(bool GSA)
{
    m_GSA = GSA;
}
QString CNmeaGen::sRMC() const
{
    return m_sRMC;
}

void CNmeaGen::setSRMC(const QString &sRMC)
{
    m_sRMC = sRMC;
}

QString CNmeaGen::sGGA() const
{
    return m_sGGA;
}

void CNmeaGen::setSGGA(const QString &sGGA)
{
    m_sGGA = sGGA;
}

QString CNmeaGen::sGSA() const
{
    return m_sGSA;
}

void CNmeaGen::setSGSA(const QString &sGSA)
{
    m_sGSA = sGSA;
}




QString CNmeaGen::makeRMC(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{
    nmeaRMC *pack = new nmeaRMC();
    if(pos->hasAttribute(QGeoPositionInfo::Attribute::MagneticVariation))
    {
        pack->setDeclination(fabs(pos->attribute(QGeoPositionInfo::Attribute::MagneticVariation)));
        if(pos->attribute(QGeoPositionInfo::Attribute::MagneticVariation) < 0)
        {
            pack->setDeclin_ew("W");
        }
        else
        {
            pack->setDeclin_ew("E");
        }
    }
    else
    {
        pack->setDeclination(0);
        pack->setDeclin_ew("");
    }
    if(pos->hasAttribute(QGeoPositionInfo::Attribute::Direction))
    {
        pack->setDirection(pos->attribute(QGeoPositionInfo::Attribute::Direction));
    }
    else
    {
        pack->setDirection(0);
    }
    if(pos->coordinate().longitude() < 0)
    {
        pack->setEw("W");
    }
    else
    {
        pack->setEw("E");
    }
    pack->setLon(fabs(pos->coordinate().longitude()));
    if(pos->coordinate().latitude() < 0)
    {
        pack->setNs("S");
    }
    else
    {
        pack->setNs("N");
    }
    pack->setLat(fabs(pos->coordinate().latitude()));
    pack->setMode("A");
    if(pos->hasAttribute(QGeoPositionInfo::Attribute::GroundSpeed))
    {
        pack->setSpeed(pos->attribute(QGeoPositionInfo::Attribute::GroundSpeed));
    }
    pack->setUtc(pos->timestamp());
    pack->setStatus("A");
    return pack->makeSentence();
}

QString CNmeaGen::makeGGA(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{
    nmeaGGA *pack = new nmeaGGA();
    pack->setDgps_age(0);
    pack->setDiff(0);
    pack->setDiff_units("");
    pack->setElv(pos->coordinate().altitude());
    pack->setElv_units("M");
    if(pos->hasAttribute(QGeoPositionInfo::Attribute::HorizontalAccuracy))
    {
        pack->setHDOP(pos->attribute(QGeoPositionInfo::Attribute::HorizontalAccuracy));
    }
    else
    {
        pack->setHDOP(0);
    }
    pack->setLat(fabs(pos->coordinate().latitude()));
    if(pos->coordinate().latitude() < 0)
    {
        pack->setNs("S");
    }
    else
    {
        pack->setNs("N");
    }
    pack->setLon(fabs(pos->coordinate().longitude()));
    if(pos->coordinate().longitude() < 0)
    {
        pack->setEw("W");
    }
    else
    {
        pack->setEw("E");
    }
    pack->setUtc(pos->timestamp());
    pack->setSatinuse(pUse->count());
    pack->setSig(pos->coordinate().type());
    return pack->makeSentence();
}

QString CNmeaGen::makeGSA(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{
    nmeaGSA *pack = new nmeaGSA();
    pack->setFix_mode("A");
    if(pos->hasAttribute(QGeoPositionInfo::Attribute::HorizontalAccuracy))
    {
        pack->setHDOP(pos->attribute(QGeoPositionInfo::Attribute::HorizontalAccuracy));
    }
    else
    {
        pack->setHDOP(0);
    }
    pack->setFix_type(pos->coordinate().type());
    if(pos->hasAttribute(QGeoPositionInfo::Attribute::VerticalAccuracy))
    {
        pack->setVDOP(pos->attribute(QGeoPositionInfo::Attribute::VerticalAccuracy));
    }
    else
    {
        pack->setVDOP(0);
    }
    pack->setPDOP(pack->getHDOP()+pack->getVDOP());
    QList<int> satlst;
    for(int cnt = 0; cnt < pUse->count(); cnt++)
    {
        satlst.append(pUse->at(cnt).satelliteIdentifier());
    }
    pack->setSat_prn(satlst);
    return pack->makeSentence();
}




/****************************************************************************
 * Functions for $GPGGA
 * **************************************************************************/

double nmeaGGA::getLat() const
{
    return lat;
}

void nmeaGGA::setLat(double value)
{
    lat = value;
    int deg = value;
    double min = (value - deg)*.6;

    s_lat = "";
    if(deg < 10)
    {
        s_lat = "0";
    }
    s_lat.append("%1").arg(deg);
    if(min < 10)
    {
        s_lat.append("0%1").arg(min);
    }
    else
    {
        s_lat.append("%1").arg(min);
    }
}

QString nmeaGGA::getNs() const
{
    return ns;
}

void nmeaGGA::setNs(QString value)
{
    ns = value;
}

double nmeaGGA::getLon() const
{
    return lon;
}

void nmeaGGA::setLon(double value)
{
    lon = value;
    int deg = value;
    double min = (value - deg)*.6;

    s_lon = "";
    if(deg < 100)
    {
        s_lon = "0";
    }
    if(deg < 10)
    {
        s_lon = "00";
    }
    s_lon.append("%1").arg(deg);
    if(min < 10)
    {
        s_lon.append("0%1").arg(min);
    }
    else
    {
        s_lon.append("%1").arg(min);
    }
}

QString nmeaGGA::getEw() const
{
    return ew;
}

void nmeaGGA::setEw(QString value)
{
    ew = value;
}

int nmeaGGA::getSig() const
{
    return sig;
}

void nmeaGGA::setSig(int value)
{
    sig = value;
}

int nmeaGGA::getSatinuse() const
{
    return satinuse;
}

void nmeaGGA::setSatinuse(int value)
{
    satinuse = value;
}

double nmeaGGA::getHDOP() const
{
    return HDOP;
}

void nmeaGGA::setHDOP(double value)
{
    HDOP = value;
}

double nmeaGGA::getElv() const
{
    return elv;
}

void nmeaGGA::setElv(double value)
{
    elv = value;
}

QString nmeaGGA::getElv_units() const
{
    return elv_units;
}

void nmeaGGA::setElv_units(QString value)
{
    elv_units = value;
}

double nmeaGGA::getDiff() const
{
    return diff;
}

void nmeaGGA::setDiff(double value)
{
    diff = value;
}

QString nmeaGGA::getDiff_units() const
{
    return diff_units;
}

void nmeaGGA::setDiff_units(QString value)
{
    diff_units = value;
}

double nmeaGGA::getDgps_age() const
{
    return dgps_age;
}

void nmeaGGA::setDgps_age(double value)
{
    dgps_age = value;
}

QString nmeaGGA::makeSentence()
{
    QString lstr = "GPGAA,";
    lstr.append(getUtc().time().toString("hhmmss") + ".00,");
    QString llat = getS_lat();
    QString llon = getS_lon();

    QString lb = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,,,,*")
            .arg(llat)
            .arg(getNs())
            .arg(llon)
            .arg(getEw())
            .arg(getSig())
            .arg(getSatinuse())
            .arg(getHDOP())
            .arg(getElv())
            .arg(getElv_units());
    lstr.append(lb);
    int chsum = 0;
    int it;
    QByteArray buff = lstr.toLocal8Bit();

    for(it = 0; it < buff.length(); ++it)
        chsum ^= (int)buff.at(it);
    lb = QString("%1")
            .arg(chsum,0,16);
    if(lb.length() == 1)
    {
        lb = "0" + lb;
    }
    lb = lb.toUpper();
    lstr.append(lb);
    lstr = "$" + lstr;
    return lstr;
}


QString nmeaGGA::getS_lat() const
{
    return s_lat;
}

void nmeaGGA::setS_lat(const QString &value)
{
    s_lat = value;
}

QString nmeaGGA::getS_lon() const
{
    return s_lon;
}

void nmeaGGA::setS_lon(const QString &value)
{
    s_lon = value;
}
QDateTime nmeaGGA::getUtc() const
{
    return utc;
}

void nmeaGGA::setUtc(const QDateTime &value)
{
    utc = value;
}


/****************************************************************************
 * Functions for $GPGSA
 * **************************************************************************/


int nmeaGSA::getFix_type() const
{
    return fix_type;
}

void nmeaGSA::setFix_type(int value)
{
    fix_type = value;
}

double nmeaGSA::getPDOP() const
{
    return PDOP;
}

void nmeaGSA::setPDOP(double value)
{
    PDOP = value;
}

double nmeaGSA::getHDOP() const
{
    return HDOP;
}

void nmeaGSA::setHDOP(double value)
{
    HDOP = value;
}

double nmeaGSA::getVDOP() const
{
    return VDOP;
}

void nmeaGSA::setVDOP(double value)
{
    VDOP = value;
}

QString nmeaGSA::makeSentence()
{
    QString lgsa = "GPGSA,";
    QString lb;
    lgsa.append(getFix_mode() + ",");
    lgsa.append("3,");
    int cnt;
    QList<int> satlst = getSat_prn();
    for(cnt = 0; cnt < satlst.count(); cnt++)
    {
        QString satid = QString("%1,").arg(satlst.at(cnt));
        lgsa.append(satid);
    }
    for(cnt = 0; cnt < (12 - satlst.count()); cnt++)
    {
        lgsa.append(",");
    }
    if(getPDOP() > 0)
    {
        lb = QString("%1,").arg(getPDOP());
        lgsa.append(lb);
    }
    else
    {
        lgsa.append(",");
    }

    if(getHDOP() > 0)
    {
        lb = QString("%1,").arg(getHDOP());
        lgsa.append(lb);
    }
    else
    {
        lgsa.append(",");
    }

    if(getVDOP() > 0)
    {
        lb = QString("%1").arg(getVDOP());
        lgsa.append(lb);
    }


    int chsum = 0;
    int it;
    QByteArray buff = lgsa.toLocal8Bit();

    for(it = 0; it < buff.length(); ++it)
        chsum ^= (int)buff.at(it);
    lb = QString("*%1")
            .arg(chsum,0,16);
    if(lb.length() == 1)
    {
        lb = "0" + lb;
    }
    lb = lb.toUpper();
    lgsa.append(lb);
    lgsa = "$" + lgsa;
    return lgsa;
}


QList<int> nmeaGSA::getSat_prn() const
{
    return sat_prn;
}

void nmeaGSA::setSat_prn(const QList<int> &value)
{
    sat_prn = value;
}

QString nmeaGSA::getFix_mode() const
{
    return fix_mode;
}

void nmeaGSA::setFix_mode(const QString &value)
{
    fix_mode = value;
}


/****************************************************************************
 * Functions for $GPRMC
 * **************************************************************************/


QString nmeaRMC::getStatus() const
{
    return status;
}

void nmeaRMC::setStatus(const QString &value)
{
    status = value;
}

double nmeaRMC::getLat() const
{
    return lat;
}

void nmeaRMC::setLat(double value)
{
    lat = value;
    int deg = value;
    double min = (value - deg)*.6;

    s_lat = "";
    if(deg < 10)
    {
        s_lat = "0";
    }
    s_lat.append(QString("%1").arg(deg));
    if(min < 10)
    {
        s_lat.append(QString("0%1").arg(min));
    }
    else
    {
        s_lat.append(QString("%1").arg(min));
    }
}

QString nmeaRMC::getNs() const
{
    return ns;
}

void nmeaRMC::setNs(const QString &value)
{
    ns = value;
}

double nmeaRMC::getLon() const
{
    return lon;
}

void nmeaRMC::setLon(double value)
{
    lon = value;
    int deg = value;
    double min = (value - deg)*.6;

    s_lon = "";
    if(deg < 100)
    {
        s_lon = "0";
    }
    if(deg < 10)
    {
        s_lon = "00";
    }
    s_lon.append(QString("%1").arg(deg));
    if(min < 10)
    {
        s_lon.append(QString("0%1").arg(min));
    }
    else
    {
        s_lon.append(QString("%1").arg(min));
    }
}

QString nmeaRMC::getEw() const
{
    return ew;
}

void nmeaRMC::setEw(const QString &value)
{
    ew = value;
}

double nmeaRMC::getSpeed() const
{
    return speed;
}

void nmeaRMC::setSpeed(double value)
{
    speed = value;
}

double nmeaRMC::getDirection() const
{
    return direction;
}

void nmeaRMC::setDirection(double value)
{
    direction = value;
}

double nmeaRMC::getDeclination() const
{
    return declination;
}

void nmeaRMC::setDeclination(double value)
{
    declination = value;
}

QString nmeaRMC::getDeclin_ew() const
{
    return declin_ew;
}

void nmeaRMC::setDeclin_ew(const QString &value)
{
    declin_ew = value;
}

QString nmeaRMC::getMode() const
{
    return mode;
}

void nmeaRMC::setMode(const QString &value)
{
    mode = value;
}

QString nmeaRMC::makeSentence()
{
    /* $GPRMC,
    UTC     HHMMSS.00,
    Staus   A,
    Lat     DDMM.XXXX,
    LtHm    N,
    Lon     DDDMM.XXXX,
    LnHm    E,
    Speed   0,
    Hdg     000,
    Date    DDMMYY,
    Var     o.oo,
    VarHm   E
    ChkSm   *XX
    */
    QString lstr = "GPRMC,";
    lstr.append(this->getUtc().time().toString("HHmmss") + ".00," + this->getStatus() + ",");
    QString llat = getS_lat();
    QString llon = getS_lon();

    QString lb = QString("%1,%2,%3,%4,")            
            .arg(llat)
            .arg(getNs())
            .arg(llon)
            .arg(getEw());
    lstr.append(lb);
    lb = QString("%1,%2,%3,")
            .arg(getSpeed())
            .arg(getDirection())
            .arg(getUtc().date().toString("ddMMyy"));
    lstr.append(lb);
    lb = QString("0,E,");
    lstr.append(lb);
    int chsum = 0;
    int it;
    QByteArray buff = lstr.toLocal8Bit();

    for(it = 0; it < buff.length(); ++it)
        chsum ^= (int)buff.at(it);
    lb = QString("A*%1")
            .arg(chsum,0,16);
    if(lb.length() == 1)
    {
        lb = "0" + lb;
    }
    lb = lb.toUpper();
    lstr.append(lb);
    lstr = "$" + lstr;
    return lstr;
}


QString nmeaRMC::getS_lat() const
{
    return s_lat;
}

void nmeaRMC::setS_lat(const QString &value)
{
    s_lat = value;
}

QString nmeaRMC::getS_lon() const
{
    return s_lon;
}

void nmeaRMC::setS_lon(const QString &value)
{
    s_lon = value;
}
QDateTime nmeaRMC::getUtc() const
{
    return utc;
}

void nmeaRMC::setUtc(const QDateTime &value)
{
    utc = value;
}
