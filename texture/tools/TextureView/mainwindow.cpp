#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTexture(){
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()){
        if(!fileName.endsWith(".tga", Qt::CaseInsensitive))
            ui->panel->setTexture(fileName.toLatin1().constData());
        else
            ui->panel->setBumpMap(fileName.toLatin1().constData());
    }
}
