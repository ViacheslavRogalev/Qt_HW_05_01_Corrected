#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stopwatch.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pb_StartStop->setText("Старт");
    ui->pb_clear->setText("Очистить");
    ui->pb_circle->setText("Круг");
    ui->lb_time->setText("Время");
    ui->pb_circle->setEnabled(false);

    stopwatcher = new Stopwatch(this);
    connect(stopwatcher, &Stopwatch::sig_StartTimer, this, &MainWindow::ReceiveStartSignal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReceiveStartSignal()
{
    ui->lb_time->setText(stopwatcher->time);
}

void MainWindow::on_pb_StartStop_toggled(bool checked)
{
    if (checked){
        ui->pb_StartStop->setText("Стоп");
        stopwatcher->StartTimer();
        ui->pb_circle->setEnabled(true);
    }
    else{
        ui->pb_StartStop->setText("Старт");
        stopwatcher->StopTimer();
        ui->pb_circle->setEnabled(false);
    }
}

void MainWindow::on_pb_clear_clicked()
{
    if(ui->pb_StartStop->isChecked()){
           stopwatcher->ClearTimer();
           stopwatcher->StartTimer();
    }
    else{
        ui->lb_time->setText("00:00:00:0000");
        stopwatcher->ClearTimer();
    }
}

void MainWindow::on_pb_circle_clicked()
{
    QString circleDiff = stopwatcher->CalculateCircle();
    ui->tBr_LapTimeDisplay->append("Круг " + QString::number(++circle_num) + ", время: " + circleDiff + " сек.");
}
