#include "Sensormanager.h"
#include "Sensor.h"
#include "Connection.h"
#include <QDir>
#include <sstream>
#include <fstream>
#include <QGeoAddress>
#include <QGeoCodingManager>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoServiceProvider>
#include <QEventLoop>
#include <QCoreApplication>


SensorManager::SensorManager(QObject *parent) : QObject(parent) {
    tmpRectangle = getCityRectangle("Darmstadt");
    qDebug() << "Start with using backup data...";
    ifstream fin;
    string line;
    // Open an existing file
    fin.open("../FineDustMap/Backup/sensorBackup.csv", ifstream::in);
    while (getline(fin, line)) {
        QString l = QString::fromStdString(line);
        Sensor s(l.section(";", 0, 0).toInt(), //Id
                 l.section(";", 1, 1).toStdString(), //Type
                 l.section(";", 2, 2).toDouble(), //lat
                 l.section(";", 3, 3).toDouble()); //lon
        addSensor(s);
    }
    fin.close();
    recordDatafromBackup();
    qDebug() << "Successfull!";
}

void SensorManager::LoadDataFromDirectoryToDB(string pathToDir) {
    QDir directory(pathToDir.c_str());
    QStringList files = directory.entryList(QStringList() << "*.csv" << "*.CSV",QDir::Files);
    foreach(QString filename, files){
        std::string filePath = pathToDir + filename.toStdString();
        std::cout << filePath << std::endl;
        //create Sensor object to read data from CSV
        //The creation of the object starts the export of data into the DB automatically
        Sensor s (filePath);
    }
}

void SensorManager::addSensor(Sensor s){
    sensors.insert(s.getSensor_id(), s);
}

void SensorManager::addRecordToSensor(int id, string timestamp, double firstValue, double secondValue){
    sensors.find(id)->addRecord(timestamp, firstValue, secondValue);
}

void SensorManager::recordDatafromBackup(){
    readBackupFile("P1");
    readBackupFile("P2");
    readBackupFile("temperature");
    readBackupFile("humidity");
}

void SensorManager::readBackupFile(QString measure){
    ifstream fin;
    string line;
    QString path = "../FineDustMap/Backup/record";
    path.append(measure);
    path.append("Backup.csv");
    fin.open(path.toStdString(), ifstream::in);
    while (getline(fin, line)) {
        QString l = QString::fromStdString(line);
        int id = l.section(";", 0, 0).toInt();
        if (measure == "P1" || measure == "temperature")
            sensors.find(id)->addRecord(l.section(";", 1, 1).toStdString(), l.section(";", 2, 2).toDouble(), -1);
        else
            sensors.find(id)->addRecord(l.section(";", 1, 1).toStdString(), -1, l.section(";", 2, 2).toDouble());
    }
    fin.close();
}

int SensorManager::getSensorIdOnPosition(double lon, double lat, QString measure){
    if (measure == "P1" || measure == "P2"){
        Sensor s(1, "SDS011", lat, lon);
        return sensors.find(sensors.key(s))->getSensor_id();
    }
    else if (measure == "temperature" || measure == "humidity") {
        Sensor s(1, "DHT22", lat, lon);
        return sensors.find(sensors.key(s))->getSensor_id();
    }
    else return -1;
}

double SensorManager::getLast(int id, QString measure){
    return sensors.find(id)->getLast(measure);
}

double SensorManager::getAverage(int id, QString timeFrom, QString timeUntil, QString measure){
    return sensors.find(id)->getAverage(timeFrom, timeUntil, measure);
}

double SensorManager::getLast(double lon, double lat, QString measure){
    return getLast(getSensorIdOnPosition(lon, lat, measure), measure);
}

double SensorManager::getAverage(double lon, double lat, QString timeFrom, QString timeUntil, QString measure){
    return getAverage(getSensorIdOnPosition(lon, lat, measure), timeFrom, timeUntil, measure);
}

void SensorManager::findSensorsInCity(QString cityName, QString measure){
    if (cityName == lastCity && measure == lastMeasure) return;
    lastMeasure = measure;
    sensorsList.clear();
    QGeoRectangle rectangle = getCityRectangle(cityName);
    for (Sensor s : sensors){
        if(s.getLatitude()<rectangle.bottomRight().latitude()
                && s.getLatitude()>rectangle.topLeft().latitude()
                && s.getLongitude()<rectangle.bottomRight().longitude()
                && s.getLongitude()>rectangle.topLeft().longitude()){
            if (((measure == "P1" || measure == "P2") && s.getSensor_type()=="SDS011") ||
                    ((measure == "temperature" || measure == "humidity") && s.getSensor_type()=="DHT22")){
                sensorsList.append(s.getSensor_id());
            }
        }
    }
}

