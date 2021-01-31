//
// Created by Yaroslav Petrovski on 25.04.2020.
//

#ifndef FINEDUSTDATA_RECORD_H
#define FINEDUSTDATA_RECORD_H

#include <string>
#include <iostream>
#include <qjsonobject.h>

using namespace std;

/**
 * @brief Class to represent the values of a Sensor.
 *
 */
class Record {
private:
    /**
     * The timestamp of the record in string format.
     */
    string timestamp;
    /**
     * The P1 value of the record (P1 if sds Sensor, temperature if dht sensor)
     */
    double firstValue;
    /**
     * The P2 value of the record (P2 if sds sensor, humidity if dht sensor)
     */
    double secondValue;

public:
    /**
     * @brief Constructor for a record object.
     * @param p_timestamp Is the timestamp of the record.
     * @param first P1 if sds sensor, temperature if dht sensor
     * @param second P2 if sds sensor, humidity if dht sensor
     */
    Record(string p_timestamp, double first, double second);

    /**
     * @brief Output the record with its values.
     */
    void showRecordData();

    /**
     * @brief Method to get a Record as a JSON Object.
     * @return Record as JSON Object
     */
    QJsonObject getJSONRecord();

    /**
      * @brief Method to get the P1 or temperature value of the Record.
      * @return P1 or temperature value
      */
    double getFirst() const;

    /**
      * @brief Method to get the P2 or humidity value of the Record.
      * @return P2 or humidity value
      */
    double getSecond() const;

    /**
      * @brief Method to get the timestamp of the record.
      * @return Timestamp as string
      */
    string getTimestamp() const;

    /**
      * @brief Method to set the second value of the record.
      * @param value P2 or humidity
      */
    void setSecondValue(double value);
};


#endif //FINEDUSTDATA_RECORD_H
