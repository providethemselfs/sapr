#include "mypainter.h"

#include <iterator>
#include <QVector>
#include <QBrush>

MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{
    tempInt = 20;
    this->setMouseTracking(true);
    setMinimumSize(50,100);
    //    cursorOn = -1;
    //    Form1 *as = new Form1;
    //    as->show();

}

void MyPainter::paintEvent(QPaintEvent *)
{
//    counttt ++;
//    qDebug() << counttt;
    QPainter paint(this);        // ИНИЦИАЦИЯ. тьфу блять, инициализация.
//    if (modul != 45 || counttt > 500)
//    {
//        QPointF pointText;
//        pointText.setX(10); pointText.setY(height()/2);
//        paint.drawText(pointText, "Пробный период закончен, получить полную версия можно, поставив студенту 45 баллов");
//    }
//    else
    {
        //qDebug() << "update";
        paint.setPen(QPen(Qt::black,2,Qt::SolidLine));
        //    paint.drawLine(tempInt,20,70,70);
        widthPntr  = this->width();
        heightPntr = this->height();
        QPointF pointWorkLeftTop;
        QPointF pointWorkRightBot;
        pointWorkLeftTop.setX(10);
        pointWorkLeftTop.setY(10);
        pointWorkRightBot.setX(widthPntr - 10);
        pointWorkRightBot.setY(heightPntr - 10);
        //    pointWorkLeftTop.setX(10);
        //    pointWorkLeftTop.setY(heightPntr/2 - widthPntr/5);
        //pointWorkLeftTop.setY(heightPntr/2 - widthPntr/3);    // изменено
        //    pointWorkRightBot.setX(widthPntr - 10);
        //    pointWorkRightBot.setY(heightPntr/2 + widthPntr/5);
        //pointWorkRightBot.setY(heightPntr/2);                 // изменено
        //    paint.drawPoint(pointWorkLeftTop);
        //    paint.drawPoint(pointWorkRightBot);
        //paint.drawLine(pointWorkLeftTop, pointWorkRightBot);
        QPointF pointRodsLT;                      // область отрисовки стержней Left Top
        QPointF pointRodsRB;                      // область отрисовки стержней Right Bot
        QPointF pointLongRodsLT;                  // область указания длинны L под стержнями
        QPointF pointLongRodsRB;                  // ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        QPointF pointTopSpaceNearRodsLT;          // возьмем немного места стержней сверху под пустое место. использовать для подписи элемента стержня
        QPointF pointTopSpaceNearRodsRB;          // ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        pointTopSpaceNearRodsLT = pointWorkLeftTop;
        pointTopSpaceNearRodsRB.setX(pointWorkRightBot.x());
        pointTopSpaceNearRodsRB.setY(pointWorkLeftTop.y() + (pointWorkRightBot.y() - pointWorkLeftTop.y())/10);
        pointRodsLT.setX(pointWorkLeftTop.x());
        pointRodsLT.setY(pointTopSpaceNearRodsRB.y());
        //    paint.drawPoint(pointTopSpaceNearRodsLT);
        //    paint.drawPoint(pointTopSpaceNearRodsRB);
        //pointRodsLT = pointWorkLeftTop;
        pointRodsRB.setX(pointWorkRightBot.x());
        pointRodsRB.setY(((((pointWorkRightBot.y() - pointWorkLeftTop.y())/3) * 2) + pointWorkLeftTop.y())); // эта сложная штука разделяет рабочую область, отдавая 2/3 под стержни и 1/3 под надпись под ними в виде длинны L
        //    paint.drawPoint(pointRodsLT);
        //    paint.drawPoint(pointRodsRB);
        //paint.drawLine(pointRodsLT, pointRodsRB);
        pointLongRodsLT.setX(pointWorkLeftTop.x());
        pointLongRodsLT.setY(pointRodsRB.y());
        pointLongRodsRB = pointWorkRightBot;
        //    paint.drawPoint(pointLongRodsLT);
        //    paint.drawPoint(pointLongRodsRB);
        //    paint.drawLine(pointLongRodsLT, pointLongRodsRB);

        //                     //
        /*разметка произведена */
        //                     //

        //    int sumRods = calculation.vecRods.length(); //количество стержней

        //    QVector <Rod*>::iterator it = calculation.vecRods.begin(); // КАКОГО ХУЯ. ЧТО ЗА ПИЗДЕЦ С ИТЕРАТОРАМИ!!!!!!!!!!
        //    //(*it)->Aa;

        //    if (!calculation.vecRods.empty())
        //        qDebug() << "               dd " <<
        //    for ( ; it != calculation.vecRods.end(); it++)
        //    {
        //        sumAa += (*it)->Aa;;
        //        sumLl += (*it)->Ll;
        //    }
        //    qDebug () << sumAa << '\t' << sumLl;
        float maxAa = 0;
        float sumLl = 0;
        for (int i = 0; i != this->vecRods.size(); i++)
        {
            if (maxAa < this->vecRods.at(i)->Aa)
                maxAa = this->vecRods.at(i)->Aa;
            sumLl += this->vecRods.at(i)->Ll;
        }
        //qDebug () << maxAa << '\t' << sumLl << '\t' << this->vecRods.size();

        for (int i = 0; i != this->vecRods.size(); i++)
        {
            float partLl = (pointRodsRB.x() - pointRodsLT.x()) / sumLl;
            float partAa = (pointRodsRB.y() - pointRodsLT.y()) / maxAa;
            this->vecRods.at(i)->longX = partLl * this->vecRods.at(i)->Ll;
            this->vecRods.at(i)->longY = partAa * this->vecRods.at(i)->Aa;
        }
        float midYy = (pointRodsRB.y() + pointRodsLT.y()) / 2;
        float sumOnXx = 0; sumOnXx += pointRodsLT.x();
        for (int i = 0; i != this->vecRods.size(); i++)
        {
            //        qDebug () << this->vecRods.at(i)->longX << '\t' << this->vecRods.at(i)->longY;
            this->vecRods.at(i)->pointLT.setX(sumOnXx);
            this->vecRods.at(i)->pointLT.setY(midYy - (this->vecRods.at(i)->longY / 2));
            this->vecRods.at(i)->pointRB.setX(sumOnXx + this->vecRods.at(i)->longX);
            sumOnXx += this->vecRods.at(i)->longX;
            this->vecRods.at(i)->pointRB.setY(midYy + (this->vecRods.at(i)->longY / 2));

            this->vecRods.at(i)->pointLB.setX(this->vecRods.at(i)->pointLT.x());
            this->vecRods.at(i)->pointLB.setY(this->vecRods.at(i)->pointRB.y());
            this->vecRods.at(i)->pointRT.setX(this->vecRods.at(i)->pointRB.x());
            this->vecRods.at(i)->pointRT.setY(this->vecRods.at(i)->pointLT.y());
            //QVector<QPoint> vecOut; vecOut.push_back(vecRods.at(i)->pointLT);    vecOut.push_back(vecRods.at(i)->pointRT);    vecOut.push_back(vecRods.at(i)->pointRT);    vecOut.push_back(vecRods.at(i)->pointRB);    vecOut.push_back(vecRods.at(i)->pointRB);    vecOut.push_back(vecRods.at(i)->pointLB);    vecOut.push_back(vecRods.at(i)->pointLB);    vecOut.push_back(vecRods.at(i)->pointLT);
            //paint.drawLines(vecOut);
            //QRect temp1; temp1.setTopLeft(vecRods.at(i)->pointLT); temp1.setBottomRight(vecRods.at(i)->pointRB);
            QPolygonF temp11; temp11.push_back(this->vecRods.at(i)->pointLB); temp11.push_back(this->vecRods.at(i)->pointLT); temp11.push_back(this->vecRods.at(i)->pointRT); temp11.push_back(this->vecRods.at(i)->pointRB);
            paint.drawPolygon(temp11);
            //----------
            if (vecRods.at(i)->zadelkaL == true)
            {
                QPen tempPen = paint.pen();
                paint.setPen(QPen(Qt::gray,18,Qt::SolidLine));
                paint.drawLine(vecRods.at(i)->pointLB,vecRods.at(i)->pointLT);
                paint.setPen(tempPen);
            }
            if (vecRods.at(i)->zadelkaR == true)
            {
                QPen tempPen = paint.pen();
                paint.setPen(QPen(Qt::gray,18,Qt::SolidLine));
                paint.drawLine(vecRods.at(i)->pointRB,vecRods.at(i)->pointRT);
                paint.setPen(tempPen);
            }

            //----------
            if (cursorOn == i)
            {
                QBrush brush;
                brush.setColor(Qt::yellow);
                brush.setStyle(Qt::Dense4Pattern); //brush.setStyle(Qt::SolidPattern);
                QPainterPath temp111; temp111.addPolygon(temp11);
                paint.fillPath(temp111,brush);
                paint.drawPolygon(temp11);
                //----------------------
                QPen p1,p2; p1 = paint.pen(); p2.setColor(Qt::red); paint.setPen(p2);
                QFont f1,f2;
                f1 = paint.font(); f2.setBold(true); f2.setPixelSize(17); paint.setFont(f2);
                if (mousPos.x() < widthPntr - 70)
                {
                    QString tempString; tempString.push_back("L="); tempString.push_back(QString::number(vecRods.at(i)->Ll));
                    paint.drawText(mousPos.x()+15, mousPos.y()+35, tempString);
                    tempString.clear(); tempString.push_back("A="); tempString.push_back(QString::number(vecRods.at(i)->Aa));
                    paint.drawText(mousPos.x()+15, mousPos.y()+55, tempString);
                    tempString.clear(); tempString.push_back("Q="); tempString.push_back(QString::number(vecRods.at(i)->Qq));
                    paint.drawText(mousPos.x()+15, mousPos.y()+75, tempString);
                    tempString.clear(); tempString.push_back("E="); tempString.push_back(QString::number(vecRods.at(i)->Ee));
                    paint.drawText(mousPos.x()+15, mousPos.y()+95, tempString);
                }
                else
                {
                    QString tempString; tempString.push_back("L="); tempString.push_back(QString::number(vecRods.at(i)->Ll));
                    paint.drawText(mousPos.x()-50, mousPos.y()+35, tempString);
                    tempString.clear(); tempString.push_back("A="); tempString.push_back(QString::number(vecRods.at(i)->Aa));
                    paint.drawText(mousPos.x()-50, mousPos.y()+50, tempString);
                    tempString.clear(); tempString.push_back("Q="); tempString.push_back(QString::number(vecRods.at(i)->Qq));
                    paint.drawText(mousPos.x()-50, mousPos.y()+65, tempString);
                    tempString.clear(); tempString.push_back("E="); tempString.push_back(QString::number(vecRods.at(i)->Ee));
                    paint.drawText(mousPos.x()-50, mousPos.y()+80, tempString);
                }

                paint.setPen(p1);
                paint.setFont(f1);
                if (selectedRod == -1)
                    emit signal_cursor_change ();

                // ----
                //            qDebug() << "UuLeft  " << vecRods.at(i)->UuMOOOOVEL;
                //            qDebug() << "UuRight " << vecRods.at(i)->UuMOOOOVER;

            }
            //---------------------------


            //----------------------
            if (selectedRod == i)
            {
                QBrush brush;
                brush.setColor(Qt::red);
                brush.setStyle(Qt::Dense4Pattern);
                //            brush.setStyle(Qt::SolidPattern);
                QPainterPath temp111; temp111.addPolygon(temp11);
                paint.fillPath(temp111,brush);
                paint.drawPolygon(temp11);

                //            emit signal_cursor_change();

            }
            //----------------------
            QFont f1,f2;
            f1 = paint.font();
            f2.setPixelSize((pointTopSpaceNearRodsRB.y() - pointTopSpaceNearRodsLT.y())*0.5);
            QRectF tempRectf;
            tempRectf.setBottom(pointTopSpaceNearRodsRB.y());
            tempRectf.setTop(pointTopSpaceNearRodsLT.y());
            tempRectf.setLeft(this->vecRods.at(i)->pointLT.x());
            tempRectf.setRight(this->vecRods.at(i)->pointRB.x());
            paint.setFont(f2);
            QTextOption tempTextOption; tempTextOption.setAlignment(Qt::AlignCenter);
            QString tempString; tempString.push_back("L="); tempString.push_back(QString::number(vecRods.at(i)->Ll)); tempString.push_back(" A=");tempString.push_back(QString::number(vecRods.at(i)->Aa));
            paint.drawText(tempRectf,tempString, tempTextOption);
            paint.setFont(f1);
            //----------------------------


            if (vecRods.at(i)->Fl > 0)
            {
                QPointF cordBeginArrow;
                cordBeginArrow.setX(vecRods.at(i)->pointLB.x());
                cordBeginArrow.setY((vecRods.at(i)->pointLB.y() + vecRods.at(i)->pointLT.y())/2);
                QPointF cordEndArrow;
                cordEndArrow.setX(cordBeginArrow.x() + vecRods.at(i)->longX/3);
                cordEndArrow.setY(cordBeginArrow.y());
                QPointF cordTopPointArrow;
                QPointF cordBotPointArrow;
                cordTopPointArrow.setX(cordEndArrow.x() - (cordEndArrow.x() - cordBeginArrow.x())/4);
                cordBotPointArrow.setX(cordTopPointArrow.x());
                cordTopPointArrow.setY(cordEndArrow.y() - (cordEndArrow.x() - cordBeginArrow.x())/10);
                cordBotPointArrow.setY(cordEndArrow.y() + (cordEndArrow.x() - cordBeginArrow.x())/10);
                if (cordBotPointArrow.y() - cordTopPointArrow.y() > (vecRods.at(i)->longY * 2/3))
                {
                    cordTopPointArrow.setY(cordEndArrow.y() + (vecRods.at(i)->longY * 2/3)/2);
                    cordBotPointArrow.setY(cordEndArrow.y() - (vecRods.at(i)->longY * 2/3)/2);
                }
                QPen tempPen = paint.pen();
                paint.setPen(QPen(Qt::red,2,Qt::SolidLine));
                paint.drawLine(cordBeginArrow, cordEndArrow); paint.drawLine(cordTopPointArrow, cordEndArrow); paint.drawLine(cordBotPointArrow, cordEndArrow);
                paint.setPen(tempPen);
            }
            if (vecRods.at(i)->Fr < 0)
            {
                QPointF cordBeginArrow;
                cordBeginArrow.setX(vecRods.at(i)->pointRB.x());
                cordBeginArrow.setY((vecRods.at(i)->pointRB.y() + vecRods.at(i)->pointRT.y())/2);
                QPointF cordEndArrow;
                cordEndArrow.setX(cordBeginArrow.x() - vecRods.at(i)->longX/3);
                cordEndArrow.setY(cordBeginArrow.y());
                QPointF cordTopPointArrow;
                QPointF cordBotPointArrow;
                cordTopPointArrow.setX(cordEndArrow.x() + (cordBeginArrow.x() - cordEndArrow.x())/4);
                cordBotPointArrow.setX(cordTopPointArrow.x());
                cordTopPointArrow.setY(cordEndArrow.y() - (cordBeginArrow.x() - cordEndArrow.x())/10);
                cordBotPointArrow.setY(cordEndArrow.y() + (cordBeginArrow.x() - cordEndArrow.x())/10);
                if (cordBotPointArrow.y() - cordTopPointArrow.y() > (vecRods.at(i)->longY * 2/3))
                {
                    cordTopPointArrow.setY(cordEndArrow.y() + (vecRods.at(i)->longY * 2/3)/2);
                    cordBotPointArrow.setY(cordEndArrow.y() - (vecRods.at(i)->longY * 2/3)/2);
                }
                QPen tempPen = paint.pen();
                paint.setPen(QPen(Qt::red,2,Qt::SolidLine));
                paint.drawLine(cordBeginArrow, cordEndArrow); paint.drawLine(cordTopPointArrow, cordEndArrow); paint.drawLine(cordBotPointArrow, cordEndArrow);
                paint.setPen(tempPen);
            }
            if (vecRods.at(i)->Qq > 0)
            {
                QPointF cordBeginArrow;
                cordBeginArrow.setX(vecRods.at(i)->pointLB.x() + vecRods.at(i)->longX/3);
                cordBeginArrow.setY((vecRods.at(i)->pointLB.y() + vecRods.at(i)->pointLT.y())/2);
                QPointF cordEndArrow;
                cordEndArrow.setX(vecRods.at(i)->pointRB.x() - vecRods.at(i)->longX/2.8);
                cordEndArrow.setY(cordBeginArrow.y());
                QPointF cordTopPointArrowL;
                QPointF cordMidPointArrowL;
                QPointF cordBotPointArrowL;
                cordMidPointArrowL.setY(cordBeginArrow.y());
                cordMidPointArrowL.setX(cordBeginArrow.x() + (cordEndArrow.x() - cordBeginArrow.x())/4);
                cordTopPointArrowL.setX(cordBeginArrow.x());
                cordBotPointArrowL.setX(cordBeginArrow.x());
                cordTopPointArrowL.setY(cordBeginArrow.y() - (cordEndArrow.x() - cordBeginArrow.x())/10);
                cordBotPointArrowL.setY(cordBeginArrow.y() + (cordEndArrow.x() - cordBeginArrow.x())/10);

                if (cordBotPointArrowL.y() - cordTopPointArrowL.y() > (vecRods.at(i)->longY * 2/3))
                {
                    cordTopPointArrowL.setY(cordEndArrow.y() + (vecRods.at(i)->longY * 2/3)/2);
                    cordBotPointArrowL.setY(cordEndArrow.y() - (vecRods.at(i)->longY * 2/3)/2);
                }
                QPen tempPen = paint.pen();
                paint.setPen(QPen(Qt::red,2,Qt::SolidLine));
                QPolygonF tempPF; tempPF.push_back(cordBotPointArrowL); tempPF.push_back(cordMidPointArrowL); tempPF.push_back(cordTopPointArrowL); tempPF.push_back(cordEndArrow);
                QBrush brush;
                brush.setColor(Qt::red);
                brush.setStyle(Qt::Dense4Pattern);
                //            brush.setStyle(Qt::SolidPattern);
                QPainterPath temp111; temp111.addPolygon(tempPF);
                paint.fillPath(temp111,brush);
                paint.drawPolygon(tempPF);
                paint.setPen(tempPen);
            }
            if (vecRods.at(i)->Qq < 0)
            {
                QPointF cordBeginArrow;
                cordBeginArrow.setX(vecRods.at(i)->pointRB.x() - vecRods.at(i)->longX/3);
                cordBeginArrow.setY((vecRods.at(i)->pointLB.y() + vecRods.at(i)->pointLT.y())/2);
                QPointF cordEndArrow;
                cordEndArrow.setX(vecRods.at(i)->pointLB.x() + vecRods.at(i)->longX/2.8);
                cordEndArrow.setY(cordBeginArrow.y());
                QPointF cordTopPointArrowR;
                QPointF cordMidPointArrowR;
                QPointF cordBotPointArrowR;
                cordMidPointArrowR.setY(cordBeginArrow.y());
                cordMidPointArrowR.setX(cordBeginArrow.x() - (cordBeginArrow.x() - cordEndArrow.x())/4);
                cordTopPointArrowR.setX(cordBeginArrow.x());
                cordBotPointArrowR.setX(cordBeginArrow.x());
                cordTopPointArrowR.setY(cordBeginArrow.y() - (cordBeginArrow.x() - cordEndArrow.x())/10);
                cordBotPointArrowR.setY(cordBeginArrow.y() + (cordBeginArrow.x() - cordEndArrow.x())/10);
                if (cordBotPointArrowR.y() - cordTopPointArrowR.y() > (vecRods.at(i)->longY * 2/3))
                {
                    cordTopPointArrowR.setY(cordEndArrow.y() + (vecRods.at(i)->longY * 2/3)/2);
                    cordBotPointArrowR.setY(cordEndArrow.y() - (vecRods.at(i)->longY * 2/3)/2);
                }

                QPen tempPen = paint.pen();
                paint.setPen(QPen(Qt::red,2,Qt::SolidLine));
                QPolygonF tempPF; tempPF.push_back(cordBotPointArrowR); tempPF.push_back(cordMidPointArrowR); tempPF.push_back(cordTopPointArrowR); tempPF.push_back(cordEndArrow);
                QBrush brush;
                brush.setColor(Qt::red);
                brush.setStyle(Qt::Dense4Pattern);
                //            brush.setStyle(Qt::SolidPattern);
                QPainterPath temp111; temp111.addPolygon(tempPF);
                paint.fillPath(temp111,brush);
                paint.drawPolygon(tempPF);
                paint.setPen(tempPen);
            }

        }
        //    if (selectedRod != -1)
        //        emit signal_change_line_edit (vecRods.at(i)->Ll, vecRods.at(i)->Aa, vecRods.at(i)->Ee, vecRods.at(i)->Qq, vecRods.at(i)->Fl, vecRods.at(i)->Fr);
        //---------------------
        float maxNn = -9999;
        float minNn = 0; // не знаю хорошая ли это идея
        for (int i = 0; i < vecRods.size(); i++)
        {
            if (vecRods.at(i)->NnL > maxNn)
                maxNn = vecRods.at(i)->NnL;
            if (vecRods.at(i)->NnR > maxNn)
                maxNn = vecRods.at(i)->NnR;
            if (vecRods.at(i)->NnL < minNn)
                minNn = vecRods.at(i)->NnL;
            if (vecRods.at(i)->NnR < minNn)
                minNn = vecRods.at(i)->NnR;
        }
        float defferenceMaxMin;
        defferenceMaxMin = maxNn - minNn;
        QPointF epyrLT = pointLongRodsLT;
        epyrLT.setY(epyrLT.y() + 10);
        QPointF epyrRB = pointLongRodsRB;
        float epyrLongY;
        epyrLongY = epyrRB.y() - epyrLT.y();
        QPolygonF epyrPolyg;
        QPointF helpEpyrPolyg;
        helpEpyrPolyg = epyrLT;

        float tempValue;
        tempValue = maxNn - 0;
        float tempValue2;
        tempValue2 = tempValue / defferenceMaxMin;
        float tempValue3;
        tempValue3 = epyrLongY * tempValue2;

        helpEpyrPolyg.setY(epyrLT.y() + tempValue3);
        epyrPolyg.push_back(helpEpyrPolyg);
        for (int i = 0; i < vecRods.size(); i++)
        {
            float tempValueL;
            tempValueL = maxNn - vecRods.at(i)->NnL;
            float tempValue2L;
            tempValue2L = tempValueL / defferenceMaxMin;
            float tempValue3L;
            tempValue3L = epyrLongY * tempValue2L;

            float tempValueR;
            tempValueR = maxNn - vecRods.at(i)->NnR;
            float tempValue2R;
            tempValue2R = tempValueR / defferenceMaxMin;
            float tempValue3R;
            tempValue3R = epyrLongY * tempValue2R;

            vecRods.at(i)->epyrNnL.setX(vecRods.at(i)->pointLB.x());
            vecRods.at(i)->epyrNnR.setX(vecRods.at(i)->pointRB.x());
            vecRods.at(i)->epyrNnL.setY(epyrLT.y() + tempValue3L);
            vecRods.at(i)->epyrNnR.setY(epyrLT.y() + tempValue3R);
            epyrPolyg.push_back(vecRods.at(i)->epyrNnL);
            epyrPolyg.push_back(vecRods.at(i)->epyrNnR);
        }
        helpEpyrPolyg.setX(epyrRB.x());
        epyrPolyg.push_back(helpEpyrPolyg);
        if (epyrPolyg.size() > 2)
            paint.drawPolygon(epyrPolyg);

        //---------------------


    }
}

