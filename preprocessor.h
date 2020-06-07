#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include "rod.h"

enum Border {Left, Right};


class Preprocessor : public QFrame
{
    Q_OBJECT
public:
    explicit Preprocessor(QWidget *parent = nullptr);

private:


    QLineEdit * leL = new QLineEdit;
    QLineEdit * leA = new QLineEdit;
    QLineEdit * leE = new QLineEdit;
    QLineEdit * leQ = new QLineEdit;
    QLineEdit * leFl = new QLineEdit;
    QLineEdit * leFr = new QLineEdit;

    QPushButton * drawB = new QPushButton("Рисовать");
    QPushButton * removeB = new QPushButton("Удалить");

    QPushButton *leftBorder = new QPushButton("Левая граница");
    QPushButton *rightBorder = new QPushButton("Правая граница");

    QLabel * nlValue = new QLabel;
    QLabel * ulValue = new QLabel;
    QLabel * nrValue = new QLabel;
    QLabel * urValue = new QLabel;

    QWidget * resW = new QWidget;

signals:

    void draw(Rod * newRod);
    void remove();
    void borderChanged(Border border);

private slots:

    void onDrawClicked();
    void onRemoveClicked();
    void onRightBorderClicked();
    void onLeftBorderClicked();


    void onLeChanged(QString text);

public slots:
    void onItemSelected(Rod * rod);

};



#endif // PREPROCESSOR_H
