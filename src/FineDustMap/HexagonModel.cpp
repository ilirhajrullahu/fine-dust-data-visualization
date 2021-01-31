#include "HexagonModel.h"

HexagonModel::HexagonModel(QObject *parent)
    : QAbstractListModel(parent)
{
    //    this->zoomLevelBT0();
}

HexagonModel::HexagonModel(SensorManager * sensorManager){
    sm = sensorManager;
}

void HexagonModel::addHexagon(const Hexagon &hexagon)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_hexagons << hexagon;
    endInsertRows();
}

void HexagonModel::removeHexagons()
{
    beginResetModel();
    m_hexagons.clear();
    endResetModel();
}

int HexagonModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_hexagons.count();
}

QVariant HexagonModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_hexagons.count())
        return QVariant();

    const Hexagon &hexagon = m_hexagons[index.row()];

    switch(role) {
    case x0:
        return hexagon.getX0();
        break;
    case x1:
        return hexagon.getX1();
        break;
    case x2:
        return hexagon.getX2();
        break;
    case x3:
        return hexagon.getX3();
        break;
    case x4:
        return hexagon.getX4();
        break;
    case x5:
        return hexagon.getX5();
        break;
    case y0:
        return hexagon.getY0();
        break;
    case y1:
        return hexagon.getY1();
        break;
    case y2:
        return hexagon.getY2();
        break;
    case y3:
        return hexagon.getY3();
        break;
    case y4:
        return hexagon.getY4();
        break;
    case y5:
        return hexagon.getY5();
        break;
    case tileColor:
        return hexagon.getColor();
        break;
    case tileOpacity:
        return hexagon.getOpacity();
        break;
    case valueTemp:
        return hexagon.getValueTemp();
        break;
    case valuePm25:
        return hexagon.getValuePm25();
        break;
    case valuePm10:
        return hexagon.getValuePm10();
        break;
    case valueHumidity:
        return hexagon.getValueHumidity();
        break;
    }
    return QVariant();
}

QColor HexagonModel::getTempTileColor(double value)
{
    if (value == -9999) {
        return "#00FFFFFF";
    } else if(value <= -5) {
        return "blue";
    } else if(value > -5 && value <= 5) {
        return "cyan";
    } else if(value > 5 && value <= 15) {
        return "green";
    } else if(value > 15 && value <= 25) {
        return "yellow";
    } else if(value > 25 && value <= 35) {
        return "orange";
    } else if(value > 35) {
        return "red";
    } else {
        return "#00FFFFFF";
    }
}

QColor HexagonModel::getPm25TileColor(double value)
{
    if (value == -9999) {
        return "#00FFFFFF";
    } else if(value <= 20) {
        return "#0a635d";
    } else if(value > 20 && value <= 40) {
        return "orange";
    } else if(value > 40 && value <= 90) {
        return "red";
    } else if(value > 90) {
        return "purple";
    } else {
        return "#00FFFFFF";
    }
}

QColor HexagonModel::getPm10TileColor(double value)
{
    if (value == -9999) {
        return "#00FFFFFF";
    } else if(value <= 25) {
        return "#0a635d";
    } else if(value > 25 && value <= 50) {
        return "orange";
    } else if(value > 50 && value <= 150) {
        return "red";
    } else if(value > 150) {
        return "purple";
    } else {
        return "#00FFFFFF";
    }
}

QColor HexagonModel::getHumidityTileColor(double value)
{
    if (value == -9999) {
        return "#00FFFFFF";
    } else if(value <= 20) {
        return "red";
    } else if(value > 20 && value <= 40) {
        return "orange";
    } else if(value > 40 && value <= 55) {
        return "yellow";
    } else if(value > 55 && value <= 80) {
        return "green";
    } else if(value > 80 && value <= 95) {
        return "cyan";
    } else if(value > 95) {
        return "blue";
    } else {
        return "#00FFFFFF";
    }
}

/*double HexagonModel::getZoomLevel() const
{
    return zoomLevel;
}*/

void HexagonModel::currentZoomLevel(QVariant zoomLevel)
{
    this->zoomLevel = zoomLevel.toDouble();
    std::cout << this->zoomLevel << std::endl;
}

