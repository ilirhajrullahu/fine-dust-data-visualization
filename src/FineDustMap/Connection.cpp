#include "Connection.h"
#include "Sensor.h"
#include "Sensormanager.h"
#include <QEventLoop>
#include <QNetworkReply>
#include <QUrlQuery>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QHash>
#include <string>
#include <QDir>
#include <sstream>
#include <fstream>

Connection::Connection(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

void Connection::postData(int id, std::string type, double lon, double lat, double first, double second, std::string timestamp)
{
    //Insert example: INSERT sensor,type=1 lat=2,lon=3,P1=4,P2=5

    QNetworkRequest request;
    request.setUrl(QUrl("http://localhost:8086/write?db=testdb"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QString insertStatement = "sensor,id=";
    insertStatement.append(QString::number(id));
    insertStatement.append(",type=");
    insertStatement.append(QString::fromStdString(type));
    insertStatement.append(" lat=");
    insertStatement.append(QString::number(lat));
    insertStatement.append(",lon=");
    insertStatement.append(QString::number(lon));
    if ((type == "SDS011") | (type == "PPD42NS")){
        insertStatement.append(",P1=");
        insertStatement.append(QString::number(first));
        insertStatement.append(",P2=");
        insertStatement.append(QString::number(second));
    }
    else {
        insertStatement.append(",temperature=");
        insertStatement.append(QString::number(first));
        insertStatement.append(",humidity=");
        insertStatement.append(QString::number(second));
    }
    insertStatement.append(" ");
    insertStatement.append(QString::fromStdString(timestamp));

    QByteArray postData = insertStatement.toUtf8();

    //manager = new QNetworkAccessManager(this);

    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

QNetworkReply* Connection::executeQuery(QString queryString){

    QUrlQuery query;
    query.addQueryItem("db", "testdb");
    query.addQueryItem("q", queryString);

    QUrl url("http://localhost:8086/query?pretty=true");
    url.setQuery(query);
    QNetworkRequest request(url);

    //manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    //qDebug() << reply->readAll();
    return reply;
}

double Connection::getValueFromReply(QString reply){
    //unpack JSON
    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply.toUtf8());

    double value =
            jsonResponse.object()["results"].toArray()[0]
            .toObject()["series"].toArray()[0]
            .toObject()["values"].toArray()[0]
            .toArray()[1].toDouble(); //jsonArray[0] is the time, jsonArray[1] is the value

    return value;
}

double Connection::getLastValue(double lon, double lat, QString measure)
{
    //Select example: SELECT LAST(P1) FROM sensor WHERE "lat"='48.554' AND "lon"='9.294'

    QString selectStatement = "SELECT LAST(";
    selectStatement.append(measure);
    selectStatement.append(") FROM sensor WHERE \"lat\"=");
    selectStatement.append(QString::number(lat));
    selectStatement.append(" AND \"lon\"=");
    selectStatement.append(QString::number(lon));

    QNetworkReply *reply = this->executeQuery(selectStatement);

    QString strReply = (QString)reply->readAll();

    return this->getValueFromReply(strReply);
}

double Connection::getLastValue(int id, QString measure)
{
    //Select example: SELECT LAST(P1) FROM sensor WHERE "id"='100'

    QString selectStatement = "SELECT LAST(";
    selectStatement.append(measure);
    selectStatement.append(") FROM sensor WHERE \"id\"='");
    selectStatement.append(QString::number(id));
    selectStatement.append("'");

    QNetworkReply *reply = this->executeQuery(selectStatement);

    QString strReply = (QString)reply->readAll();

    return this->getValueFromReply(strReply);
}

double Connection::getAverageWithinTimeRange(double lon, double lat, QString timeFrom, QString timeUntil, QString measure)
{
    //Example: SELECT mean(P2) FROM sensor WHERE lon=9.233 AND lat=50.205 ...
    //... AND time>=1514761100000000000 AND time<=1514761207000000000 group by id
    //alternative to timestamp: '2018-01-01T22:00:00Z'

    QString selectStatement = "SELECT MEAN(";
    selectStatement.append(measure);
    selectStatement.append(") FROM sensor WHERE \"lat\"=");
    selectStatement.append(QString::number(lat));
    selectStatement.append(" AND \"lon\"=");
    selectStatement.append(QString::number(lon));
    selectStatement.append(" AND time >= '");
    selectStatement.append(timeFrom);
    selectStatement.append("' AND time <='");
    selectStatement.append(timeUntil);
    selectStatement.append("' group by id");

    QNetworkReply *reply = this->executeQuery(selectStatement);

    QString strReply = (QString)reply->readAll();

    return this->getValueFromReply(strReply);
}

void Connection::backup(QString startTime, QString endTime, QString frequency){
    backupSensors();
    backupRecords("P1", startTime, endTime, frequency);
    backupRecords("P2", startTime, endTime, frequency);
    backupRecords("temperature", startTime, endTime, frequency);
    backupRecords("humidity", startTime, endTime, frequency);
}

void Connection::backupSensors(){
    qDebug() << "Starting backup sensors...";

    std::ofstream myfile;
    myfile.open ("../FineDustMap/Backup/sensorBackup.csv", std::ofstream::trunc);

    //Get sensor data frm the DB
    QString selectStatement = "SHOW SERIES";
    QNetworkReply *reply = this->executeQuery(selectStatement);
    QString strReply = (QString)reply->readAll();

    //unpack JSON
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    //response object
    QJsonObject jsonObject = jsonResponse.object();

    QJsonArray jsonArray =
            jsonObject["results"].toArray()[0]
            .toObject()["series"].toArray()[0]
            .toObject()["values"].toArray();

    for (auto sensorData : jsonArray){
        //Data example: "sensor,id=5553,type=SDS011"
        QString data = sensorData.toArray()[0].toString();
        //First section example: "nr=1000". "nr=" removed
        int id = data.section(",", 1, 1).remove(0, 3).toInt();
        //Second section example "type=SDS011". "type=" removed
        QString type = data.section(",", 2, 2).remove(0, 5);

        //get lon and lat (They are not keys, but fieleds)
        double lon = getLastValue(id, "lon");
        double lat = getLastValue(id, "lat");

        myfile << id << ";" << type.toStdString() << ";" << lat << ";" << lon << "\n";
    }
    myfile.close();
    qDebug() << "Backup copy of sensors created!";
}

void Connection::backupRecords(QString measure, QString startTime, QString endTime, QString frequency){
    cout << "Starting backup " << measure.toStdString() << " records..." << endl;

    std::ofstream myfile;
    string path = "../FineDustMap/Backup/record";
    path += measure.toStdString();
    path += "Backup.csv";
    myfile.open (path, std::ofstream::trunc);

    //Get sensor data frm the DB
    QString selectStatement = "SELECT mean(";
    selectStatement.append(measure);
    selectStatement.append(") FROM sensor WHERE time>'");
    selectStatement.append(startTime);
    selectStatement.append("' AND time<'");
    selectStatement.append(endTime);
    selectStatement.append("'GROUP BY time(");
    selectStatement.append(frequency);
    selectStatement.append("), id FILL(none)");
    QNetworkReply *reply = this->executeQuery(selectStatement);
    QString strReply = (QString)reply->readAll();

    //unpack JSON
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    //response object
    QJsonObject jsonObject = jsonResponse.object();
    //results array
    QJsonArray jsonArray = jsonObject["results"].toArray()[0].toObject()["series"].toArray();

    for (auto sensor : jsonArray){
        jsonObject = sensor.toObject();
        int id = jsonObject["tags"].toObject()["id"].toString().toInt();
        QJsonArray recordsArray = jsonObject["values"].toArray();
        for (auto record : recordsArray){
            QString time = record.toArray()[0].toString();
            double val = record.toArray()[1].toDouble();
            myfile << id << ";" << time.toStdString() << ";" << val << "\n";
        }
    }
    myfile.close();
    qDebug() << "Backup copy created!";
}
