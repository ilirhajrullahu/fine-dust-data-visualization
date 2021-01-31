#ifndef HEXAGONMODEL_H
#define HEXAGONMODEL_H

#include "Hexagon.h"
#include "Sensormanager.h"
#include <QAbstractListModel>
#include <QQmlProperty>
#include <QObject>
#include <QVariant>
#include <iostream>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QQmlContext>

/**
 * @brief Class to represent a Hexagon and help for the drawing of the Hexagon.
 */
class HexagonModel : public QAbstractListModel
{
    Q_OBJECT

protected:
    /**
     * @brief Returns the model's role names.
     * @return Returns the model's role names.
     */
    QHash<int, QByteArray> roleNames() const;

private:
    /**
     * @brief A list of all created hexagons.
     */
    QList<Hexagon> m_hexagons;

    /**
     * @brief Variable to use SensorManager methods.
     */
    SensorManager * sm;

public :
    /**
     * @brief Current zoomlevel of the map.
     */
    double zoomLevel;

    /**
     * @brief Enum that contains all roles used by the model.
     */
    enum HexagonRoles {
        x0 = Qt::UserRole + 1, x1, x2, x3, x4, x5, y0, y1, y2, y3, y4, y5, tileColor, tileOpacity, valueTemp, valuePm25, valuePm10, valueHumidity
    };

    /**
     * @brief Constructs an abstract list model with the given parent.
     * @param parent given parent
     */
    HexagonModel(QObject * parent = 0);

    /**
     * @brief Constructs an abstract list model with a reference to the SensorManager.
     * @param sensorManager SensorManager with sensor data
     */
    HexagonModel (SensorManager * sensorManager);

    /**
     * @brief Adds a new hexagon to the model.
     * @param hexagon Create a new hexagon and use it as argument.
     */
    void addHexagon(const Hexagon &hexagon);

    /**
     * @brief Remove all hexagons from the model.
     */
    Q_INVOKABLE void removeHexagons();

    /**
     * @brief Returns the number of rows under the given parent.
     *
     * @param parent given parent
     * @return number of children of parend
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief Returns the data stored under the given role for the item referred to by the index.
     * @param index index of the item
     * @param role role of the item
     * @return stored data
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * @brief Matches the measured temperature value to the corresponding color from the legend.
     *
     * If the parameter is -9999 the color #00FFFFFF is returned.
     *
     * @param temperature measurement
     * @return corresponding color for the measurement
     */
    Q_INVOKABLE QColor getTempTileColor(double);

    /**
     * @brief Matches the measured Pm25 value to the corresponding color from the legend.
     *
     * If the parameter is -9999 the color #00FFFFFF is returned.
     *
     * @param Pm25 measurement
     * @return corresponding color for the measurement
     */
    Q_INVOKABLE QColor getPm25TileColor(double);

    /**
     * @brief Matches the measured Pm10 value to the corresponding color from the legend.
     *
     * If the parameter is -9999 the color #00FFFFFF is returned.
     *
     * @param Pm10 measurement
     * @return corresponding color for the measurement
     */
    Q_INVOKABLE QColor getPm10TileColor(double);

    /**
     * @brief Matches the measured humidity value to the corresponding color from the legend.
     *
     * If the parameter is -9999 the color #00FFFFFF is returned.
     *
     * @param humidity measurement
     * @return corresponding color for the measurement
     */
    Q_INVOKABLE QColor getHumidityTileColor(double);

    /**
     * @brief set zoomLevel
     * @param zoomLevel new zoomLevel
     */
    Q_INVOKABLE void currentZoomLevel(QVariant zoomLevel);

    /**
     * @brief Model for zoomlevel between 0 and 7.
     *
     * Creates the model with all the hexagons for a zoomlevel between 0 and 7.
     *
     * @param model Model from main.cpp
     * @param ctxt QQmlContext from main.cpp
     */
    Q_INVOKABLE void zoomLevelBT0(HexagonModel &model, QQmlContext *ctxt);

    /**
     * @brief Model for zoomlevel between 7 and 9.
     *
     * Creates the model with all the hexagons for a zoomlevel between 7 and 9.
     *
     * @param model Model from main.cpp
     * @param ctxt QQmlContext from main.cpp
     */
    Q_INVOKABLE void zoomLevelBT7(HexagonModel &model, QQmlContext *ctxt);

    /**
     * @brief Model for zoomlevel between 9 and 10.
     *
     * Creates the model with all the hexagons for a zoomlevel between 9 and 10.
     *
     * @param model Model from main.cpp
     * @param ctxt QQmlContext from main.cpp
     */
    Q_INVOKABLE void zoomLevelBT9(HexagonModel &model, QQmlContext *ctxt);

    /**
     * @brief Model for zoomlevel between 10 and 12.
     *
     * Creates the model with all the hexagons for a zoomlevel between 10 and 12.
     *
     * @param model Model from main.cpp
     * @param ctxt QQmlContext from main.cpp
     */
    Q_INVOKABLE void zoomLevelBT10(HexagonModel &model, QQmlContext *ctxt);

    /**
     * @brief Model for zoomlevel bigger then 12.
     *
     * Creates the model with all the hexagons for a zoomlevel bigger then 12.
     *
     * @param model Model from main.cpp
     * @param ctxt QQmlContext from main.cpp
     */
    Q_INVOKABLE void zoomLevelBT12(HexagonModel &model, QQmlContext *ctxt);
};

#endif // HEXAGONMODEL_H