void HexagonModel::zoomLevelBT0(HexagonModel &model, QQmlContext *ctxt)
{
    std::cout << "ZoomLevelBT0 wird geladen!" << std::endl;

    Hexagon hexagon;
    double columncounter = 0;
    double rowcounter = 0;
    bool gate = false;

    //die punkte als arrays
    double newX[6];
    double newY[6];

    //das hexagon von dem alle anderen abgeleitet werden
    Hexagon *startHex = new Hexagon(5.565, 6.065, 6.065, 5.565, 5.065, 5.065,
                                    47.115, 47.365, 47.615, 47.865, 47.615, 47.365, "red", 0, 0, 0, 0, 0);

    //SensorManager sm;
    double tempVal, pm25Val, pm10Val, humidityVal;

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<10; j++)
        {
            //newX/newY -> neue koordinaten für das nächste hexagon in der schleife -> wird aus dem starthexagon + counter berechnet
            for(int k=0; k<6; k++)
            {
                newX[k] = startHex->getAllCoords("x", k) + columncounter;
                newY[k] = startHex->getAllCoords("y", k) + rowcounter;
            }

            tempVal = sm->getAveragePolygonValue(newY, newX, "temperature");
            pm25Val = sm->getAveragePolygonValue(newY, newX, "P1");
            pm10Val = sm->getAveragePolygonValue(newY, newX, "P2");
            humidityVal = sm->getAveragePolygonValue(newY, newX, "humidity");
            if(!(tempVal == -9999 && pm25Val == -9999 && pm10Val == -9999 && humidityVal == -9999)){
                model.addHexagon(Hexagon(newX[0], newX[1], newX[2], newX[3], newX[4], newX[5],      //x0... -> longi
                        newY[0], newY[1], newY[2], newY[3], newY[4], newY[5],      //y0... -> lati
                        model.getPm25TileColor(pm25Val), 0.6, tempVal, pm25Val, pm10Val, humidityVal));  //Farbe des Hexagon, opacity, temp, pm25, pm10
            }
            columncounter = columncounter + 1;
        }
        if(gate == false){
            columncounter = 0.5;
            gate = true;
        }else{
            columncounter = 0;
            gate = false;
        }
        rowcounter = rowcounter + 0.5;
    }
    ctxt->setContextProperty("modelBT0", &model);
}

void HexagonModel::zoomLevelBT7(HexagonModel &model, QQmlContext *ctxt)
{
    std::cout << "ZoomLevelBT6 wird geladen!" << std::endl;

    Hexagon hexagon;
    double columncounter = 0;
    double rowcounter = 0;
    bool gate = false;

    //die punkte als arrays
    double newX[6];
    double newY[6];

    //das hexagon von dem alle anderen abgeleitet werden
    Hexagon *startHex = new Hexagon(5.565, 5.865, 5.865, 5.565, 5.265, 5.265,
                                    47.115, 47.265, 47.415, 47.565, 47.415, 47.265, "red", 0, 0, 0, 0, 0);

    double tempVal, pm25Val, pm10Val, humidityVal;

    for(int i=0; i<27; i++)
    {
        for(int j=0; j<17; j++)
        {
            //newX/newY -> neue koordinaten für das nächste hexagon in der schleife -> wird aus dem starthexagon + counter berechnet
            for(int k=0; k<6; k++)
            {
                newX[k] = startHex->getAllCoords("x", k) + columncounter;
                newY[k] = startHex->getAllCoords("y", k) + rowcounter;
            }

            tempVal = sm->getAveragePolygonValue(newY, newX, "temperature");
            pm25Val = sm->getAveragePolygonValue(newY, newX, "P1");
            pm10Val = sm->getAveragePolygonValue(newY, newX, "P2");
            humidityVal = sm->getAveragePolygonValue(newY, newX, "humidity");
            if(!(tempVal == -9999 && pm25Val == -9999 && pm10Val == -9999 && humidityVal == -9999)){
                model.addHexagon(Hexagon(newX[0], newX[1], newX[2], newX[3], newX[4], newX[5],      //x0... -> longi
                        newY[0], newY[1], newY[2], newY[3], newY[4], newY[5],      //y0... -> lati
                        model.getPm25TileColor(pm25Val), 0.6, tempVal, pm25Val, pm10Val, humidityVal));  //Farbe des Hexagon, opacity, temp, pm25, pm10
            }
            columncounter = columncounter + 0.6;
        }
        if(gate == false){
            columncounter = 0.3;
            gate = true;
        }else{
            columncounter = 0;
            gate = false;
        }
        rowcounter = rowcounter + 0.3;
    }
    ctxt->setContextProperty("modelBT7", &model);
}

