#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Preprocessor * preprocessor = new Preprocessor;

    MyPainter * myPainter = new MyPainter;

    QVBoxLayout * mainLayout = new QVBoxLayout;

    mainLayout->addWidget(preprocessor);
    mainLayout->addWidget(myPainter);

    ui->centralwidget->setLayout(mainLayout);

    connect(preprocessor, SIGNAL(draw(Rod*)), myPainter, SLOT(onNewRodAdded(Rod *)));
    connect(preprocessor, SIGNAL(remove()), myPainter, SLOT(onRemove()));
    connect(preprocessor, SIGNAL(borderChanged(Border)), myPainter, SLOT(onBorderChanged(Border)));
    connect(myPainter, SIGNAL(signal_selected_rod(Rod*)), preprocessor, SLOT(onItemSelected(Rod *)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

