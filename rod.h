#ifndef ROD_H
#define ROD_H

#include <QtGui>
struct Rod
{
    float Ll = 0;
    float Aa = 0;
    float Ee = 0;
    float Qq = 0;
    float Fl = 0;
    float Fr = 0;
    float longY;
    float longX;
    QPointF pointLB;
    QPointF pointLT;
    QPointF pointRB;
    QPointF pointRT;
    QPolygonF polygon;
    float edgeForceL;
    float edgeForceR;
    bool zadelkaL = false;
    bool zadelkaR = false;
    double UuMOOOOVEL = 0;
    double UuMOOOOVER = 0;
    float NnL = 0;
    float NnR = 0;
    QPointF epyrNnL;
    QPointF epyrNnR;
};

#endif // ROD_H
