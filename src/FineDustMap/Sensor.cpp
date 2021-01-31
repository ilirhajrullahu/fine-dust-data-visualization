//
// Created by Yaroslav Petrovski on 25.04.2020.
//

#include <vector>
#include <sstream>
#include <fstream>
#include <locale> //for parsing time
#include <iomanip> //for parsing time
#include <stdio.h> //to delete files
#include "Connection.h"
#include "Sensor.h"


Sensor::Sensor(int p_sensor_id, string p_sensor_type, double p_latitude, double p_longitude) {
    this->sensor_id = p_sensor_id;
    this->sensor_type = p_sensor_type;
    //this->location = p_location;
    this->latitude = p_latitude;
    this->longitude = p_longitude;
}

Sensor::Sensor(string filePath) {
    if (readSensorData(filePath)){
        readAndExportRecordData(filePath);
    }
}

int Sensor::getSensor_id() const
{
    return sensor_id;
}

double Sensor::getLatitude() const
{
    return latitude;
}

double Sensor::getLongitude() const
{
    return longitude;
}

string Sensor::getSensor_type() const
{
    return sensor_type;
}

vector<string> Sensor::splitRawString(string raw, const char delim){
    vector<string> elements;
    stringstream ss(raw);
    string element;
    while (getline(ss, element, delim)) {
        if (element.length() > 0) {
            elements.push_back(element);
        } else {
            elements.push_back("0");
        }
    }
    return elements;
}

string Sensor::reformatTime(string timeFromCsv){
    std::tm t = {};
    std::istringstream ss(timeFromCsv);

    if (ss >> std::get_time(&t,"%Y-%m-%dT%H:%M:%S"))
    {
        std::stringstream timess;
        timess << std::mktime(&t);
        std::string timestring = timess.str().append("000000000");
        //std::cout << timestring << std::endl;
        return timestring;
    }
    else
    {
        std::cout << "Parse date failed\n";
        return "0";
    }
}

bool checkIfPointInDarmstadtArea(double lat, double lon){
    if(lat<50.327929664466275
            && lat>49.42169406084926
            && lon<9.3109130859375
            && lon>7.943115234375001){
        return true;
    }
    return false;
}

bool Sensor::readSensorData(string fileName) {
    ifstream fin;
    string line;
    // Open an existing file
    fin.open(fileName, ifstream::in);
    getline(fin, line); //ignore first line
    getline(fin, line); //get first line
    vector<string> raw = this->splitRawString(line, ';');
    this->sensor_id = std::stoi(raw[0]);
    this->sensor_type = raw[1];
    //this->location = std::stoi(raw[2]);
    this->latitude = std::stod(raw[3]);
    this->longitude = std::stod(raw[4]);
    fin.close();
    /*if (!(checkIfPointInDarmstadtArea(latitude, longitude))){
        //remove(fileName.c_str()); //delete file from directory
        qDebug() << "Ignore file. Wrong area";
        return false;
    }*/
    if (sensor_type != "DHT22" && sensor_type != "SDS011" && sensor_type != "PPD42NS"){
        //remove(fileName.c_str()); //delete file from directory
        qDebug() << "Ignore file. Wrong sensor";
        return false;
    }
    return true;
}

void Sensor::readAndExportRecordData(string fileName) {
    ifstream fin;
    string line;
    // Open an existing file
    fin.open(fileName, ifstream::in);
    getline(fin, line); //ignore first line

    Connection c;

    qDebug() << "STARTED writing data into DB";

    while (getline(fin, line)) {
        vector<string> raw = splitRawString(line, ';');
        string timestamp = this->reformatTime(raw[5]);
        if (sensor_type == "SDS011" || sensor_type == "PPD42NS") {
            double p_p1 = std::stod(raw[6]);
            double p_p2 = std::stod(raw[9]);
            c.postData(this->sensor_id, this->sensor_type,
                       this->longitude, this->latitude, p_p1, p_p2, timestamp);
        }
        else { //DHT22
            double temerature = std::stod(raw[6]);
            double humidity = std::stod(raw[7]);
            c.postData(this->sensor_id, this->sensor_type,
                       this->longitude, this->latitude, temerature, humidity, timestamp);
        }

    }
    fin.close();

    qDebug() << "STOPPED writing data into DB";
}

void Sensor::exportDataToDatabase(){
    Connection c;
    for (auto record : this->records) {
        c.postData(this->sensor_id, this->sensor_type, this->longitude, this->latitude,
                   record.getFirst(), record.getSecond(), record.getTimestamp());
    }
}

void Sensor::showData() {
    for (auto record : this->records) {
        cout << this-> sensor_type << " " << this->latitude << " " << this->longitude << " ";
        record.showRecordData();
    }
}

void Sensor::addRecord(string timestamp, double firstValue, double secondValue){
    //If firstValue==-1 only secondValue has to be set
    if (firstValue == -1){
        records.find(timestamp)->setSecondValue(secondValue);
    }
    else {
        Record rec(timestamp, firstValue, secondValue);
        records.insert(timestamp, rec);
    }

}

std::string Sensor::dataAsString(){
    return to_string(sensor_id)+";"+sensor_type+";"+to_string(latitude)+";"+to_string(longitude);
}

double Sensor::getLast(QString measure){
    if (measure == "P1" || measure == "temperature" ){
        return records.last().getFirst();
    }else{
        return records.last().getSecond();
    }
}

double Sensor::getAverage(QString timeFrom, QString timeUntil, QString measure){
    int count = 0;
    double sum = 0;
    for (Record r : records){
        if (r.getTimestamp()>=timeFrom.toStdString() && r.getTimestamp()<=timeUntil.toStdString()){
            count++;
            if (measure == "P1" || measure == "temperature" ) sum += r.getFirst();
            else sum += r.getSecond();
        }
    }
    if (0 == count) return -9999;
    return sum/count;
}

bool Sensor::operator==(const Sensor &other) const{
    if (this->latitude == other.latitude
            && this->longitude == other.longitude
            && this->sensor_type == other.sensor_type){
        return true;
    }
    if (this->sensor_id == other.sensor_id)
        return true;
    else return false;
}


