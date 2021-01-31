#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <QMap>
#include <QList>
#include <QObject>
#include <QGeoCoordinate>
#include <QGeoRectangle>
#include <QGeoLocation>
#include "Hexagon.h"
#include "Sensor.h"


/**
 * @brief Class to manage Sensors and perform calculations for the frontend.
 *
 */
class SensorManager : public QObject
{
    Q_OBJECT

private:
    /**
     * The container for all the sensors. Key is the sensor ID and the value is the sensor itself.
     */
    QMap<int, Sensor> sensors;
    /**
     * The last computed city rectangle.
     */
    QGeoRectangle tmpRectangle;
    /**
     * The last searched city.
     */
    QString lastCity;
    /**
     * The last searched measurement.
     */
    QString lastMeasure;
    /**
     * The list to temporarily store the IDs of the sensors.
     */
    QList<int> sensorsList;

public:
    /**
     * @brief Constructor of the SensorManager object.
     * @param parent Is the default QObject parameter that won
     */
    explicit SensorManager(QObject *parent = nullptr);

    /**
     * @brief Load all CSV in the directory to the DB
     * @param pathToDir Path to the directory
     */
    void LoadDataFromDirectoryToDB(std::string pathToDir);

    /**
     * @brief Add sensor to the sensors collection
     * @param s Sensor to be added.
     */
    void addSensor(Sensor s);

    /**
     * @brief Add record to a sensor.
     * @param id Id of the sensor
     * @param timestamp Date and time of the record.
     * @param firstValue P1 value of the record.
     * @param secondValue P2 value of the record.
     */
    void addRecordToSensor(int id, string timestamp, double firstValue, double secondValue);

    /**
     * @brief Read backup copies to use instead of the DB.
     */
    void recordDatafromBackup();

    /**
     * @brief Read specific file
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     */
    void readBackupFile(QString measure);

    /**
     * @brief Method to get ID of the sensor on the position
     * @param lon Longitude coordinate of the position
     * @param lat Latitude coordinate of the position
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @return sensor-ID
     */
    int getSensorIdOnPosition(double lon, double lat, QString measure);

    /**
     * @brief Method to get last value of the sensor with the specific id
     * @param id sensor-ID
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @return Last value
     */
    double getLast(int id, QString measure);

    /**
     * @brief Method to get average value of the sensor in the given timeperiod
     * @param id Sensor-ID
     * @param timeFrom Start time of the period
     * @param timeUntil End time of the period
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @return Average value
     */
    double getAverage(int id, QString timeFrom, QString timeUntil, QString measure);

    /**
     * @brief Method to get last value of the sensor at the specific location
     * @param lon Longitude coordinate of the location
     * @param lat Latidude coordinate of the location
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @return last value
     */
    double getLast(double lon, double lat, QString measure);

    /**
     * @brief Method to get average value of the sensor in the timeperiod
     * @param lon Longitude coordinate of the sensor
     * @param lat Latitude coordinate of the sensor
     * @param timeFrom start time
     * @param timeUntil end time
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @return average value
     */
    double getAverage(double lon, double lat, QString timeFrom, QString timeUntil, QString measure);

    /**
     * @brief Method to find sensors inside the city rectangle and temporarily store them
     * @param cityName the name of the city in Germany
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     */
    void findSensorsInCity(QString cityName, QString measure);

    /**
     * @brief Method to get average value in the city during the timeperiod
     * @param cityName the name of the city in Germany
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @param timeFrom start time
     * @param timeUntil end time
     * @return average value
     */
    Q_INVOKABLE double avgCityValue(QString cityName, QString measure, QString timeFrom, QString timeUntil);

    /**
     * @brief Method to get location of the city
     * @param cityName the name of the city in Germany
     * @return location
     */
    Q_INVOKABLE QGeoLocation getLocation(QString cityName);

    /**
     * @brief Method to get rectangle that includes the city
     * @param cityName the name of the city in Germany
     * @return georectangle with ONLY topLeft and bottomRight set
     */
    Q_INVOKABLE QGeoRectangle getCityRectangle(QString cityName);

    /**
     * @brief Method to get coordinates of the point in the city center
     * @param cityName the name of the city in Germany
     * @return Coordinates of the pint
     */
    Q_INVOKABLE QGeoCoordinate getCityCenter(QString cityName);

    /**
      * @brief Method to get average temperature or other value of sensors inside a polygon
      * @param polyY Y coordinates of the polygon
      * @param polyX X coordinates of the polygon
      * @param dataValue the value of the sensor (temperature or fine dust)
      * @return Average value (temperature, fine dust) inside given polygon
      */
    Q_INVOKABLE double getAveragePolygonValue(double polyY[6], double polyX[6], QString dataValue);

    /**
     * @brief Method to prove if a point is located inside a polygon/hexagon.
     * @param polyY Is the array with Y coordinates of the polygon.
     * @param polyX Is the array with X coordinates of the polygon.
     * @param polyCorners Is the amount of corners of the polygon (we use 6 corners per default).
     * @param y Is the y coordinate of the point.
     * @param x Is the x coordinate of the point.
     * @return True if the point is in the polygon, false if not.
     */
    bool pointInPolygon(double polyY[6], double polyX[6], double y, double x);


};

#endif // SENSORMANAGER_H
