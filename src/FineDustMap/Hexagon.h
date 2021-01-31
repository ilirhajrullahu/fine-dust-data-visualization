#ifndef HEXAGON_H
#define HEXAGON_H

#include <QColor>
#include <vector>

/**
 * @brief Class to represent a Hexagon and store its values.
 *
 */
class Hexagon
{

private:
    /**
     * The x coordinates of the edges of the hexagon.
     */
    double x0, x1, x2, x3, x4, x5;
    /**
     * The y coordinates of the edges of the hexagon.
     */
    double y0, y1, y2, y3, y4, y5;
    /**
     * The color of the hexagon.
     */
    QColor color;
    /**
     * The opacity of the hexagon.
     */
    double opacity;
    /**
     * The temperature value of the hexagon.
     */
    double valueTemp;
    /**
     * The Pm25 value of the hexagon.
     */
    double valuePm25;
    /**
     * The Pm10 value of the hexagon.
     */
    double valuePm10;
    /**
     * The humidity value of the hexagon.
     */
    double valueHumidity;

public:
    /**
     * @brief The default constructor.
     */
    Hexagon();
    /**
     * @brief The constructor for the Hexagon object.
     * @param x0 The x coordinate of an edge of the Hexagon.
     * @param x1 The x coordinate of an edge of the Hexagon.
     * @param x2 The x coordinate of an edge of the Hexagon.
     * @param x3 The x coordinate of an edge of the Hexagon.
     * @param x4 The x coordinate of an edge of the Hexagon.
     * @param x5 The x coordinate of an edge of the Hexagon.
     * @param y0 The y coordinate of an edge of the Hexagon.
     * @param y1 The y coordinate of an edge of the Hexagon.
     * @param y2 The y coordinate of an edge of the Hexagon.
     * @param y3 The y coordinate of an edge of the Hexagon.
     * @param y4 The y coordinate of an edge of the Hexagon.
     * @param y5 The y coordinate of an edge of the Hexagon.
     * @param color The color of the hexagon.
     * @param opacity The opacity of the hexagon.
     * @param valueTemp The temperature value of the hexagon.
     * @param valuePm25 The Pm25 value of the hexagon.
     * @param valuePm10 The Pm10 value of the hexagon.
     * @param valueHumidity The humidity value of the hexagon.
     */
    Hexagon(double x0, double x1, double x2, double x3, double x4, double x5, double y0, double y1, double y2, double y3, double y4, double y5,
            QColor color, double opacity, double valueTemp, double valuePm25, double valuePm10, double valueHumidity);
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getX0() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */

    double getX1() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getX2() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getX3() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getX4() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getX5() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getY0() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getY1() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getY2() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getY3() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getY4() const;
    /**
     * @brief Get method for edge coordinate of Hexagon.
     */
    double getY5() const;
    /**
     * @brief Get method for the color of the Hexagon.
     */
    QColor getColor() const;
    /**
     * @brief Get method for the opacity of the Hexagon.
     */
    double getOpacity() const;
    /**
     * @brief Get method for the current temperature of the sensors in the Hexagon.
     */
    double getValueTemp() const;
    /**
     * @brief Get method for the current Pm25 value of the sensors in the Hexagon.
     */
    double getValuePm25() const;
    /**
     * @brief Get method for the current Pm10 value of the sensors in the Hexagon.
     */
    double getValuePm10() const;
    /**
     * @brief Get method for the current Humidity of the sensors in the Hexagon.
     */
    double getValueHumidity() const;

    /**
     * @brief Method to return specific x or y coordinates of the edges of a Hexagon.
     * @param axis Is either the x or the y axis.
     * @param counter Is the edge of the Hexagon
     * @return The coordinate (x or y) depending on the parameters.
     */
    double getAllCoords(QString axis, int counter);

};

#endif // HEXAGON_H
