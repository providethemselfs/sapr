#ifndef CALCULATION_H
#define CALCULATION_H

#include "rod.h"


class Calculation
{
public:
    QVector<Rod*> vecRods;
    Calculation();
    void CalEdgeForce();
    void getVecRods(QVector<Rod*> item);
    double helpCalEdgeForce(int i);
    double * gauss(double **a, double *y, int n);
};
#endif // CALCULATION_H
