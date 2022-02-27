#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    appPath = QCoreApplication::applicationDirPath();
    qDebug() << "App Path:" << appPath;
    ui->imageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (QFile::exists(appPath+"/finger.pgm"))
    {
        QFile file (appPath+"/finger.pgm");
        file.remove();
    }
    ui->pushButton->setIcon(QIcon(":/images/swipeyourfinger.png"));
    QPixmap pixmap(":/images/doit.png");
    int w = pixmap.width() * 2;
    int h = pixmap.height() * 2;
    ui->imageLabel->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));

    QApplication::processEvents();
    QProcess *process = new QProcess();
    try {
        process->start(appPath+"/capture", QStringList() );
        process->waitForFinished();
        process->close();
        if (QFile::exists(appPath+"/finger.pgm"))
        {
            QPixmap pixmap(appPath+"/finger.pgm");
            int w = pixmap.width() * 2;
            int h = pixmap.height() * 2;
            ui->imageLabel->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
        } else {
            QPixmap pixmap(":/images/tryagain.png");
            int w = pixmap.width() * 2;
            int h = pixmap.height() * 2;
            ui->imageLabel->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
        }
    }
    catch (...) {
        QPixmap pixmap(":/images/tryagain.png");
        int w = pixmap.width() * 2;
        int h = pixmap.height() * 2;
        ui->imageLabel->setPixmap(pixmap.scaled(w,h,Qt::KeepAspectRatio));
    }
    ui->pushButton->setIcon(QIcon(":/images/starttoscan.png"));
}
