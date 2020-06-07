#include "calculation.h"

Calculation::Calculation()
{

}
void Calculation::getVecRods(QVector<Rod*> item)
{
    vecRods = item;
}
void Calculation::CalEdgeForce() // хуевое название функции   базаришь
{
    int indexZadelkaL, indexZadelkaR;
    for(int i = 0; i < vecRods.size(); i++)
    {
        if (vecRods.at(i)->zadelkaL)
            indexZadelkaL = i;
        if (vecRods.at(i)->zadelkaR)
            indexZadelkaR = i;
    }
    //дичь
    double **a, *y, *x;

    int n;
    n = indexZadelkaR - indexZadelkaL;

    if(n <= 0)
    {
        //неправильно границы поставили, здесь приложение падает
        return;
    }

    a = new double*[n];
    y = new double[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n]; // заполнить нулями!!!

        for (int j = 0; j < n; j++)
            a[i][j] = 0;
        y[i] = 0;
    }
    //int currentEdge = 2;
    int counterEdge = 0;
    for (int i = indexZadelkaL; i < indexZadelkaR; i++)
    {
        a[counterEdge][counterEdge] = helpCalEdgeForce(i) + helpCalEdgeForce(i+1);
        if (counterEdge+1 < n)
            a[counterEdge][counterEdge+1] = -1 * helpCalEdgeForce(i+1);
        if (counterEdge - 1 >= 0)
            a[counterEdge][counterEdge-1] = -1 * helpCalEdgeForce(i);
        y[counterEdge] = vecRods.at(i)->Fr + (vecRods.at(i)->Qq * vecRods.at(i)->Ll)/2; // переделать!
        if (i+1 == indexZadelkaR && vecRods.at(indexZadelkaR)->Qq != 0)
            y[counterEdge] += (vecRods.at(indexZadelkaR)->Qq * vecRods.at(indexZadelkaR)->Ll)/2;
        counterEdge++;
    }
    for (int i = 0; i < n; i++)
    {
        qDebug() << endl;
        for (int j = 0; j < n; j++)
            qDebug() << a[i][j] << " ";
    }
    for (int i = 0; i < n; i++)
        qDebug() << y[i] << "    ";

    x = gauss(a, y, n);
    for (int i = 0; i < n; i++)
        qDebug() << x[i] << '\t';
    counterEdge = 0;
    for (int i = indexZadelkaL; i < indexZadelkaR; i++)
    {
        vecRods.at(i)  ->UuMOOOOVER = x[counterEdge];
        vecRods.at(i+1)->UuMOOOOVEL = x[counterEdge];

        counterEdge++;
    }
    //-----------
    for (int i = indexZadelkaL; i <= indexZadelkaR; i++)
    {
        vecRods.at(i)->NnL = (helpCalEdgeForce(i) * (vecRods.at(i)->UuMOOOOVER - vecRods.at(i)->UuMOOOOVEL)) + (((vecRods.at(i)->Qq * vecRods.at(i)->Ll)/2) * (1 - 2*(0)));
        vecRods.at(i)->NnR = (helpCalEdgeForce(i) * (vecRods.at(i)->UuMOOOOVER - vecRods.at(i)->UuMOOOOVEL)) + (((vecRods.at(i)->Qq * vecRods.at(i)->Ll)/2) * (1 - 2*(1)));
    }
    //-----------
    //for (int i = 0; i < n; i++)
        //delete[] a[i];
    //delete[] a;
    //delete[] x;
    //delete[] y;
}

double Calculation::helpCalEdgeForce(int i)
{
    return ((vecRods.at(i)->Aa * vecRods.at(i)->Ee)/vecRods.at(i)->Ll);
}

double * Calculation::gauss(double **a, double *y, int n)
{
    double *x, max;
    int k, index;
    const double eps = 0.00001;  // точность
    x = new double[n];
    k = 0;
    while (k < n)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        {
            // нет ненулевых диагональных элементов
            qDebug() << "reshenie nevozmojno nulevoi stolbec";
            qDebug() << index << " matrica A" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}
