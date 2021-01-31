#include "Hexagon.h"
#include <iostream>

Hexagon::Hexagon()
{
}

Hexagon::Hexagon(double x0, double x1, double x2, double x3, double x4, double x5, double y0, double y1, double y2, double y3, double y4, double y5,
                 QColor color, double opacity, double valueTemp, double valuePm25, double valuePm10, double valueHumidity)
{
    this->x0 = x0;
    this->x1 = x1;
    this->x2 = x2;
    this->x3 = x3;
    this->x4 = x4;
    this->x5 = x5;
    this->y0 = y0;
    this->y1 = y1;
    this->y2 = y2;
    this->y3 = y3;
    this->y4 = y4;
    this->y5 = y5;
    this->color = color;
    this->opacity = opacity;
    this->valueTemp = valueTemp;
    this->valuePm25 = valuePm25;
    this->valuePm10 = valuePm10;
    this->valueHumidity = valueHumidity;
}

double Hexagon::getX0() const
{
    return x0;
}

double Hexagon::getX1() const
{
    return x1;
}

double Hexagon::getX2() const
{
    return x2;
}

double Hexagon::getX3() const
{
    return x3;
}

double Hexagon::getX4() const
{
    return x4;
}

double Hexagon::getX5() const
{
    return x5;
}

double Hexagon::getY0() const
{
    return y0;
}

double Hexagon::getY1() const
{
    return y1;
}

double Hexagon::getY2() const
{
    return y2;
}

double Hexagon::getY3() const
{
    return y3;
}

double Hexagon::getY4() const
{
    return y4;
}

double Hexagon::getY5() const
{
    return y5;
}

QColor Hexagon::getColor() const
{
    return color;
}

double Hexagon::getOpacity() const
{
    return opacity;
}

double Hexagon::getValueTemp() const
{
    return valueTemp;
}

double Hexagon::getValuePm25() const
{
    return valuePm25;
}

double Hexagon::getValuePm10() const
{
    return valuePm10;
}

double Hexagon::getValueHumidity() const
{
    return valueHumidity;
}

double Hexagon::getAllCoords(QString axis, int counter)
{
    if(axis == "x")
    {
        switch (counter) {
        case 0:
            return x0;
            break;
        case 1:
            return x1;
            break;
        case 2:
            return x2;
            break;
        case 3:
            return x3;
            break;
        case 4:
            return x4;
            break;
        case 5:
            return x5;
            break;
        default:
            break;
        }
    } else if(axis == "y") {
        switch (counter) {
        case 0:
            return y0;
            break;
        case 1:
            return y1;
            break;
        case 2:
            return y2;
            break;
        case 3:
            return y3;
            break;
        case 4:
            return y4;
            break;
        case 5:
            return y5;
            break;
        default:
            break;
        }
    }
    return 0;
}