void MyPainter::wheelEvent(QWheelEvent *event)
{
//    modul = 0;
    //    qDebug() << event->delta();
    if (event->delta() < 0)
        tempInt += 20;
    else
        tempInt -= 20;
    update(); // аналогичен     this->myWgt->repaint();
}

void MyPainter::mouseMoveEvent(QMouseEvent *event)
{
    mousPos = event->pos();
    update();
    //
    //
    //qDebug() << event->pos();
    int copyCursorOn = cursorOn;
    bool rodAlreadyFound = false;
    for (int i = 0; i < vecRods.size(); i++)
    {
        if ( vecRods.at(i)->pointLT.x() < event->x()
             && vecRods.at(i)->pointLT.y() < event->y()
             && vecRods.at(i)->pointRB.x() > event->x()
             && vecRods.at(i)->pointRB.y() > event->y()
             && rodAlreadyFound == false)                                  // МНЕ
        {                                                               // НЕ
            //qDebug() << vecRods.at(i)->Aa;                            // НРАВИТСЯ
            cursorOn = i;                                               // ЭТА
            rodAlreadyFound = true;                                     // ХУЕТА
        }                                                               //
        else                                                            // МОЖНО
        {                                                               // ПИСАТЬ
            if (!rodAlreadyFound)              // БОЛЕЕ
                cursorOn = -1;                                          // ПОНЯТНЫЙ
        }                                                               // КОД
    }                                                                   // БЕЗ
    //    qDebug() << cursorOn;                                             // ЕБУЧИХ
    if (copyCursorOn != cursorOn)                                       // КАСТЫЛЕЙ (нет)
        this->update();
}

