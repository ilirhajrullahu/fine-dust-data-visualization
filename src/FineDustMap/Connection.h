#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QNetworkAccessManager>
#include "Sensormanager.h"

/**
 * @brief Class to connect with influxDB and write data there
 *
 */
class Connection : public QObject
{

    Q_OBJECT

signals:

private:
    /**
     * Network access manager to connect with the DB.
     */
    QNetworkAccessManager *manager;

public:
    explicit Connection(QObject *parent = nullptr);

    /**
     * @brief Method to persist data in the DB
     * @param id ID of the sensor to be persisted
     * @param type Type of the sensor to be persisted
     * @param lon Longitude coordinate of the sensor to be persisted
     * @param lat Latitude coordinate of the sensor to be persisted
     * @param first P1 if sds sensor, temperature if dht sensor
     * @param second P2 if sds sensor, humidity if dht sensor
     * @param timestamp Date and time of the sensor to be persisted
     */
    void postData(int id, std::string type, double lon, double lat, double first, double second, std::string timestamp);

    /**
     * @brief Execute the query given as String in the parameter and return the request
     * @param query The query (select statement)
     * @return Request for the database
     */
    QNetworkReply* executeQuery(QString query);

    /**
     * @brief Method to unpack reply JSON
     * @param reply Reply as string
     * @return The unpacked value
     */
    double getValueFromReply(QString reply);

    /**
     * @brief Method to get last value in the specific point
     * @param lon Longitude coordinate of the point
     * @param lat Latitude coordinate of the point
     * @param measure P1 or P2
     * @return Last value
     */
    double getLastValue(double lon, double lat, QString measure);

    /**
     * @brief Method to get last P1 value of the sensor
     * @param nr Sensor ID
     * @param measure P1 or P2
     * @return Last P1 value of the sensor
     */
    Q_INVOKABLE double getLastValue(int id, QString measure);

    /**
     * @brief Get average value in the specific point within given timerange
     * @param lon Longitude coordinate of the range
     * @param lat Latitude coordinate of the range
     * @param timeFrom Start time
     * @param timeUntil End time
     * @param measure P1 or P2
     * @return Average value from the specific point and the given timerange
     */
    Q_INVOKABLE double getAverageWithinTimeRange(double lon, double lat, QString timeFrom, QString timeUntil, QString measure);

    /**
     * @brief Backup copy of the DB as CSV files for sensors and each mesure
     * @param startTime Start time, for example: "2020-06-01T00:00:00Z"
     * @param endTime End time, for example: "2020-06-02T00:00:00Z"
     * @param frequency How many records per sensor. Ex.: every hour: "1h", 20 minutes: "20m"
     */
    void backup(QString startTime, QString endTime, QString frequency);

    /**
     * @brief Method to write all Sensors to CSV
     */
    void backupSensors();

    /**
     * @brief Write CSV with all records
     * @param measure Type of the values ("P1" or "P2" or "temperature" or "humidity")
     * @param startTime Start time, for example: "2020-06-01T00:00:00Z"
     * @param endTime End time, for example: "2020-06-02T00:00:00Z"
     * @param frequency How many records per sensor. Ex.: every hour: "1h", 20 minutes: "20m"
     */
    void backupRecords(QString measure, QString startTime, QString endTime, QString frequency);

};

#endif // CONNECTION_H
