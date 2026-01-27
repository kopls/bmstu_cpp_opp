#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_load_btn_clicked()
{
}

void MainWindow::on_turn_btn_clicked()
{
}

void MainWindow::on_move_btn_clicked()
{
}

void MainWindow::on_scale_btn_clicked()
{
}
