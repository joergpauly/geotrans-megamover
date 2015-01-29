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

#ifndef CNMEAGEN_H
#define CNMEAGEN_H

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <QString>
#include <QDateTime>
#include <QGeoPositionInfo>
#include <QGeoSatelliteInfo>

class CNmeaGen
{
public:
    CNmeaGen();
    ~CNmeaGen();
    void generate(QGeoPositionInfo pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse);

    bool RMC() const;
    void setRMC(bool RMC);

    bool GGA() const;
    void setGGA(bool GGA);

    bool GSA() const;
    void setGSA(bool GSA);

    QString sRMC() const;
    void setSRMC(const QString &sRMC);

    QString sGGA() const;
    void setSGGA(const QString &sGGA);

    QString sGSA() const;
    void setSGSA(const QString &sGSA);

private: //Members
    bool m_RMC;
    bool m_GGA;
    bool m_GSA;
    QString m_sRMC;
    QString m_sGGA;
    QString m_sGSA;

private: //Functions
    QString makeRMC(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse);
    QString makeGGA(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse);
    QString makeGSA(QGeoPositionInfo *pos, QList<QGeoSatelliteInfo> *pView, QList<QGeoSatelliteInfo> *pUse);

};


/*************************************************************************************************
 *
 * Helper-Classes
 *
 * ************************************************************************************************/

class nmeaGGA
{
     QDateTime  utc;        /**< UTC of position (just time) */
     double     lat;        /**< Latitude in NDEG - [degree][min].[sec/60] */
     QString    s_lat;
     QString    ns;         /**< [N]orth or [S]outh */
     double     lon;        /**< Longitude in NDEG - [degree][min].[sec/60] */
     QString    s_lon;
     QString    ew;         /**< [E]ast or [W]est */
     int        sig;        /**< GPS quality indicator (0 = Invalid; 1 = Fix; 2 = Differential, 3 = Sensitive) */
     int        satinuse;   /**< Number of satellites in use (not those in view) */
     double     HDOP;       /**< Horizontal dilution of precision */
     double     elv;        /**< Antenna altitude above/below mean sea level (geoid) */
     QString    elv_units;  /**< [M]eters (Antenna height unit) */
     double     diff;       /**< Geoidal separation (Diff. between WGS-84 earth ellipsoid and mean sea level. '-' = geoid is below WGS-84 ellipsoid) */
     QString    diff_units; /**< [M]eters (Units of geoidal separation) */
     double     dgps_age;   /**< Time in seconds since last DGPS update */
     int        dgps_sid;   /**< DGPS station ID number */

public:
     QDateTime getUtc() const;
     void setUtc(const QDateTime &value);
     double getLat() const;
     void setLat(double value);
     QString getNs() const;
     void setNs(QString value);
     double getLon() const;
     void setLon(double value);
     QString getEw() const;
     void setEw(QString value);
     int getSig() const;
     void setSig(int value);
     int getSatinuse() const;
     void setSatinuse(int value);
     double getHDOP() const;
     void setHDOP(double value);
     double getElv() const;
     void setElv(double value);
     QString getElv_units() const;
     void setElv_units(QString value);
     double getDiff() const;
     void setDiff(double value);
     QString getDiff_units() const;
     void setDiff_units(QString value);
     double getDgps_age() const;
     void setDgps_age(double value);
     QString makeSentence();
     QString getS_lat() const;
     void setS_lat(const QString &value);
     QString getS_lon() const;
     void setS_lon(const QString &value);
};




class nmeaGSA
{
    QString         fix_mode;   /**< Mode (M = Manual, forced to operate in 2D or 3D; A = Automatic, 3D/2D) */
    int             fix_type;   /**< Type, used for navigation (1 = Fix not available; 2 = 2D; 3 = 3D) */
    QList<int>      sat_prn;    /**< PRNs of satellites used in position fix (null for unused fields) */
    double          PDOP;       /**< Dilution of precision */
    double          HDOP;       /**< Horizontal dilution of precision */
    double          VDOP;       /**< Vertical dilution of precision */

public:
    QString getFix_mode() const;
    void setFix_mode(const QString &value);
    int getFix_type() const;
    void setFix_type(int value);
    double getPDOP() const;
    void setPDOP(double value);
    double getHDOP() const;
    void setHDOP(double value);
    double getVDOP() const;
    void setVDOP(double value);
    QString makeSentence();
    QList<int> getSat_prn() const;
    void setSat_prn(const QList<int> &value);
};


class nmeaRMC
{
    QDateTime  utc;       /**< UTC of position */
    QString    status;     /**< Status (A = active or V = void) */
     double     lat;        /**< Latitude in NDEG - [degree][min].[sec/60] */
     QString    s_lat;
     QString    ns;         /**< [N]orth or [S]outh */
     double     lon;        /**< Longitude in NDEG - [degree][min].[sec/60] */
     QString    s_lon;
     QString    ew;         /**< [E]ast or [W]est */
     double     speed;      /**< Speed over the ground in knots */
     double     direction;  /**< Track angle in degrees True */
     double     declination; /**< Magnetic variation degrees (Easterly var. subtracts from true course) */
     QString    declin_ew;  /**< [E]ast or [W]est */
     QString    mode;       /**< Mode indicator of fix type (A = autonomous, D = differential, E = estimated, N = not valid, S = simulator) */

public:
     QDateTime getUtc() const;
     void setUtc(const QDateTime &value);
     QString getStatus() const;
     void setStatus(const QString &value);
     double getLat() const;
     void setLat(double value);
     QString getNs() const;
     void setNs(const QString &value);
     double getLon() const;
     void setLon(double value);
     QString getEw() const;
     void setEw(const QString &value);
     double getSpeed() const;
     void setSpeed(double value);
     double getDirection() const;
     void setDirection(double value);
     double getDeclination() const;
     void setDeclination(double value);
     QString getDeclin_ew() const;
     void setDeclin_ew(const QString &value);
     QString getMode() const;
     void setMode(const QString &value);
     QString makeSentence();
     QString getS_lat() const;
     void setS_lat(const QString &value);
     QString getS_lon() const;
     void setS_lon(const QString &value);
};

#endif // CNMEAGEN_H
