//
// Created by Yaroslav Petrovski on 25.04.2020.
//

#ifndef FINEDUSTDATA_SENSOR_H
#define FINEDUSTDATA_SENSOR_H

#include "Record.h"
#include <vector>
#include <qjsonobject.h>
#include <QJsonArray>
#include <QMap>

/**
 * @brief Class to represent a specific Sensor.
 *
 */
class Sensor {
private:
    /**
     * The ID of the sensor.
     */
    int sensor_id;
    /**
     * The type of the sensor.
     */
    string sensor_type;
    /**
     * The latitude coordinate of the sensor.
     */
    double latitude;
    /**
     * The longitude coordinate of the sensor.
     */
    double longitude;
    /**
     * The records of the sensor. Key is the timestamp and the value is the record itself.
     */
    QMap<string, Record> records;

    /**
     * @brief Method to split the row
     * @param row The whole line to be split
     * @param delim Delimiter to be used for the split
     * @return vector of strings/separated values
     */
    vector<string> splitRawString(string raw, const char delim);
    /**
     * @brief Method to get time in influxDB format
     * @param timeFromCsv Time value from CSV-row
     * @return Timestamp for influxDB
     */
    string reformatTime(string timeFromCsv);

public:
    /**
     * @brief Constructor for the sensor object.
     * @param p_sensor_id Is the sensor ID.
     * @param p_sensor_type Is the type of the sensor.
     * @param p_latitude Is the latitude coordinate of the sensor.
     * @param p_longitude Is the longitude coordinate of the sensor.
     *
     */
    Sensor(int p_sensor_id, string p_sensor_type, double p_latitude, double p_longitude);
    /**
     * @brief Constructor with a given file from which it creates the objects.
     * @param filepath Is the path to the file.
     */
    Sensor(string filePath);

    /**
     * @brief Read Sensor attributes from a CSV-file
     * @param filename Is the path to the file
     * @return True if data ok, false if wrong sensortype or wrong area
     */
    bool readSensorData(string fileName);

    /**
     * @brief Read all records from CSV file and write them into DB
     * @param filanem Is the path to the file.
     */
    void readAndExportRecordData(string fileName);

    /**
     * @brief Output of the records of the sensor.
     */
    void showData();

    /**
     * @brief Method to write Sensor data in the database
     */
    void exportDataToDatabase();

    /**
     * @brief Method to add a add new record to the sensor.
     * @param timestamp Time of the record
     * @param firstValue P1 or temperature (put -1 when secondValue only)
     * @param secondValue P2 or humidity (put -1 when firstValue only)
     */
    void addRecord(string timestamp, double firstValue, double secondValue);

    /**
     * @brief Method to return sensor as string.
     * @return One string with the data of the sensor, separated by ';'
     */
    std::string dataAsString();

    /**
     * @brief Method to return the sensor ID.
     * @return Sensor ID
     */
    int getSensor_id() const;

    /**
     * @brief Method to get last value of the sensor depending on the given value.
     * @param measure "P1" or "P2" or "temperature" or "humidity"
     * @return Last value of the sensor.
     */
    double getLast(QString measure);

    /**
     * @brief Method to get the average value of a Sensor in a given period.
     * @param timeFrom Start time of the period
     * @param timeUntil End time of the period
     * @param measure "P1" or "P2", "temperature" or "humidity"
     * @return The average value, but return -9999 when not valid parameters
     */
    double getAverage(QString timeFrom, QString timeUntil, QString measure);

    /**
     * @brief operator == equal if position+type are the same or if the same id
     * @param other Second sensor to be compared with
     * @return true if equal, otherwise return false
     */
    bool operator==(const Sensor & other) const;

    /**
     * @brief Method to get the latitude coordinate of the sensor.
     * @return the latitude coordinate of the sensor
     */
    double getLatitude() const;
    /**
     * @brief Method to get the longitude coordinate of the sensor.
     * @return the longitude coordinate of the sensor.
     */
    double getLongitude() const;
    /**
     * @brief Method to get the type of the sensor.
     * @return the sensor type.
     */
    string getSensor_type() const;
};


#endif //FINEDUSTDATA_SENSOR_H