double SensorManager::avgCityValue(QString cityName, QString measure, QString timeFrom, QString timeUntil){
    cout << "Start computing average " << measure.toStdString() << " in " << cityName.toStdString() << endl;
    findSensorsInCity(cityName, measure);
    double sum = 0;
    double count = 0;
    for (int nr : sensorsList){
        double SensorAvg = sensors.values(nr).first().getAverage(timeFrom, timeUntil, measure);
        if (-9999 != SensorAvg){
            sum += SensorAvg;
            count++;
        }
    }
    if (0==count) {
        cout << "0 sensors in this area or time interval!" << endl;
        return -9999;
    }
    cout << "Successful! " << count << " sensors were considered." << endl;
    return sum/count;
}

QGeoLocation SensorManager::getLocation(QString cityName){
    QGeoLocation location;
    QEventLoop eventLoop;
    QString entry = "esri";
    QGeoServiceProvider qGeoService(entry);
    QGeoCodingManager *pQGeoCoder = qGeoService.geocodingManager();
    if (!pQGeoCoder) {
        cerr << "GeoCodingManager '" << entry.toStdString() << "' not available!" << endl;
        return location;
    }

    QLocale qLocaleC(QLocale::C, QLocale::AnyCountry);
    pQGeoCoder->setLocale(qLocaleC);
    // build address
    QGeoAddress qGeoAddr;
    qGeoAddr.setCountry(QString::fromUtf8("Germany"));
    qGeoAddr.setCity(cityName);
    QGeoCodeReply *pQGeoCode = pQGeoCoder->geocode(qGeoAddr);
    if (!pQGeoCode) {
        cerr << "GeoCoding totally failed!" << endl;
        return location;
    }
    QObject::connect(pQGeoCode, &QGeoCodeReply::finished,
                     [&eventLoop, &location, pQGeoCode](){
        cout << "Reply: " << pQGeoCode->errorString().toStdString();
        switch (pQGeoCode->error()) {
#define CASE(ERROR) \
        case QGeoCodeReply::ERROR: cerr << #ERROR << endl; break
        CASE(NoError);
        CASE(EngineNotSetError);
        CASE(CommunicationError);
        CASE(ParseError);
        CASE(UnsupportedOptionError);
        CASE(CombinationError);
        CASE(UnknownError);
#undef CASE
        default: cerr << "Undocumented error!" << endl;
        }
        if (pQGeoCode->error() != QGeoCodeReply::NoError) return;
        QList<QGeoLocation> qGeoLocs = pQGeoCode->locations();
        cout << qGeoLocs.size() << " location(s) returned." << endl;
        for (QGeoLocation &qGeoLoc : qGeoLocs) {
            location = qGeoLoc;
            if (qGeoLoc.address().city() == ""){
                cout << "The city was not found!" << endl;
            }
        }
        eventLoop.exit(0);
    });
    eventLoop.exec();
    return location;
}

QGeoRectangle SensorManager::getCityRectangle(QString cityName){
    if (lastCity == cityName) return tmpRectangle;
    lastCity = cityName;
    tmpRectangle = getLocation(cityName).boundingBox();
    return tmpRectangle;
}

QGeoCoordinate SensorManager::getCityCenter(QString cityName){
    return getLocation(cityName).coordinate();
}

double SensorManager::getAveragePolygonValue(double polyY[6], double polyX[6], QString dataValue){
    int counter = 0;
    double averageValue = 0.0;

    for ( auto it = this->sensors.begin(); it != this->sensors.end(); ++it )
    {
        if (pointInPolygon(polyY,polyX,it->getLatitude(),it->getLongitude()) == true){
            if (((dataValue == "P1" || dataValue == "P2") && it->getSensor_type()=="SDS011") ||((dataValue == "temperature" || dataValue == "humidity") && it->getSensor_type()=="DHT22")){
                averageValue+=it->getLast(dataValue);
                ++counter;
            }
        }
    }
    if (counter == 0){
        return -9999;
    }else{
        return averageValue/counter;
    }
}

bool SensorManager::pointInPolygon(double polyY[6], double polyX[6], double y, double x)
{
    int polyCorners = 6;
    int   i, j = polyCorners-1;
    bool  oddNodes=false;

    for (i=0; i<polyCorners; i++) {
        if ((polyY[i]<y && polyY[j]>=y)||(polyY[j]<y && polyY[i]>=y)) {
            if (polyX[i]+(y-polyY[i])/(polyY[j]-polyY[i])*(polyX[j]-polyX[i])<x) {
                oddNodes=!oddNodes; }}
        j=i;
    }

    return oddNodes;
}