void MyPainter::mousePressEvent(QMouseEvent *event)
{
    int selectedRodClon = selectedRod;
    qDebug() << event->buttons();
    if (event->buttons() == Qt::LeftButton || event->buttons() == Qt::RightButton)
    {
        qDebug() << " one click";
        //rightToChangeCursorOn = !rightToChangeCursorOn;
        if (selectedRod != cursorOn)
            selectedRod = cursorOn;
        else
            selectedRod = -1;
    }
    this->repaint();
    if (selectedRodClon != selectedRod)
    {
        if(selectedRod == -1)
            emit this->signal_selected_rod(nullptr);
        else
            emit this->signal_selected_rod(vecRods.at(selectedRod));
    }
    //    qDebug() << selectedRod;
}

void MyPainter::mouseDoubleClickEvent(QMouseEvent *event)
{
//    qDebug() << event->buttons();
//    if( event->buttons() == Qt::LeftButton)
//        qDebug() << "мы его победили (нет) double click";
    if (!vecRods.empty())
    {
        this->getVecRods(vecRods);
        this->CalEdgeForce();
    }
}

void MyPainter::onNewRodAdded(Rod * newRod)
{
    vecRods.push_back(newRod);
    update();
}

void MyPainter::onRemove()
{
    vecRods.removeAt(selectedRod);
    selectedRod = -1;
    repaint();
}

void MyPainter::onBorderChanged(Border b)
{
    if(b == Border::Left)
    {
        vecRods.at(selectedRod)->zadelkaL = !vecRods.at(selectedRod)->zadelkaL; // инверсия

    }
    else
    {
        vecRods.at(selectedRod)->zadelkaR = !vecRods.at(selectedRod)->zadelkaR; // инверсия
    }
    repaint();
}