void HexagonModel::zoomLevelBT9(HexagonModel &model, QQmlContext *ctxt)
{
    std::cout << "ZoomLevelBT9 wird geladen!" << std::endl;

    Hexagon hexagon;
    double columncounter = 0;
    double rowcounter = 0;
    bool gate = false;

    //die punkte als arrays
    double newX[6];
    double newY[6];

    //das hexagon von dem alle anderen abgeleitet werden
    Hexagon *startHex = new Hexagon(5.565, 5.765, 5.765, 5.565, 5.365, 5.365,
                                    47.115, 47.215, 47.315, 47.415, 47.315, 47.215, "red", 0, 0, 0, 0, 0);

    double tempVal, pm25Val, pm10Val, humidityVal;

    for(int i=0; i<41; i++)
    {
        for(int j=0; j<25; j++)
        {
            //newX/newY -> neue koordinaten für das nächste hexagon in der schleife -> wird aus dem starthexagon + counter berechnet
            for(int k=0; k<6; k++)
            {
                newX[k] = startHex->getAllCoords("x", k) + columncounter;
                newY[k] = startHex->getAllCoords("y", k) + rowcounter;
            }

            tempVal = sm->getAveragePolygonValue(newY, newX, "temperature");
            pm25Val = sm->getAveragePolygonValue(newY, newX, "P1");
            pm10Val = sm->getAveragePolygonValue(newY, newX, "P2");
            humidityVal = sm->getAveragePolygonValue(newY, newX, "humidity");
            if(!(tempVal == -9999 && pm25Val == -9999 && pm10Val == -9999 && humidityVal == -9999)){
                model.addHexagon(Hexagon(newX[0], newX[1], newX[2], newX[3], newX[4], newX[5],      //x0... -> longi
                        newY[0], newY[1], newY[2], newY[3], newY[4], newY[5],      //y0... -> lati
                        model.getPm25TileColor(pm25Val), 0.6, tempVal, pm25Val, pm10Val, humidityVal));  //Farbe des Hexagon, opacity, temp, pm25, pm10
            }
            columncounter = columncounter + 0.4;
        }
        if(gate == false){
            columncounter = 0.2;
            gate = true;
        }else{
            columncounter = 0;
            gate = false;
        }
        rowcounter = rowcounter + 0.2;
    }
    ctxt->setContextProperty("modelBT9", &model);
}

void HexagonModel::zoomLevelBT10(HexagonModel &model, QQmlContext *ctxt)
{
    std::cout << "ZoomLevelBT10 wird geladen!" << std::endl;

    Hexagon hexagon;
    double columncounter = 0;
    double rowcounter = 0;
    bool gate = false;

    //die punkte als arrays
    double newX[6];
    double newY[6];

    //das hexagon von dem alle anderen abgeleitet werden
    Hexagon *startHex = new Hexagon(5.565, 5.615, 5.615, 5.565 , 5.515 ,5.515 ,
                                    47.115,47.140 , 47.165 ,47.19 ,47.165 , 47.140, "red", 0, 0, 0, 0, 0);

    double tempVal, pm25Val, pm10Val, humidityVal;

    for(int i=0; i<156; i++)
    {
        for(int j=0; j<96; j++)
        {
            //newX/newY -> neue koordinaten für das nächste hexagon in der schleife -> wird aus dem starthexagon + counter berechnet
            for(int k=0; k<6; k++)
            {
                newX[k] = startHex->getAllCoords("x", k) + columncounter;
                newY[k] = startHex->getAllCoords("y", k) + rowcounter;
            }

            tempVal = sm->getAveragePolygonValue(newY, newX, "temperature");
            pm25Val = sm->getAveragePolygonValue(newY, newX, "P1");
            pm10Val = sm->getAveragePolygonValue(newY, newX, "P2");
            humidityVal = sm->getAveragePolygonValue(newY, newX, "humidity");
            if(!(tempVal == -9999 && pm25Val == -9999 && pm10Val == -9999 && humidityVal == -9999)){
                model.addHexagon(Hexagon(newX[0], newX[1], newX[2], newX[3], newX[4], newX[5],      //x0... -> longi
                        newY[0], newY[1], newY[2], newY[3], newY[4], newY[5],      //y0... -> lati
                        model.getPm25TileColor(pm25Val), 0.6, tempVal, pm25Val, pm10Val, humidityVal));  //Farbe des Hexagon, opacity, temp, pm25, pm10
            }
            columncounter = columncounter + 0.1;
        }
        if(gate == false){
            columncounter = 0.05;
            gate = true;
        }else{
            columncounter = 0;
            gate = false;
        }
        rowcounter = rowcounter + 0.05;
    }
    ctxt->setContextProperty("modelBT10", &model);
}

