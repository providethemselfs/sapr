#include "preprocessor.h"

Preprocessor::Preprocessor(QWidget *parent) : QFrame(parent)
{

    this->setFrameShape(Box);
    this->setMaximumHeight(100);

    QLabel * labL = new QLabel("Параметр L:");
    QLabel * labA = new QLabel("Параметр A:");
    QLabel * labE = new QLabel("Параметр E:");
    QLabel * labQ = new QLabel("Параметр Q:");
    QLabel * labFl = new QLabel("Параметр Fl:");
    QLabel * labFr = new QLabel("Параметр Fr:");




    leftBorder->setEnabled(false);
    rightBorder->setEnabled(false);

    QLabel * nlName = new QLabel("NL:");
    QLabel * ulName = new QLabel("UL:");
    QLabel * nrName = new QLabel("NR:");
    QLabel * urName = new QLabel("UR:");





    QVBoxLayout *mainLt = new QVBoxLayout;


    QHBoxLayout * procLt = new QHBoxLayout;
    procLt->addWidget(labL);
    procLt->addWidget(leL);

    procLt->addWidget(labA);
    procLt->addWidget(leA);

    procLt->addWidget(labE);
    procLt->addWidget(leE);

    procLt->addWidget(labQ);
    procLt->addWidget(leQ);

    procLt->addWidget(labFl);
    procLt->addWidget(leFl);

    procLt->addWidget(labFr);
    procLt->addWidget(leFr);

    procLt->addStretch();

    procLt->addWidget(drawB);
    procLt->addWidget(removeB);
    procLt->addWidget(leftBorder);
    procLt->addWidget(rightBorder);



    QHBoxLayout * resLt = new QHBoxLayout;
    resLt->addWidget(nlName);
    resLt->addWidget(nlValue);

    resLt->addWidget(ulName);
    resLt->addWidget(ulValue);

    resLt->addWidget(nrName);
    resLt->addWidget(nrValue);

    resLt->addWidget(urName);
    resLt->addWidget(urValue);

    resLt->addStretch();

    resW->setLayout(resLt);

    mainLt->addLayout(procLt);
    mainLt->addWidget(resW);



    this->setLayout(mainLt);

    removeB->setEnabled(false);
    resW->hide();

    connect(drawB, SIGNAL(clicked()), this, SLOT(onDrawClicked()));
    connect(removeB, SIGNAL(clicked()), this, SLOT(onRemoveClicked()));
    connect(leftBorder, SIGNAL(clicked()), this, SLOT(onLeftBorderClicked()));
    connect(rightBorder, SIGNAL(clicked()), this, SLOT(onRightBorderClicked()));

    connect(leL, SIGNAL(textChanged(QString)), this, SLOT(onLeChanged(QString)));
}

void Preprocessor::onDrawClicked()
{
    if(leL->text() == "" || leA->text() == "" || leE->text() == ""
            ||leQ->text() == "" || leFl->text() == "" || leFr->text() == "")
    {
        //оповестить, что поле не заполнено
        return;

    }

    Rod * r = new Rod;
    r->Ll = leL->text().toFloat();
    r->Aa = leA->text().toFloat();
    r->Ee = leE->text().toFloat();
    r->Qq = leQ->text().toFloat();
    r->Fl = leFl->text().toFloat();
    r->Fr = leFr->text().toFloat();


    emit this->draw(r);
}

void Preprocessor::onRemoveClicked()
{
    emit this->remove();
}

void Preprocessor::onLeftBorderClicked()
{
    emit this->borderChanged(Border::Left);
}

void Preprocessor::onRightBorderClicked()
{
    emit this->borderChanged(Border::Right);
}


void Preprocessor::onLeChanged(QString text)
{
    QLineEdit * le = static_cast<QLineEdit*>(sender());

    bool ok;
    text.toFloat(&ok);

    if(!ok)
    {
        le->setText("");
    }
}

void Preprocessor::onItemSelected(Rod *rod)
{

    if(rod != nullptr)
    {
        leL->setText(QString::number(rod->Ll));
        leA->setText(QString::number(rod->Aa));
        leE->setText(QString::number(rod->Ee));
        leQ->setText(QString::number(rod->Qq));
        leFl->setText(QString::number(rod->Fl));
        leFr->setText(QString::number(rod->Fr));

        nlValue->setText(QString::number(rod->NnL, 'g', 6));
        ulValue->setText(QString::number(rod->UuMOOOOVEL, 'g', 6));
        nrValue->setText(QString::number(rod->NnR, 'g', 6));
        urValue->setText(QString::number(rod->UuMOOOOVER, 'g', 6));

        resW->show();
    }
    else
    {
        leL->setText("");
        leA->setText("");
        leE->setText("");
        leQ->setText("");
        leFl->setText("");
        leFr->setText("");

        resW->hide();
    }

    drawB->setEnabled(rod == nullptr);
    removeB->setEnabled(rod != nullptr);

    leftBorder->setEnabled(rod != nullptr);
    rightBorder->setEnabled(rod != nullptr);
}
