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




    QHBoxLayout * mainLt = new QHBoxLayout;
    mainLt->addWidget(labL);
    mainLt->addWidget(leL);

    mainLt->addWidget(labA);
    mainLt->addWidget(leA);

    mainLt->addWidget(labE);
    mainLt->addWidget(leE);

    mainLt->addWidget(labQ);
    mainLt->addWidget(leQ);

    mainLt->addWidget(labFl);
    mainLt->addWidget(leFl);

    mainLt->addWidget(labFr);
    mainLt->addWidget(leFr);

    mainLt->addStretch();

    mainLt->addWidget(drawB);
    mainLt->addWidget(removeB);
    mainLt->addWidget(leftBorder);
    mainLt->addWidget(rightBorder);

    removeB->setEnabled(false);



    this->setLayout(mainLt);

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


    }
    else
    {
        leL->setText("");
        leA->setText("");
        leE->setText("");
        leQ->setText("");
        leFl->setText("");
        leFr->setText("");
    }

    drawB->setEnabled(rod == nullptr);
    removeB->setEnabled(rod != nullptr);

    leftBorder->setEnabled(rod != nullptr);
    rightBorder->setEnabled(rod != nullptr);
}