void HexagonModel::zoomLevelBT12(HexagonModel &model, QQmlContext *ctxt)
{
    std::cout << "ZoomLevelBT12 wird geladen!" << std::endl;

    Hexagon hexagon;
    double columncounter = 0;
    double rowcounter = 0;
    bool gate = false;

    //die punkte als arrays
    double newX[6];
    double newY[6];

    //das hexagon von dem alle anderen abgeleitet werden
    Hexagon *startHex = new Hexagon(5.565, 5.59, 5.59, 5.565 , 5.54 ,5.54 ,
                                    47.115,47.1275 , 47.14 ,47.1525 ,47.14 , 47.1275, "red", 0, 0, 0, 0, 0);

    double tempVal, pm25Val, pm10Val, humidityVal;

    for(int i=0; i<312; i++)
    {
        for(int j=0; j<192; j++)
        {
            //newX/newY -> neue koordinaten für das nächste hexagon in der schleife -> wird aus dem starthexagon + counter berechnet
            for(int k=0; k<6; k++)
            {
                newX[k] = startHex->getAllCoords("x", k) + columncounter;
                newY[k] = startHex->getAllCoords("y", k) + rowcounter;
            }

            tempVal = sm->getAveragePolygonValue(newY, newX, "temperature");
            pm25Val = sm->getAveragePolygonValue(newY, newX, "P1");
            pm10Val = sm->getAveragePolygonValue(newY, newX, "P2");
            humidityVal = sm->getAveragePolygonValue(newY, newX, "humidity");
            if(!(tempVal == -9999 && pm25Val == -9999 && pm10Val == -9999 && humidityVal == -9999)){
                model.addHexagon(Hexagon(newX[0], newX[1], newX[2], newX[3], newX[4], newX[5],      //x0... -> longi
                        newY[0], newY[1], newY[2], newY[3], newY[4], newY[5],      //y0... -> lati
                        model.getPm25TileColor(pm25Val), 0.6, tempVal, pm25Val, pm10Val, humidityVal));  //Farbe des Hexagon, opacity, temp, pm25, pm10
            }
            columncounter = columncounter + 0.05;
        }
        if(gate == false){
            columncounter = 0.025;
            gate = true;
        }else{
            columncounter = 0;
            gate = false;
        }
        rowcounter = rowcounter + 0.025;
    }
    ctxt->setContextProperty("modelBT12", &model);
}

QHash<int, QByteArray> HexagonModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[x0] = "x0";
    roles[x1] = "x1";
    roles[x2] = "x2";
    roles[x3] = "x3";
    roles[x4] = "x4";
    roles[x5] = "x5";
    roles[y0] = "y0";
    roles[y1] = "y1";
    roles[y2] = "y2";
    roles[y3] = "y3";
    roles[y4] = "y4";
    roles[y5] = "y5";
    roles[tileColor] = "tileColor";
    roles[tileOpacity] = "tileOpacity";
    roles[valueTemp] = "valueTemp";
    roles[valuePm25] = "valuePm25";
    roles[valuePm10] = "valuePm10";
    roles[valueHumidity] = "valueHumidity";

    return roles;
}
