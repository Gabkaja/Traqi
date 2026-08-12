#include "GPS.h"

#include <TinyGPS++.h>

static TinyGPSPlus gpsParser;

static const int GPS_RX_PIN = 16;
static const int GPS_TX_PIN = 17;

static const uint32_t GPS_BAUD = 9600;


void GPS::begin()
{
    gpsSerial.begin(
        GPS_BAUD,
        SERIAL_8N1,
        GPS_RX_PIN,
        GPS_TX_PIN
    );
}


void GPS::update()
{
    while(gpsSerial.available())
    {
        gpsParser.encode(gpsSerial.read());
    }


    if(gpsParser.location.isValid())
    {
        latitude_ = gpsParser.location.lat();
        longitude_ = gpsParser.location.lng();
    }


    if(gpsParser.speed.isValid())
    {
        speedKmh_ = gpsParser.speed.kmph();
    }


    if(gpsParser.satellites.isValid())
    {
        satellites_ = gpsParser.satellites.value();
    }


    fix_ = gpsParser.location.isValid();
}


bool GPS::hasFix() const
{
    return fix_;
}


double GPS::latitude() const
{
    return latitude_;
}


double GPS::longitude() const
{
    return longitude_;
}


float GPS::speedKmh() const
{
    return speedKmh_;
}


int GPS::satellites() const
{
    return satellites_;
}