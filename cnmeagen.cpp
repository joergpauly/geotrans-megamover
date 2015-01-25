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

}

CNmeaGen::~CNmeaGen()
{

}

QString CNmeaGen::generate(QGeoPositionInfo pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{
    QString lSentence = "$";

    if(m_RMC)
    {
        QString lrmc = makeRMC(&pos, pView, pUse);
        lSentence.append(lrmc);
    }

    if(m_GGA)
    {
        QString lgga = makeGGA(&pos, pView, pUse);
        lSentence.append(lgga);
    }

    if(m_GSA)
    {
        QString lgsa = makeGSA(&pos, pView, pUse);
        lSentence.append(lgsa);
    }
    return lSentence;
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

QString CNmeaGen::makeRMC(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{
    nmeaRMC *pack = new nmeaRMC();
    pack->setDeclination(fabs(pos->attribute(QGeoPositionInfo::MagneticVariation)));
    if(pos->attribute(QGeoPositionInfo::MagneticVariation) < 0)
    {
        pack->setDeclin_ew("W");
    }
    else
    {
        pack->setDeclin_ew("E");
    }
    pack->setDirection(pos->attribute(QGeoPositionInfo::Direction));
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
    pack->setSpeed(pos->attribute(QGeoPositionInfo::GroundSpeed));
    pack->setUtc(pos->timestamp());
    pack->setStatus("A");
    return pack->makeSentence();
}

QString CNmeaGen::makeGGA(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{

}

QString CNmeaGen::makeGSA(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse)
{

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
}

char nmeaGGA::getNs() const
{
    return ns;
}

void nmeaGGA::setNs(char value)
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
}

char nmeaGGA::getEw() const
{
    return ew;
}

void nmeaGGA::setEw(char value)
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

char nmeaGGA::getElv_units() const
{
    return elv_units;
}

void nmeaGGA::setElv_units(char value)
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

char nmeaGGA::getDiff_units() const
{
    return diff_units;
}

void nmeaGGA::setDiff_units(char value)
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
    QString lstr = "GPRMC,";
    lstr.append(this->getUtc().time().toString("HHmmsszz") + "," + this->getStatus() + ",");
    QString lb = QString("%1,%2,%3,%4,")
            .arg(getLon())
            .arg(getEw())
            .arg(getLat())
            .arg(getNs());
    lstr.append(lb);
    lb = QString("%1,%2,%3%4,%5,%6,%7*")
            .arg(getSpeed())
            .arg(getDirection())
            .arg(getUtc().date().toString("ddMMM"))
            .arg(getUtc().date().year() - 100)
            .arg(fabs(getDeclination()))
            .arg(getDeclin_ew())
            .arg(getMode());
    lstr.append(lb);
    int chsum = 0;
    int it;
    QByteArray buff = lstr.toLocal8Bit();

    for(it = 0; it < buff.length(); ++it)
        chsum ^= (int)buff.at(it);
    lb = QString("%1").arg(chsum,2,10);
    lb.append("\n");
    lstr.append(lb);
    return lstr;
}

QDateTime nmeaRMC::getUtc() const
{
    return utc;
}

void nmeaRMC::setUtc(const QDateTime &value)
{
    utc = value;
}
