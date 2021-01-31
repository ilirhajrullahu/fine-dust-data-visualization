//
// Created by Yaroslav Petrovski on 25.04.2020.
//

#include "Record.h"


string Record::getTimestamp() const
{
    return timestamp;
}

void Record::setSecondValue(double value)
{
    secondValue = value;
}

Record::Record(string p_timestamp, double first, double second) {
    this->timestamp = p_timestamp;
    this->firstValue = first;
    this->secondValue = second;
}

void Record::showRecordData() {
    cout << this->timestamp << " " << this->firstValue << " " << this->secondValue << " " << endl;
}

QJsonObject Record::getJSONRecord(){
    QJsonObject json_record;

    QString temp = QString::fromStdString(this->timestamp);
    json_record["record_timestamp"] = temp;
    json_record["record_p1"] = this->firstValue;
    json_record["record_p2"] = this->secondValue;

    return json_record;
}

double Record::getFirst() const
{
    return firstValue;
}

double Record::getSecond() const
{
    return secondValue;
}
