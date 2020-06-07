#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QtGui> // как альтернатива <QPainter>
#include <calculation.h>
#include <rod.h>
#include "preprocessor.h"


class MyPainter : public QWidget, Calculation
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);



    int tempInt;
    float widthPntr;
    float heightPntr;
    void wheelEvent(QWheelEvent *event);
    QVector<Rod*> vecRods;
    void mouseMoveEvent(QMouseEvent *event);
    int cursorOn = -1;
    QPoint mousPos;
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
//    bool rightToChangeCursorOn = true;
    int selectedRod = -1;
//    bool rightToChangeSelectedRod = true;
    int modul = 45;
    int counttt = 0;




signals:
    void signal_cursor_change ();
    void signal_selected_rod(Rod * r);

public slots:

    void onNewRodAdded(Rod * r);

    void onBorderChanged(Border b);

    void onRemove();
};

#endif // MYPAINTER_H
